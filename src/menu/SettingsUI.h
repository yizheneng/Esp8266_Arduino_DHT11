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
  void updateDisplay();
  int event(const KEventCode&);
private:
  void updateMenu(int currentIdex);

  int8_t state;
};

#endif
