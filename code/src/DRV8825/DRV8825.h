#ifndef DRV8825_h
#define DRV8825_h

#include <Arduino.h>

#define Enable PA3  // GPIO pin number pick any you want
#define Step PA4 // GPIO pin number pick any you want
#define Dir PA5  // GPIO pin number pick any you want

class DRV8825
{
private:
public:
    DRV8825();
    void run();
};

#endif
