#ifndef _WEATHER_MENU_UI_H_
#define _WEATHER_MENU_UI_H_
#include "../displayDrivers/UIInterface.h"

class WeatherMenuUI : public UIInterface {
public:
  WeatherMenuUI();

  void enter();      // 切换界面时，会调用此函数
  // void updateDisplay();
  int event(const KEventCode&);
private:
  
};

#endif
