/* DateFormats.cpp
 * Definitions for date formats for use with the Time library
 * 
 * Authors:  Domenico Monaco <hack at kiuz.it>
 * 
 * //// IMPORTANT
 * NOT TESTED FOR Arduino Due and Teensy 3.0 
 *
 */

#if ARDUINO >= 100
#include <Arduino.h> 
#else
#include <WProgram.h> 
#endif

#include <string.h> // for strcpy_P or strcpy
#include "Time.h"

/**
 * Disaply complete time with 'hh:mm:ss' format
 */
void timeComplete_Display(){
  Serial.print(hour());
  Serial.print(":");
  printDigits(minute());
  Serial.print(":");
  printDigits(second());
}

/**
 * Display Date and Time with 'YYYY-MM-DDThh:mm:ss' format
 * info: http://www.w3.org/TR/NOTE-datetime
 */
void utcFormat_Display(){
	Serial.print(year());
	Serial.print("-");
  printDigits(month());
	Serial.print("-");
  printDigits(day());
	Serial.print("T");

	timeComplete_Display();
}

/**
 * Display Date and Time with 'hh:mm:ss <CompleteNameDayWeek> dd <CompleteNameMonth> YYYY' format
 */
void longStrFormat_Display(){

	timeComplete_Display();

	Serial.print(" ");
  Serial.print(dayStr(weekday()));
  Serial.print(" ");
  Serial.print(day());
  Serial.print(" ");
  Serial.print(monthStr(month()));
  Serial.print(" ");
  Serial.print(year());
}

/**
 * Display Date and Time with 'hh:mm:ss <ShortNameDayWeek> dd <ShortNameMonth> YYYY' format
 */
void shortStrFormat_Display(){
	
	timeComplete_Display();

	Serial.print(" ");
	Serial.print(dayShortStr(weekday()));
  Serial.print(" ");
  Serial.print(day());
  Serial.print(" ");
  Serial.print(monthShortStr(month()));
  Serial.print(" ");
  Serial.print(year());
}

/**
 * utility function for digital clock display: prints preceding colon and leading 0
 */
void printDigits(int digits) {
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
}