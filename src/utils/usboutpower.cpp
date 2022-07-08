#include "usboutpower.h"
#include <string>
#include <Arduino.h>
#include <NTPClient.h>

#define DURATION_TIME 30 * 60 * 1000//30 // unit:min

extern NTPClient timeClient;

UsboutPower::UsboutPower(uint8_t controlPin) :
    controlPin(controlPin),
    state(false)
{
    digitalWrite(controlPin, LOW);
    pinMode(controlPin, OUTPUT);
}

UsboutPower::~UsboutPower()
{
}

void UsboutPower::tickOnce()
{
    static unsigned long startTime = 0; // 开始打开时间

    // if((millis() - startTime) > 4000) {
    //     startTime = millis();
    //     if(state) {
    //         digitalWrite(controlPin, LOW);
    //         state = false;
    //     } else {
    //         digitalWrite(controlPin, HIGH);
    //         state = true;
    //     }
    // }
    // return;

    if(state) {
        if((millis() - startTime) > DURATION_TIME) {
            digitalWrite(controlPin, LOW);
            state = false;
        }
        return;
    }

    time_t rawtime = timeClient.getEpochTime();
    struct tm *info;
    info = localtime(&rawtime);

    if((info->tm_hour == 8)
        && (info->tm_min == 0)) {
        digitalWrite(controlPin, HIGH);
        state = true;
        startTime = millis();
    }
}

bool UsboutPower::getState()
{
    return state;
}
