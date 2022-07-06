#include "usboutpower.h"
#include <Arduino.h>

UsboutPower::UsboutPower(uint8_t controlPin) 
{
    pinMode(controlPin, OUTPUT);
    digitalWrite(controlPin, LOW);
}

UsboutPower::~UsboutPower()
{
}

void UsboutPower::tickOnce()
{

}