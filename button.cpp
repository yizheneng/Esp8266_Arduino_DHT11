#include "button.h"
#include <Arduino.h>

Button::Button(int pin) :
  pin(pin),
  lastResult(false),
  lastReadTime(0)
{
  pinMode(pin, INPUT);
  // digitalWrite(pin, HIGH);
}

bool Button::isPressed()
{
  return !digitalRead(pin);
}

bool Button::isClicked()
{
  bool result = isPressed();
  if((!lastResult) && result) {
    lastReadTime = millis ();
    lastResult = true;
    return true;
  }

  if(result && lastResult) {
    if((millis() - lastReadTime) < 300) {
      return false;
    } else {
      lastReadTime = millis ();
      lastResult = true;
      return true;
    }
  }

  lastResult = false;
  return false;
}
