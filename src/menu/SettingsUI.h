#ifndef _SETTINGS_UI_H_
#define _SETTINGS_UI_H_
#include "../displayDrivers/UIInterface.h"

enum  SettingsUIState {
  SETTINGS_UI_STATE_WIFI_SETTINGS = 0, // WIFI 配置
  SETTINGS_UI_STATE_TIME_SETTINGS,     // 时间配置
  SETTINGS_UI_STATE_LOCAL_SETTINGS,    // 时区配置
  SETTINGS_UI_STATE_EXIT,              // 退出
  SETTINGS_UI_STATE_MAX
};

class SettingsUI : public UIInterface {
public:
  SettingsUI();

  void enter();      // 切换界面时，会调用此函数
  int8_t tickOnce(); // 定时调用该接口用于刷新界面逻辑,当前界面需要退出时，将返回要进入的界面ID即可，不需退出时，则返回-1
private:
  void updateMenu(int currentIdex);

  int8_t state;
};

#endif
