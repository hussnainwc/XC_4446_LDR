#include <Arduino.h>
#include "XC-4446_LDR.h"

int pin = 0; // specify analog pin you wish to read from
XC_4446 ldr(pin);

void setup() {
  Serial.begin(9600);
  ldr.begin();
  ldr.SetRange(15); // will set a range of 15 percent +- from initial reading.
  ldr.SetSampleSize(3); // sample size 3.
  ldr.SetSampleInterval(50); // sample interval 50 milliseconds/
}

void loop() {
  ldr.SafeReadLux(true);
  delay(850); // since default interval is 50 milliseconds and sample size is 3.
              //delay of 850 milliseconds is used to get 1 second delays.
}
