#ifndef _SETTINGS_MENU_UI_H_
#define _SETTINGS_MENU_UI_H_
#include "../displayDrivers/UIInterface.h"

class SettingsMenuUI : public UIInterface {
public:
  SettingsMenuUI();

  void enter();      // 切换界面时，会调用此函数
  void updateDisplay();
  int event(const KEventCode&);
private:
  
};

#endif
