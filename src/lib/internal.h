/**
 * internal.h
 *
 * Copyright (c) 2011 Armin Bauer (eulerpfad.com)
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#include "config.h"

typedef void *osdephandle;

/** 
 * filterfunctions filter a code to correct errornous chars included 
 * by faulty scanners into the code.
 */
typedef int (*filtercode)(int ch, void* handle);


/**
 * internal description
 */
typedef struct stdbar_internal_handle {
  osdephandle fd;
  int type;
  int endOfCodeChar;
  int endOfCodeLength;
  int mode;
  filtercode filterfunction;
  int enableFilter;
  int fixedLength;
  char devicename[STDBAR_MAX_STR_LEN];

  // options for the scanning process.
  int SHIFT;
} stdbar_internal_handle;


/**
 * this os dependent function checks if the device exists.
 * @param num the device identifier. if the os doesnt supply identifiers, the abstraction has to
 * @return 1 if the device exists, 0 otherwise
 */
int __stdbar_checkDevice(int num);

/**
 * reads out the device info structure and fills it.
 * @param pos the device identifier. if the os doesnt supply identifiers, the abstraction has to
 * @return 1 if it worked, 0 otherwise.
 */
int __stdbar_getDeviceInfo(stdbar_device_description* dev, int pos);

/** 
 * returns a handle for the input device
 * @param pos describes the device to be opened (eg by name)
 * @return 0 not working, 1 otherwise
 */
int __stdbar_opendevice(const char* pos, void* s);

/**
 * closes the given device
 */
void __stdbar_close(osdephandle x);

/**
 * read char from the device.
 * @return -1 (or < 0) for error, should break the reading. >0 means a scancode is coming
 */
int __stdbar_read(osdephandle x);

/**
 * enables exclusive mode to the device
 * @return 0 if failed, 1 if succeeded
 */
int __stdbar_setExclusive(osdephandle x);

/**
 * convert a scancode to a keycode
 * @return >0 is a keycode, -1 (or <0) is an error message
 */
int __stdbar_scan2key(int scancode, stdbar_internal_handle* handle);



// filter functions.
extern int STDBAR_FILTER_NUMBERS(int ch, void* handle);
extern int STDBAR_FILTER_ASCII(int ch, void* handle);

