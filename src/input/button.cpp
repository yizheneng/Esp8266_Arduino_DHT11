#include "button.h"
#include <Arduino.h>

Button::Button(int pin) :
  pin(pin),
  lastResult(false),
  lastReadTime(0)
{
  pinMode(pin, INPUT_PULLUP);
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
    if((millis() - lastReadTime) < 300) { // 小于300ms认为是抖动
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

PressStatus Button::pressStatus() {
  bool result = isPressed();

  if(result) {
    if(!lastResult) {
      lastReadTime = millis ();
      lastResult = true;
    }
    return PRESS_STATUS_PRESSING;
  } else {
    if(lastResult) {
      if((millis() - lastReadTime) < 300) { // 小于300ms认为是抖动
        return PRESS_STATUS_PRESSING;
      } else if((millis() - lastReadTime) > 1000) {
        lastResult = false;
        return PRESS_STATUS_LONG_PRESS;
      } else {
        lastResult = false;
        return PRESS_STATUS_SHORT_PRESS;
      }
    }
    return PRESS_STATUS_NO_PRESS;
  }
}
