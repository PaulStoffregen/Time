#include <Time.h>
#include <TimeLib.h>


void setup() {
  // put your setup code here, to run once:
pinMode(11,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  timerEvery(1000,toggle);

}

void toggle(){
  digitalWrite(11,!digitalRead(11));
  }
