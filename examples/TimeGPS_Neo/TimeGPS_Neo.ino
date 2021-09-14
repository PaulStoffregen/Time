/*
   TimeGPS_Neo.ino

   Example written by Richard Teel with printDigits & digitalClockDisplay from TimeGPS example
   Hardware used
    Teensy 2.0 https://www.pjrc.com/store/teensy.html
    Sparkfun GPS GP-735 https://www.sparkfun.com/products/13670

   NOTE: The time remains in UTC. You may use adjustTime to change to local time.

   Sample Output
    ...\TimeGPS_Neo.ino: started
    Time set from GPS to: 9-13-2021 23:51:22
    Time set from GPS to: 9-13-2021 23:51:52
    Time set from GPS to: 9-13-2021 23:52:22
    Time set from GPS to: 9-13-2021 23:52:51
    Time set from GPS to: 9-13-2021 23:53:22
    Time set from GPS to: 9-13-2021 23:53:52
    Time set from GPS to: 9-13-2021 23:54:22
    Time set from GPS to: 9-13-2021 23:54:51

*/

#include <NMEAGPS.h>
#include <GPSport.h>
#include <TimeLib.h>

/***********/
/*   GPS   */
/***********/
NMEAGPS  gps; // This parses the GPS characters
gps_fix  fix; // This holds on to the latest values

// Debug function to print the date and time
void printDigits(int digits) {
  // utility function for digital clock display: prints preceding colon and leading 0
  Serial.print(":");
  if (digits < 10)
    Serial.print('0');
  Serial.print(digits);
}

void digitalClockDisplay() {
  // digital clock display of the time
  Serial.print(month());
  Serial.print("-");
  Serial.print(day());
  Serial.print("-");
  Serial.print(year());
  Serial.print(" ");
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.println();
}

void setup() {
  Serial.begin(9600);

  // Wait for a serial connection
  while (!Serial)
    ;

  // Print the sketch file path and name
  Serial.print(F(__FILE__));
  Serial.println( F(": started") );

  // For demonstration purposes, set the time sync interval to 30 seconds
  // It is recommended to leave at the default 300 seconds
  setSyncInterval(30);

  // GPS
  gpsPort.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  while (gps.available( gpsPort )) {
    fix = gps.read();
  }

  // Set the time
  if (timeStatus() != timeSet) {
    if (fix.valid.time && fix.valid.date) {
      setTime(fix.dateTime.hours, fix.dateTime.minutes, fix.dateTime.seconds, fix.dateTime.date, fix.dateTime.month, fix.dateTime.full_year());
      if (Serial) {
        Serial.print(F("Time set from GPS to: "));
        digitalClockDisplay();
      }
    }
  }
}