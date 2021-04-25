#include <Arduino.h>
#include "lcd/lcd.h"
#include "ToF/tof.h"
#include "SPI.h"

lcd* mylcd;
tof* mytof;

void setup() {
  mylcd = new lcd();
  mytof = new tof(tof_scl, tof_sda);
}

void loop() {
  // put your main code here, to run repeatedly:
}