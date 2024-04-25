/*
arduino_wstring_x86_64
Copyright (C) 2024 D.Salzner <mail@dennissalzner.de>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
/**
 * Very sloppy compatibility layer to be able to use WString.cpp/WString.h from the Arduino 1.8.6 AVR-Core.
 * 
 * Useful to:
 * - be able to use Arduino String libraries
 * - no need to roll an own implementation of replace, split, etc.
 * - maintain compatibility between arduino and desktop code
 * - can also provide a lean string implementation for C-only (non C) code
 *
 * To use:
 * 1. get WString.h/.cpp from Arduiono 1.8.6. AVR-Core
 * 2. comment out #include <avr/pgmspace.h>
 * 3. add #include "Arduino-WString.h" (this file) before including WString.h
 *
 * Caution:
 * - number to string are not implementated and return NULL possible wrecking havok
 * - defines can interfere with other code
 * - compiler needs to see this header first
*/
#pragma once
// ---

#include <stdio.h>
#include <stdlib.h>

#define strcpy_P strcpy
#define strlen_P strlen
//#define dtostrf atoll
#define PGM_P char*

void utoa(unsigned int val, char * buf, int base);
void ltoa(unsigned int val, char * buf, int base);
void itoa(unsigned int val, char * buf, int base);
void ultoa(unsigned int val, char * buf, int base);
char * dtostrf(double val, unsigned int, unsigned int, char * buf);

