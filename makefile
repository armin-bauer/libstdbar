OBJECTS_LIBRARY=src/lib/library.o												\
				src/lib/countDevices.o											\
				src/lib/getDeviceInfo.o											\
				src/lib/deviceIsInitialised.o									\
				src/lib/openDevice.o											\
				src/lib/options.o												\
				src/lib/closeHandle.o											\
				src/lib/isscanner.o												\
				src/lib/osdep/linuximpl.o										\
				src/lib/setCodetype.o											\
				src/lib/readcode.o												\
				src/lib/codes/scan2key.o										\
				src/lib/filters/numbersonly.o									\
				src/lib/filters/ascii.o											\

OBJECTS_DEVICES=src/tools/devices.o
OBJECTS_READBARCODES=src/tools/readbarcodes.o
OBJECTS_DETECTSCANNERS=src/tools/detect.o

LIBRARY_OUTPUT_STATIC=bin/stdbar.a
LIBRARY_OUTPUT_SO=bin/stdbar.so
TOOL_OUTPUT_DEVICES=bin/devices
TOOL_OUTPUT_READBARCODES=bin/readcodes
TOOL_OUTPUT_DETECTSCANNERS=bin/scanners

CFLAGS=-Iinclude/ -fPIC -g
CXXFLAGS=-Iinclude/ -fPIC -g
LDFLAGS=


all: $(OBJECTS_LIBRARY) $(OBJECTS_DEVICES) $(OBJECTS_READBARCODES) $(OBJECTS_DETECTSCANNERS)
	rm -f $(LIBRARY_OUTPUT_STATIC) $(LIBRARY_OUTPUT_SO) $(TOOL_OUTPUT_DEVICES) $(TOOL_OUTPUT_READBARCODES)
	
	# build static and dynamic archive
	ar r $(LIBRARY_OUTPUT_STATIC) $(OBJECTS_LIBRARY)
	c++ --shared -o $(LIBRARY_OUTPUT_SO) $(OBJECTS_LIBRARY)
	
	# build the tools
	c++ -o $(TOOL_OUTPUT_DEVICES) $(OBJECTS_DEVICES) $(LIBRARY_OUTPUT_STATIC)
	c++ -o $(TOOL_OUTPUT_READBARCODES) $(OBJECTS_READBARCODES) $(LIBRARY_OUTPUT_STATIC)
	c++ -o $(TOOL_OUTPUT_DETECTSCANNERS) $(OBJECTS_DETECTSCANNERS) $(LIBRARY_OUTPUT_STATIC)

clean: 
	rm -f $(LIBRARY_OUTPUT_STATIC) $(LIBRARY_OUTPUT_SO) $(TOOL_OUTPUT_DEVICES) $(TOOL_OUTPUT_READBARCODES) $(TOOL_OUTPUT_DETECTSCANNERS)
	rm -f $(OBJECTS_LIBRARY) $(OBJECTS_DEVICES) $(OBJECTS_READBARCODES) $(OBJECTS_DETECTSCANNERS)


