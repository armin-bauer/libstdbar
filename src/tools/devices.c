/**
 * devices.c
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

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <memory.h>
#include <stdio.h>
#include <stdbar.h>


int main(int argc, char** argv) {
  // print out the existing devices.
  int numDevices = stdbar_countDevices();

  // print message.
  printf("%s:\n", argv[0]);
  printf("Found %d devices:\n", numDevices);

  // get the device ids.
  int i=0;
  for(;i<numDevices;i++) {
    stdbar_device_description devDescription;

    // get device description.
    int result = stdbar_getDeviceInfo(i, &devDescription);
    if(result == STDBAR_OK) {
      printf("  %d) %s: %s (%s)\n", i, devDescription.deviceFilename, devDescription.name, devDescription.deviceLocation);
    }
  }

  // return to calling process.
  return 0;
}
