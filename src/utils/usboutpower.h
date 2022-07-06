#ifndef _USB_POWER_H_
#define _USB_POWER_H_
#include <stdint.h>

class UsboutPower
{
public:
    UsboutPower(uint8_t controlPin);
    ~UsboutPower();

    void tickOnce();
private:
    uint8_t controlPin;
};




#endif
