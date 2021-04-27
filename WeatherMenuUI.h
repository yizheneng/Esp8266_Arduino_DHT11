#ifndef _WEATHER_MENU_UI_H_
#define _WEATHER_MENU_UI_H_
#include "UIInterface.h"

class WeatherMenuUI : public UIInterface {
public:
  WeatherMenuUI();

  void enter();      // 切换界面时，会调用此函数
  int8_t tickOnce(); // 定时调用该接口用于刷新界面逻辑,当前界面需要退出时，将返回要进入的界面ID即可，不需退出时，则返回-1
private:
  
};

#endif
