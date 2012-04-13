/**
 * setCodetype.c
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


void stdbar_setCodeType(stdbar_handle handle, int type) {
  // get the handle
  stdbar_internal_handle* h = (stdbar_internal_handle*) handle;

  // defaults.
  h->filterfunction = 0;
  h->fixedLength = 1;

  // set defaults for the codetype.
  switch(type) {
    case STDBAR_TYPE_BARCODE_EAN8:      // ean8 codes.
                                        h->type = STDBAR_TYPE_BARCODE_EAN8;
                                        h->endOfCodeChar = '\n';
                                        h->endOfCodeLength = 8;
                                        h->filterfunction = STDBAR_FILTER_NUMBERS;
                                        break;

    case STDBAR_TYPE_BARCODE_EAN13:     // ean13 codes.
                                        h->type = STDBAR_TYPE_BARCODE_EAN13;
                                        h->endOfCodeChar = '\n';
                                        h->endOfCodeLength = 13;
                                        h->filterfunction = STDBAR_FILTER_NUMBERS;
                                        break;

    case STDBAR_TYPE_BARCODE_CODE128:
                                        // take anything and end with linebreak
                                        h->type = STDBAR_TYPE_BARCODE_CODE128;
                                        h->endOfCodeChar = '\n';
                                        h->endOfCodeLength = 1;
                                        h->fixedLength = 0;
                                        h->filterfunction = STDBAR_FILTER_ASCII;
                                        break;

    case STDBAR_TYPE_BARCODE_ANY_LINEBREAK:
                                        // take anything and end with linebreak
                                        h->type = STDBAR_TYPE_BARCODE_ANY_LINEBREAK;
                                        h->endOfCodeChar = '\n';
                                        h->endOfCodeLength = 1;
                                        h->fixedLength = 0;
                                        break;

    default:
    case STDBAR_TYPE_BARCODE_NONE:      // no type registered.
                                        h->type = STDBAR_TYPE_BARCODE_NONE;
                                        h->endOfCodeChar = '\0';
                                        h->endOfCodeLength = 0;
                                        h->fixedLength = 0;
                                        break;
  }
}


