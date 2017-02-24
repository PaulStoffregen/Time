/* 
 * TimeConversion.ino
 *
 * This program demonstrates one way to use the time conversion <ConvertTime.h> part of the library, 
 * to allow you to easily handle timezones and daylight savings time, and make printing much simpler.
 * 
 * To customize the timezone, edit the UTC_OFFSET value. 
 * To enable automatic daylight saving time calculations, uncomment the corresponding daylight 
 * savings blocks.
 * 
 * This uses the same code as the TimeSerial example to synchronize the time.
 * A Processing example sketch to automatically send the messages is included in the download
 * On Linux, you can use "date +T%s\n > /dev/ttyACM0" (UTC time zone)
 */ 


// change this to the UTC offset of the timezone you want:
// for reference here are the USA offset values:
// PST = -8, MST = -7, CST = -6, EST = -5
#define UTC_OFFSET -7 

// Uncomment one of these blocks to enable daylight savings time calculations:
// For USA daylight savings:

//#include <util/usa_dst.h>
//#define DST usa_dst;

// For european daylight savings:

//#include <util/eur_dst.h>
//#define DST eur_dst;



 
#include <time.h>

#include <Time.h>
#include <ConvertTime.h>
#include <Wire.h>
#include <DS1307RTC.h>  // a basic DS1307 library that returns time as a time_t


void setup() {
  Serial.begin(9600);
  while (!Serial) ; // Needed for Leonardo only
  
  Serial.println("Waiting for sync message");

  #ifdef DST // set daylight savings if configured.
  set_dst(DST);
  #endif
  
  set_zone(UTC_OFFSET * SECS_PER_HOUR); //set timezone offset
  
}

void loop() {
  // Serial clock synchronization routine. See the TimeSerial example for an explanation of how this works.
  if (Serial.available()) {
    processSyncMessage();
  }
  
  if (timeStatus()!= timeNotSet) {
    digitalClockDisplay();  
  }
  
  delay(1000);
}


void digitalClockDisplay() {
  time_t libtime = now(); // get the current time according to LibTime.
  time_t timeh = convertToTimeH(libtime); // time.h uses a different format, so have to convert.
  String str = ctime(&timeh); // but once we have it there, it only takes one line to turn it into a string.
  // You can also easily do custom time formats using the 'strftime', although it's a bit more complicated to use.
  Serial.println(str); // and print that time.
}



#define TIME_HEADER  "T"   // Header tag for serial time sync message

// Serial clock synchronization routine. See the TimeSerial example to see how this works.
void processSyncMessage() { 
  unsigned long pctime;
  const unsigned long DEFAULT_TIME = 1357041600; // Jan 1 2013

  if(Serial.find(TIME_HEADER)) {
     pctime = Serial.parseInt();
     if( pctime >= DEFAULT_TIME) { // check the integer is a valid time (greater than Jan 1 2013)
       setTime(pctime); // Sync Arduino clock to the time received on the serial port
     }
  }
}





