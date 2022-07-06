#ifndef _BUTTON_H_
#define _BUTTON_H_

enum PressStatus {
  PRESS_STATUS_NO_PRESS = 0,
  PRESS_STATUS_PRESSING = 1,
  PRESS_STATUS_SHORT_PRESS = 2,
  PRESS_STATUS_LONG_PRESS  = 3,
};

class Button {
public:
  Button(int pin);

  bool isPressed();

  /**
   * 不支持长按接口
   */
  bool isClicked();

  /**
   * 长按接口
   */
  PressStatus pressStatus();
private:
  int pin;
  bool lastResult;
  int lastReadTime;
};

#endif
