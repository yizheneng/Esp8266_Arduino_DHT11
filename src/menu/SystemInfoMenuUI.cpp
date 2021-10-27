#include "SystemInfoMenuUI.h"
#include "../icon/systemicon.h"
#include "../button/button.h"
extern Button buttonL;
extern Button buttonC;
extern Button buttonR;
extern Button buttonUser;

// 主界面
SystemInfoMenuUI::SystemInfoMenuUI() :
  UIInterface()
{
  painter.showPicture(40, 0, 48, 48, systemIcon48X48[SYSTEM_ICON_INFO]);
  painter.setXY(30, 48);
  painter.setFont(OLED_FONT_12X6);
  painter.printf("System Info");
}

void SystemInfoMenuUI::enter()
{
  
}

int8_t SystemInfoMenuUI::tickOnce()
{
  switch (buttonUser.pressStatus())
  {
  case PRESS_STATUS_SHORT_PRESS:
    return UI_INDEX_MENU_SETTINGS_UI;
    break;
  case PRESS_STATUS_LONG_PRESS:
    return UI_INDEX_MENU_WEATHER;
    break;
  }

  return -1;
}
