/**
 * openDevice.c
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

#include <stdio.h>
#include <malloc.h>
#include <stdbar.h>
#include "internal.h"



stdbar_handle stdbar_openDeviceByNum(int deviceId, int mode, int* errorRes) {
  stdbar_device_description dev;

  // create the path.
  int result = stdbar_getDeviceInfo(deviceId, &dev);
  if(result != STDBAR_OK) {
    *errorRes = STDBAR_ERR_NOTFOUND;
    return 0;
  }

  //
  // try opening the device.
  return stdbar_openDevice(dev.deviceFilename, mode, errorRes);
}


stdbar_handle stdbar_openDevice(const char* deviceFile, int mode, int* errorRes) {
  // try opening the file descriptor.
  osdephandle osdh = malloc(OSDH_SIZE);
	int res = __stdbar_opendevice(deviceFile, osdh);
	if(res == -1) {
    free(osdh);
    *errorRes = STDBAR_ERR_NOTFOUND;
		return 0;
	}

  // prepare the handle structure.
  stdbar_handle result = (stdbar_handle) malloc(sizeof(stdbar_internal_handle));
  stdbar_internal_handle* internal = (stdbar_internal_handle*) result;

  // initialise the structure.
  internal->fd = osdh;
  internal->mode = mode;

  // TODO: set default options.
  stdbar_setCodeType(result, STDBAR_TYPE_BARCODE_NONE);
  stdbar_setFilterState(result, STDBAR_FILTER_OFF);


  // grab device if needed.
  if(mode & STDBAR_OPEN_EXCLUSIVE != 0) {
    // this grabs the device getting exclusive access
    int rslt = __stdbar_setExclusive(internal->fd);
    if(rslt == 0) {
      // close the device handle.
      stdbar_closeHandle(result);
      *errorRes = STDBAR_ERR_EXCLUSIVE_NOT_POSSIBLE;
      return 0;
    }
  }

  //
  // set no error.
  *errorRes = STDBAR_OK;
  return result;
}
