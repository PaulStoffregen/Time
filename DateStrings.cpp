/* DateStrings.cpp
 * Definitions for date strings for use with the Time library
 *
 * Updated for Arduino 1.5.7 18 July 2014
 *
 * No memory is consumed in the sketch if your code does not call any of the string methods
 * You can change the text of the strings, make sure the short strings are each exactly 3 characters
 * the long strings can be any length up to the constant dt_MAX_STRING_LEN defined in TimeLib.h
 *
 */

#if defined(__AVR__)
#include <avr/pgmspace.h>
#else
// for compatiblity with Arduino Due and Teensy 3.0 and maybe others?
#define PROGMEM
#define PGM_P  const char *
#define pgm_read_byte(addr) (*(const unsigned char *)(addr))
#define pgm_read_word(addr) (*(const unsigned char **)(addr))
#if defined(ESP8266) || defined(ARDUINO_ARCH_ESP32)
#ifndef strcpy_P
#define strcpy_P(dest, src) strcpy((dest), (src))
#endif
#endif
#endif
#include <string.h> // for strcpy_P or strcpy
#include "TimeLib.h"
#include "Translation.h"

static char buffer[dt_MAX_STRING_LEN+1];  // must be big enough for longest string and the terminating null

/* functions to return date strings */

char* monthStr(uint8_t month)
{
    strcpy_P(buffer, (PGM_P)pgm_read_word(&(monthTable[month])));
    return buffer;
}

char* monthShortStr(uint8_t month)
{
   strcpy_P(buffer, (PGM_P)pgm_read_word(&(monthShortTable[month])));
   return buffer;
}

char* dayStr(uint8_t day)
{
   strcpy_P(buffer, (PGM_P)pgm_read_word(&(dayOfWeekTable[day])));
   return buffer;
}

char* dayShortStr(uint8_t day)
{
   strcpy_P(buffer, (PGM_P)pgm_read_word(&(dayOfWeekShortTable[day])));
	 return buffer;
}
