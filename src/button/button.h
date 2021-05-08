#ifndef _BUTTON_H_
#define _BUTTON_H_

class Button {
public:
  Button(int pin);

  bool isPressed();

  bool isClicked();
private:
  int pin;
  bool lastResult;
  int lastReadTime;
};

#endif
