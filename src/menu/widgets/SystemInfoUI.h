#ifndef _SYSTEM_INFO_UI_H_
#define _SYSTEM_INFO_UI_H_
#include "../../displayDrivers/UIInterface.h"

class SystemInfoUI : public UIInterface {
public:
  SystemInfoUI();

  void enter();      // 切换界面时，会调用此函数
  void updateDisplay();
  int event(const KEventCode&);
private:
  
};

#endif
