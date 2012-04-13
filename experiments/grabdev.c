/**
 * grabdev.c
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
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/input.h>



// 
// try getting the keyboard events.
int main(int argc, const char** argv) {
	struct input_event event;
	unsigned int entry[2];
	const char* device = argv[1];
	
	// 
	// open the device
	printf("Opening device %s\n", device);
	int fd = open(device, O_SYNC|O_RDONLY|O_RDWR);
	if(fd == -1) {
		printf("error opening file.\n");
		return -1;
	}

	// 
	// try grabbing the device
	ioctl(fd, EVIOCGRAB);


	// read the events.
	fd_set rd;
	while(1) {
		FD_ZERO(&rd);
		FD_SET(fd, &rd);

		// select
		int s = select(fd+1, &rd, 0, 0, 0);
		if(s == -1) {
			printf("error on select.\n");
			return -2;
		}

		// read what came from the fd.
		int n = read(fd, (void*)&event, sizeof(event));
		
		// tell what we got.
		if(event.type == EV_KEY && event.value == 1) {
			// convert scancode to 
			entry[0] = event.code;
			int nRet = ioctl(fd, EVIOCGKEYCODE, entry);
			printf("%d\n", nRet);

			// print the key character.
			printf("%d\n", entry[1]);
		}
	}

	return 0;
}

