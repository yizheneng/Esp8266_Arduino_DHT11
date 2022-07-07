#include "adckeys.h"
#include <Arduino.h>

#define NO_KEY -1
#define DELAY_TIME 200 //ms

AdcKeys::AdcKeys(int adcPin) :
    adcPin(adcPin)
{
    delaytime = millis();
}

AdcKeys::~AdcKeys()
{
}

int AdcKeys::getPinNum()
{
    if((millis() - delaytime) < DELAY_TIME) {
        return NO_KEY;
    }

    int val = analogRead(adcPin);
    // Serial.print("Adc value:");
    // Serial.print(val, 10);
    // Serial.println("");

    if(val < 100) {
        delaytime = millis();
        return 0;
    }

    return NO_KEY;
}