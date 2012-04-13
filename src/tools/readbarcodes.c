/**
 * readbarcodes.c
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



void printUsage() {
  printf("Usage:\n");
  printf("       readcodes /dev/input/eventX [options]\n");
  printf("\n");
  printf("  --ean8     ... read EAN8 codes\n");
  printf("  --ean13    ... read EAN13 codes\n");
  printf("  --code128  ... read Code128 codes\n");
}


int main(int argc, char** argv) {
  char buffer[2048];
  int errors = 0;

  // 
  // get the device to read from.
  const char* readDevice = argv[1];
  if(argc < 2) {
    printUsage();
    return 0;
  }

  // open the device.
  stdbar_handle handle = stdbar_openDevice(readDevice, STDBAR_OPEN_EXCLUSIVE, &errors);
  if(handle == 0) {
    printf("Error %d opening the device.\n", errors);
    return 0;
  }

  //
  // perform configuration
  stdbar_setCodeType(handle, STDBAR_TYPE_BARCODE_ANY_LINEBREAK);
  if(argc > 2 && strcmp("--ean13", argv[2]) == 0) {
    stdbar_setCodeType(handle, STDBAR_TYPE_BARCODE_EAN13);
    stdbar_setFilterState(handle, STDBAR_FILTER_ON);
  } else if(argc > 2 && strcmp("--ean8", argv[2]) == 0) {
    stdbar_setCodeType(handle, STDBAR_TYPE_BARCODE_EAN8);
    stdbar_setFilterState(handle, STDBAR_FILTER_ON);
  } else if(argc > 2 && strcmp("--code128", argv[2]) == 0) {
    stdbar_setCodeType(handle, STDBAR_TYPE_BARCODE_CODE128);
    stdbar_setFilterState(handle, STDBAR_FILTER_ON);
  }

  //
  // Announce we'll scan now:
  printf("Beginning scan: \n");

  //
  // read barcodes.
  while(1) {
    // read one barcode.
    int nRet = stdbar_readCode(handle, buffer, 2048);
    if(nRet == STDBAR_ERR_INVALIDCODE) {
      continue;
    } else if(nRet != STDBAR_OK) {
      break;
    }

    // print out the barcode.
    printf("  Barcode scanned: %s\n", buffer);
  }


  // close the device.
  stdbar_closeHandle(handle);

  // return to calling process.
  return 0;
}
