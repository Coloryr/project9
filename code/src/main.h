#ifndef MAIN_h
#define MAIN_h

#include <Arduino.h>
#include "lcd/lcd.h"
#include "ToF/tof.h"
#include "IO/Input.h"
#include "DRV8825/DRV8825.h"
#include "YX65491/YX65491.h"

extern lcd *mylcd;
extern tof *mytof;
extern Input *io;
extern DRV8825 *drv;
extern YX65491 *xyz;

#endif
