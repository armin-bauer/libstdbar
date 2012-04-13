/**
 * countDevices.c
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
#include "internal.h"


int stdbar_countDevices() {
  int foundDevices = 0;

  // try to find out how many event devices we have in the system at the moment.
  int i=0;
  for(;i<STDBAR_MAX_EVENT_FILES;i++) {
    // try to stat the file.
    if(1 == __stdbar_checkDevice(i)) {
      foundDevices++;
    }
  }

  // return number of found devices.
  return foundDevices;
}

