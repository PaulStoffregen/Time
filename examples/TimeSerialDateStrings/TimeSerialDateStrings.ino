/* 
 * TimeSerialDateStrings.pde
 * example code illustrating Time library date strings
 *
 * This sketch adds date string functionality to TimeSerial sketch
 * Also shows how to handle different messages
 *
 * A message starting with a time header sets the time
 * A Processing example sketch to automatically send the messages is inclided in the download
 * On Linux, you can use "date +T%s\n > /dev/ttyACM0" (UTC time zone)
 *
 * A message starting with a format header sets the date format

 * send: Fs\n for short date format
 * send: Fl\n for long date format
 * send: Fu\n for UTC date format
 * 
 * Changes:
 *   - [2014-9-6, Domenico Monaco, hack@kiuz.it]
 *     - Added UTC format
 *     - Changed method to switch "format" from single boolena to ENUM variable
 *
 */ 
 
#include <Time.h>  

// single character message tags
#define TIME_HEADER   'T'   // Header tag for serial time sync message
#define FORMAT_HEADER 'F'   // Header tag indicating a date format message
#define FORMAT_SHORT  's'   // short month and day strings
#define FORMAT_LONG   'l'   // (lower case l) long month and day strings
#define FORMAT_UTC    'u'

#define TIME_REQUEST  7     // ASCII bell character requests a time sync message 

enum FORMAT {
  l,
  s,
  u
};

FORMAT formatMessage = u;

void setup()  {
  Serial.begin(9600);
  while (!Serial) ; // Needed for Leonardo only
  setSyncProvider( requestSync);  //set function to call when sync required
  Serial.println("Waiting for sync message");
}

void loop(){    
  if (Serial.available() > 1) { // wait for at least two characters
    char c = Serial.read();
    if( c == TIME_HEADER) {
      processSyncMessage();
    }
    else if( c== FORMAT_HEADER)
    {
      processFormatMessage();
    }
  }
  if (timeStatus()!= timeNotSet) {
    digitalClockDisplay();  
  }
  delay(1000);
}

void digitalClockDisplay() {
  // digital clock display of the time
  if(formatMessage==l){
    longStrFormat_Display();
  }
  else if(formatMessage==s){
    shortStrFormat_Display();
  }else{
    utcFormat_Display();
  }

  Serial.println("");
}

void  processFormatMessage() {
   char c = Serial.read();
   if( c == FORMAT_LONG){
      formatMessage = l;
      Serial.println(F("Setting long format"));
   }
   else if( c == FORMAT_SHORT) {
      formatMessage = s;   
      Serial.println(F("Setting short format"));
   }
   else if( c == FORMAT_UTC) {
      formatMessage = u;
      Serial.println(F("Setting UTC format"));
   }
}

void processSyncMessage() {
  unsigned long pctime;
  const unsigned long DEFAULT_TIME = 1357041600; // Jan 1 2013 - paul, perhaps we define in time.h?

   pctime = Serial.parseInt();
   if( pctime >= DEFAULT_TIME) { // check the integer is a valid time (greater than Jan 1 2013)
     setTime(pctime); // Sync Arduino clock to the time received on the serial port
   }
}

time_t requestSync() {
  Serial.write(TIME_REQUEST);  
  return 0; // the time will be sent later in response to serial mesg
}
