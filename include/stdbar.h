/**
 * stdbar.h
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

#ifndef __INCLUDED_STDBAR_H
#define __INCLUDED_STDBAR_H 1


#define STDBAR_LIBRARY_VERSION   "1.0.0"

#define STDBAR_MAX_STR_LEN 1024

#define STDBAR_OPEN_NONEXCLUSIVE            0                    /// device still prints to stdin
#define STDBAR_OPEN_EXCLUSIVE               1                    /// open device in exclusive mode, the device won't post data to stdin or X

#define STDBAR_ERR_INVALIDCODE             -4
#define STDBAR_ERR_INTERNAL                -3
#define STDBAR_ERR_TOO_SHORT               -2
#define STDBAR_ERR_EXCLUSIVE_NOT_POSSIBLE  -1
#define STDBAR_ERR_NOTFOUND                 0
#define STDBAR_OK                           1

#define STDBAR_INITIALISED                  1
#define STDBAR_NOT_INITIALISED              0

#define STDBAR_FILTER_OFF                   0
#define STDBAR_FILTER_ON                    1


#define STDBAR_TYPE_BARCODE_NONE            0
#define STDBAR_TYPE_BARCODE_ANY_LINEBREAK   1
#define STDBAR_TYPE_BARCODE_EAN8            2
#define STDBAR_TYPE_BARCODE_EAN13           3
#define STDBAR_TYPE_BARCODE_CODE128         4



typedef struct stdbar_device_description {
  int             initialised;                         /// if this is 0, the structure is not initialised
  char            name[STDBAR_MAX_STR_LEN];
  int             driverVersion;
  char            deviceLocation[STDBAR_MAX_STR_LEN];
  char            deviceFilename[STDBAR_MAX_STR_LEN];
  int             deviceNo;
} stdbar_device_description;

typedef void* stdbar_handle;


#ifdef __cplusplus
extern "C" {
#endif // __cplusplus


/**
 * this function returns the active library version at runtime.
 */
const char* stdbar_getVersion();

/**
 * this function returns the number of devices currently known
 */
int stdbar_countDevices();

/**
 * returns information about a device.
 * @param num the number of the device. must be >= 0 and < countDevices
 * @return STDBAR_OK on success, STDBAR_ERR_* otherwise
 */
int stdbar_getDeviceInfo(int num, stdbar_device_description* dev);

/**
 * @return STDBAR_NOT_INITIALISED if the structure is not initialised, STDBAR_INITIALISED otherwise.
 */
int stdbar_deviceIsInitialised(stdbar_device_description* dev);

/**
 * @return 0 if its not a barcode scanner,  1 if it is
 */
int stdbar_deviceIsScanner(stdbar_device_description* dev);

/**
 * opens a device using /dev/input/eventX as a filename
 * @param mode mode of operation for this device
 */
stdbar_handle stdbar_openDeviceByNum(int deviceId, int mode, int* errorRes);

/**
 * opens a device
 * @param mode mode of operation for this device
 */
stdbar_handle stdbar_openDevice(const char* deviceFile, int mode, int* errorRes);

/**
 * sets the codetype for the scanner.
 * @param type one out of STDBAR_TYPE_BARCODE_*
 */
void stdbar_setCodeType(stdbar_handle handle, int type);

/**
 * sets the filterstate.
 * @param filter one of STDBAR_FILTER_OFF or STDBAR_FILTER_ON
 */
void stdbar_setFilterState(stdbar_handle handle, int type);

/**
 * close a device
 */
void stdbar_closeHandle(stdbar_handle handle);

/**
 * reads a barcode from the handle
 * Note: function will fail, if buffer is too small. Buffer should be at last 1+CODELENGTH where
 * codelength is a property of the handle (for example 13 on EAN13)
 * 
 * @return STBAR_OK if succeeded or one of STDBAR_ERR_* if failed
 */
int stdbar_readCode(stdbar_handle handle, char* buffer, int len);



#ifdef __cplusplus
}
#endif // __cplusplus
#endif // __INCLUDED_STDBAR_H
