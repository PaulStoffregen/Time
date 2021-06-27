#include <Time.h>
#include <TimeLib.h>

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("Hours Passed: ");
  Serial.println(timerHour());
  
  Serial.print("Minutes Passed:");
  Serial.println(timerMin());
  
  Serial.print("Seconds Passed:");
  Serial.println(timerSecond());
  
  Serial.print("Millis Passed:");
  Serial.println(timerNow());
  
  Serial.println();
  delay(1000);
}
