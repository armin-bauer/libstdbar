/**
 * scan2key.c
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
#include <linux/input.h>
#include <stdbar.h>
#include "../internal.h"



int __stdbar_scan2key(int scancode, stdbar_internal_handle* handle) {
  int shiftstate = handle->SHIFT;
  handle->SHIFT = (scancode == KEY_LEFTSHIFT || scancode == KEY_RIGHTSHIFT);
  if(handle->SHIFT == 1) {
    return -1;
  }

  switch(scancode)
  {
    case KEY_1:     return '1';
    case KEY_2:     return '2';
    case KEY_3:     return '3';
    case KEY_4:     return '4';
    case KEY_5:     return '5';
    case KEY_6:     return '6';
    case KEY_7:     return '7';
    case KEY_8:     return '8';
    case KEY_9:     return '9';
    case KEY_0:     return '0';
    case KEY_A:     return shiftstate == 1 ? 'A' : 'a';
    case KEY_B:     return shiftstate == 1 ? 'B' : 'b';
    case KEY_C:     return shiftstate == 1 ? 'C' : 'c';
    case KEY_D:     return shiftstate == 1 ? 'D' : 'd';
    case KEY_E:     return shiftstate == 1 ? 'E' : 'e';
    case KEY_F:     return shiftstate == 1 ? 'F' : 'f';
    case KEY_G:     return shiftstate == 1 ? 'G' : 'g';
    case KEY_H:     return shiftstate == 1 ? 'H' : 'h';
    case KEY_I:     return shiftstate == 1 ? 'I' : 'i';
    case KEY_J:     return shiftstate == 1 ? 'J' : 'j';
    case KEY_K:     return shiftstate == 1 ? 'K' : 'k';
    case KEY_L:     return shiftstate == 1 ? 'L' : 'l';
    case KEY_M:     return shiftstate == 1 ? 'M' : 'm';
    case KEY_N:     return shiftstate == 1 ? 'N' : 'n';
    case KEY_O:     return shiftstate == 1 ? 'O' : 'o';
    case KEY_P:     return shiftstate == 1 ? 'P' : 'p';
    case KEY_Q:     return shiftstate == 1 ? 'Q' : 'q';
    case KEY_R:     return shiftstate == 1 ? 'R' : 'r';
    case KEY_S:     return shiftstate == 1 ? 'S' : 's';
    case KEY_T:     return shiftstate == 1 ? 'T' : 't';
    case KEY_U:     return shiftstate == 1 ? 'U' : 'u';
    case KEY_V:     return shiftstate == 1 ? 'V' : 'v';
    case KEY_W:     return shiftstate == 1 ? 'W' : 'w';
    case KEY_X:     return shiftstate == 1 ? 'X' : 'x';
    case KEY_Y:     return shiftstate == 1 ? 'Y' : 'y';
    case KEY_Z:     return shiftstate == 1 ? 'Z' : 'z';
    case KEY_SPACE: return ' ';
    case KEY_TAB:   return '\t';
    case KEY_ENTER: return '\n';
    case KEY_MINUS: return '-';
    case KEY_EQUAL: return '=';
  }

//#ifdef _STDBAR_DEBUG
  printf("DEBUG: unknown scancode: %d\n", scancode);
//#endif // _STDBAR_DEBUG

  // not found in table
  return -1;
}
