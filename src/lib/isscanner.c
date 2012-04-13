/**
 * isscanner.c
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

#include <malloc.h>
#include <stdbar.h>
#include "internal.h"


static const char* listOfKnownDevices[] =
{
   "USB-SON-V0"
};


int stdbar_deviceIsScanner(stdbar_device_description* dev) {
  int i=0;

  if(stdbar_deviceIsInitialised(dev) == 0) {
    // uninitialised means not a scanner
    return 0;
  }

  //
  // go through the list of known devices and return 1 if this
  // one was found.
  for(;i<sizeof(listOfKnownDevices)/sizeof(char*);i++) {
    if(strcmp(listOfKnownDevices[i], dev->name) == 0) {
      // found the device, must be a scanner.
      // TODO: implement some more detecion
      return 1;
    }
  }

  // return 0 because this device was not recognized as a barcode scanner.
  return 0;
}
