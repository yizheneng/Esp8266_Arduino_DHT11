#include "SettingsMenuUI.h"
#include "../icon/systemicon.h"
#include "../button/button.h"
extern Button buttonL;
extern Button buttonC;
extern Button buttonR;
// extern Button buttonUser;

// 主界面
SettingsMenuUI::SettingsMenuUI() :
  UIInterface()
{
  
}

void SettingsMenuUI::enter()
{
  UIInterface::enter();
  clearDisplay();

  showPicture(40, 0, 48, 48, systemIcon48X48[SYSTEM_ICON_SETTINGS]);
  setXY(40, 48);
  setFont(OLED_FONT_12X6);
  printf("Settings");
}

int SettingsMenuUI::event(const KEventCode& event)
{
  switch (K_EVENT_CLASS(event))
  {
  case K_EVENT_CLASS_KEY:
    if(K_EVENT_DATA(event) == K_EVENT_KEY_LEFT) {
      nextWidget = UI_INDEX_MAIN_UI;
      break;
    }

    if(K_EVENT_DATA(event) == K_EVENT_KEY_OK) {
      nextWidget = UI_INDEX_SETTINGS_UI;
      break;
    }
    break;
  case K_EVENT_CLASS_TICK_ONCE:
    updateDisplay();
    break;
  }

  return KWidget::event(event);
}

void SettingsMenuUI::updateDisplay()
{
}
