#include <Time.h>
#include <TimeLib.h>


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(11,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("Time Since Last Reset:" );
  Serial.print(timerNow());
  Serial.print(",");
  Serial.println(millis());
  
  if (digitalRead(11)){
    Serial.print("Reset");
    timerReset();
    }
    
    delay(500);
  
}
