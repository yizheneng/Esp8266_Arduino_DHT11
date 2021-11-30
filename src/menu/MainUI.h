#ifndef _MAIN_UI_H_
#define _MAIN_UI_H_
#include "../displayDrivers/UIInterface.h"
#include "../KWidgets/KWidget.h"
#include "../KWidgets/KLabel.h"
#include "../KWidgets/KImage.h"
#include "../KWidgets/KButton.h"

class MainUI : public UIInterface {
public:
  MainUI();

  void enter();      // 切换界面时，会调用此函数
  int8_t tickOnce(); // 定时调用该接口用于刷新界面逻辑,当前界面需要退出时，将返回要进入的界面ID即可，不需退出时，则返回-1
private:
  KLabel* timeLabel;
  KLabel* dateLabel;
  KLabel* lowTempLabel;
  KLabel* highTempLabel;
  KLabel* realTempLabel;
  KLabel* realHumLabel;
  KLabel* newsLabel;

  KImage* weatherIcon;
};

#endif
