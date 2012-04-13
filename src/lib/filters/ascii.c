/**
 * ascii.c
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
#include "../internal.h"


/**
 * filter returns 0 if char was not valid
 */
int STDBAR_FILTER_ASCII(int ch, void* handle) {
  stdbar_internal_handle* h = (stdbar_internal_handle*) handle;

  // check if the character is allowed or the end of line char.
  if((ch >= 0 && ch <= 127) || ch == h->endOfCodeChar) {
    return ch;
  }

  return 0;
}

