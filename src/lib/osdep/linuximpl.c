/**
 * linuximpl.c
 * 
 * This file is part of lib_stdbar.
 *
 * lib_stdbar is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * lib_stdbar is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with lib_stdbar.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdbar.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <linux/input.h>
#include <memory.h>
#include "../internal.h"

#ifdef STDBAR_LINUX


typedef struct STDBAR_HANDLE_STRUCT {
  int fd;
} STDBAR_HANDLE_STRUCT;


/**
 * this os dependent function checks if the device exists.
 * @param num the device identifier. if the os doesnt supply identifiers, the abstraction has to
 * @return 1 if the device exists, 0 otherwise
 */
int __stdbar_checkDevice(int num) {
  char buffer[STDBAR_MAX_STR_LEN];
  struct stat s;

  // make the path to the event
  memset(buffer, 0, STDBAR_MAX_STR_LEN);
  snprintf(buffer, STDBAR_MAX_STR_LEN-1, EVENT_DEVICES, num);

  // returns 1 on success while stat returns 0, so switch
  return stat(buffer, &s) == 0 ? 1 : 0;
}

/**
 * reads out the device info structure and fills it.
 * @param pos the device identifier. if the os doesnt supply identifiers, the abstraction has to
 * @return 0 if it worked.
 */
int __stdbar_getDeviceInfo(stdbar_device_description* dev, int pos) {
  char buffer[STDBAR_MAX_STR_LEN];
  struct stat s;

  // make the path to the event
  memset(buffer, 0, STDBAR_MAX_STR_LEN);
  snprintf(buffer, STDBAR_MAX_STR_LEN-1, EVENT_DEVICES, pos);
  
  // open the handle.
  int fd = open(buffer, O_RDONLY);
  if(fd == -1) {
    return 0;
  }

  // set the params.
  dev->initialised = 1;
  dev->driverVersion = 0;
  dev->deviceNo = pos;
  strncpy(dev->deviceFilename, buffer, STDBAR_MAX_STR_LEN);
  ioctl(fd, EVIOCGNAME(STDBAR_MAX_STR_LEN), dev->name);
  ioctl(fd, EVIOCGPHYS(STDBAR_MAX_STR_LEN), dev->deviceLocation);

  // worked, have initialised the file.
  close(fd);
  return 1;
}


/**
 * returns a handle for the input device
 * @param pos describes the device to be opened (eg by name)
 * @return 0 not working, 1 otherwise
 */
int __stdbar_opendevice(const char* deviceFile, osdephandle x) {
  STDBAR_HANDLE_STRUCT* s = (STDBAR_HANDLE_STRUCT*) x;

  // open the file with lowlevel sync io.
  s->fd = open(deviceFile, O_SYNC|O_RDONLY|O_RDWR);

  // return 1 if it worked.
  return (s->fd >= 0) ? 1 : 0;
}

/**
 * closes the given device
 */
void __stdbar_close(osdephandle x) {
  STDBAR_HANDLE_STRUCT* s = (STDBAR_HANDLE_STRUCT*) x;

  // if the file handle is opened, close it
  if(s->fd != -1) {
    close(s->fd);
  }
}

/**
 * enables exclusive mode to the device
 * @return 0 if failed, 1 if succeeded
 */
int __stdbar_setExclusive(osdephandle x) {
  STDBAR_HANDLE_STRUCT* s = (STDBAR_HANDLE_STRUCT*) x;

  // use iocontrol to grab the device
  return ioctl(s->fd, EVIOCGRAB, ((void*)1)) == 0 ? 1 : 0;
}


/**
 * read char from the device.
 * @return -1 (or < 0) for error, should break the reading. >0 means a scancode is coming
 */
int __stdbar_read(osdephandle x) {
  STDBAR_HANDLE_STRUCT* s = (STDBAR_HANDLE_STRUCT*) x;
  int fd = s->fd;
	struct input_event event;
	fd_set rd;

  // read the events.
	while(1) {
		FD_ZERO(&rd);
		FD_SET(fd, &rd);

		// select
		int s = select(fd+1, &rd, 0, 0, 0);
		if(s == -1) {
      return -1;
		}

		// read what came from the fd.
		int n = read(fd, (void*)&event, sizeof(event));
    if(n == -1) {
      // no data or error although select returned...
      return -1;
    }

		// check what we got.
    if(event.type == EV_KEY && event.value == 1) {
      // printf("Got: Type %d, Value: %d, Code:%d\n", event.type, event.value, event.code);
      return event.code;
    }
	}
}


#endif // STDBAR_LINUX
