stdbar 1.0.0 - Library for reading barcode scanner input


1. License
   -------
    This file is part of lib_stdbar.
    
    lib_stdbar is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    lib_stdbar is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    
    You should have received a copy of the GNU General Public License
    along with lib_stdbar.  If not, see <http://www.gnu.org/licenses/>.


2. Getting support / corporate accounts
   ------------------------------------
	If you are a corporate user and need to get support or want stuff in this 
	library developed, you can get pricing information and an estimate by sending 
	your request to git-contact@eulerpfad.com .
	
    If you want to use our software but don't want to write the code yourself, we
    can offer you help. We develop your individual software, adjusted to your
    needs and integrated in your software sollutions so feel free to ask for
    an estimate.


3. About stdbar
   ------------
	The stdbar library is a C-Library for reading input from BARCODE scanners. 
	Most people do that by speculating that the scanner behaves like a keyboard sending 
	scancodes. The downside of this method of reading the codes is, that all barcode 
	scanner input always goes in your stdin. So you can not controll the software while 
	scanning. If you're for example in a menu, scanning might trigger some actions 
	that are unwanted. Using stdbar, all barcode scanner input comes on a seperate channel 
	and can thus be read where it belongs by an application.

4. Naming
   ------
	The name was given, cause the barcode input does not come from stdin but in a 
	seperate channel, which could be named as stdbar. The name was given by Saij. 

5. State
   ----- 
	The library is still under development. Currently Linux 2.6 / 3 is supported (evdev 
	needed). For barcode formats, we support EAN13 and any barcode read by a scanner 
	that was terminated by a return scancode. More to come.

6. Future
   ------
	For the future we want to implement barcode scanner detection, plug and play, 
	more barcode formats.


