/*
 * example code illustrating date strings library with Real Time Clock.
 *
 */

#include <TimeLib.h>
#include <Wire.h>
#include <DS1307RTC.h>  // a basic DS1307 library that returns time as a time_t

static boolean isLongFormat = true; // Change to false to get short format.

void setup()
{
  Serial.begin(9600);
  while (!Serial)   // wait until Arduino Serial Monitor opens
  {
  }
  setSyncProvider(RTC.get);   // the function to get the time from the RTC
  if(timeStatus() != timeSet)
  {
    Serial.println("Unable to sync with the RTC");
  }
  else
  {
    Serial.println("RTC has set the system time");
  }
}

void loop()
{
  if (timeStatus() == timeSet)
  {
    digitalClockDisplay();
  }
  else
  {
    Serial.println("The time has not been set.  Please run the Time");
    Serial.println("TimeRTCSet example, or DS1307RTC SetTime example.");
    Serial.println();
    delay(4000);
  }
  delay(1000);
}

void digitalClockDisplay()
{
  // digital clock display of the time
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.print(" ");
  if(isLongFormat)
  {
    Serial.print(dayStr(weekday()));
  }
  else
  {
    Serial.print(dayShortStr(weekday()));
  }
  Serial.print(" ");
  Serial.print(day());
  Serial.print(" ");
  if(isLongFormat)
  {
    Serial.print(monthStr(month()));
  }
  else
  {
    Serial.print(monthShortStr(month()));
  }
  Serial.print(" ");
  Serial.print(year());
  Serial.println();
}

void printDigits(int digits)
{
  // utility function for digital clock display: prints preceding colon and leading 0
  Serial.print(":");
  if(digits < 10)
  {
    Serial.print('0');
  }
  Serial.print(digits);
}
