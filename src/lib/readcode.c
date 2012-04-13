/**
 * readcode.
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


#include <memory.h>
#include <stdbar.h>
#include "internal.h"


int stdbar_readCode(stdbar_handle h, char* buffer, int len) {
  stdbar_internal_handle* internal = (stdbar_internal_handle*) h;

  //
  // check if the code will be long enough.
  // the code should not be shorter than the minimum given by the user
  if(len-1 < internal->endOfCodeLength) {
    return STDBAR_ERR_TOO_SHORT;
  }

  //
  // clear the buffer.
  memset(buffer, 0, len);

  //
  // read the code from the device.
  int length = 0;
  while(1) {
    // read a scancode...
    int scanCode = __stdbar_read(internal->fd);
    if(scanCode == -1) {
      return STDBAR_ERR_INTERNAL;
    }

    //
    // convert the scancode.
    int num = __stdbar_scan2key(scanCode, internal);
    if(num < 0) {
      continue;
    }

    //
    // if filters are enabled, filter.
    if(internal->filterfunction != 0 && internal->enableFilter == STDBAR_FILTER_ON) {
      num = internal->filterfunction(num, internal);
      if(num == 0) {
        // character was filtered.
        continue;
      }
    }

    // 
    // check if it's the return sign.
    if(num == internal->endOfCodeChar) {
      break;
    }

    //
    // check if the code is too long for the expected result.
    if(length >= len-1) {
      return STDBAR_ERR_INVALIDCODE;
    }

    //
    // we got a character, set that.
    buffer[length++] = num;
  }

  //
  // check if we got a full code.
  if(internal->fixedLength == 1 && length != internal->endOfCodeLength) {
    return STDBAR_ERR_INVALIDCODE;
  }

  // workked.
  return STDBAR_OK;
}
