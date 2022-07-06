#ifndef _SYSTEM_INFO_MENU_UI_H_
#define _SYSTEM_INFO_MENU_UI_H_
#include "../displayDrivers/UIInterface.h"

class SystemInfoMenuUI : public UIInterface {
public:
  SystemInfoMenuUI();

  void enter();      // 切换界面时，会调用此函数
  void updateDisplay();
  int event(const KEventCode&);
private:
  
};

#endif
