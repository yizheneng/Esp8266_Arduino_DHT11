#include "SystemInfoMenuUI.h"
#include "../icon/systemicon.h"
#include "../button/button.h"
#include <Arduino.h>

// 主界面
SystemInfoMenuUI::SystemInfoMenuUI() :
  UIInterface()
{
  
}

void SystemInfoMenuUI::enter()
{
  UIInterface::enter();

  clearDisplay();
  showPicture(40, 0, 48, 48, systemIcon48X48[SYSTEM_ICON_INFO]);
  setXY(30, 48);
  setFont(OLED_FONT_12X6);
  printf("System Info");
}

int SystemInfoMenuUI::event(const KEventCode& event)
{
  switch (K_EVENT_CLASS(event))
  {
  case K_EVENT_CLASS_KEY:
    if(K_EVENT_DATA(event) == K_EVENT_KEY_LEFT) {
      nextWidget = UI_INDEX_MENU_SETTINGS_UI;
      break;
    }

    if(K_EVENT_DATA(event) == K_EVENT_KEY_OK) {
      nextWidget = UI_INDEX_SYSTEM_INFO_UI;
      break;
    }

    if(K_EVENT_DATA(event) == K_EVENT_KEY_RIGHT) {
      nextWidget = UI_INDEX_MENU_WEATHER;
      break;
    }
    break;
  case K_EVENT_CLASS_TICK_ONCE:
    updateDisplay();
    break;
  }

  return 0;
}

void SystemInfoMenuUI::updateDisplay()
{

}
