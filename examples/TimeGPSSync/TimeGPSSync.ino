#include <Time.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

SoftwareSerial gps(3, 4); // RX, TX
TinyGPSPlus gpsEncoder;

void setup() {
  Serial.begin(9600);
  gps.begin(9600);

  setSyncProvider(&gpsTimeSync);
  setSyncInterval(5); // Seconds between re-sync
}

void loop() {
  while (gps.available() > 0) {
    gpsEncoder.encode(gps.read());
  }
  Serial.print("Now: ");
  Serial.println(now());
  delay(1000);
}

/**
 * This is the magic, we get the date/time from the GPS unit
 * and use it to convert to a time_t
 */
time_t gpsTimeSync(void) {
  tmElements_t tm;

  tm.Second = gpsEncoder.time.second();
  tm.Minute = gpsEncoder.time.minute();
  tm.Hour = gpsEncoder.time.hour();
  tm.Day = gpsEncoder.date.day();
  tm.Month = gpsEncoder.date.month();
  tm.Year = CalendarYrToTm(gpsEncoder.date.year());

  return makeTime(tm);
}
