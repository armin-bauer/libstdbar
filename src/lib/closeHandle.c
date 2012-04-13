/**
 * closeHandle.c
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



void stdbar_closeHandle(stdbar_handle handle) {
  stdbar_internal_handle* x = (stdbar_internal_handle*) handle;

  // close the handle.
  if(x->fd != 0) {
    __stdbar_close(x->fd);
    free(x->fd);
  }
  
  free(x);
}

