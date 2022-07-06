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
  int event(const KEventCode& event);

private:
  void updateDisplay();

  KLabel* timeLabel;
  KLabel* dateLabel;
  KLabel* tempAndHumLabel;
  // KLabel* lowTempLabel;
  // KLabel* highTempLabel;
  // KLabel* realTempLabel;
  // KLabel* realHumLabel;
  KLabel* newsLabel;

  KImage* weatherIcon;
};

#endif
