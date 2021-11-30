#include "SettingsMenuUI.h"
#include "../icon/systemicon.h"
#include "../button/button.h"
extern Button buttonL;
extern Button buttonC;
extern Button buttonR;
extern Button buttonUser;

// 主界面
SettingsMenuUI::SettingsMenuUI() :
  UIInterface()
{
  showPicture(40, 0, 48, 48, systemIcon48X48[SYSTEM_ICON_SETTINGS]);
  setXY(40, 48);
  setFont(OLED_FONT_12X6);
  printf("Settings");
}

void SettingsMenuUI::enter()
{
  setFont(OLED_FONT_8X6);
  setDisplayMode(1);
  setXY(0, 18);
}

int8_t SettingsMenuUI::tickOnce()
{
  switch (buttonUser.pressStatus())
  {
  case PRESS_STATUS_SHORT_PRESS:
    return UI_INDEX_MAIN_UI;
    break;
  case PRESS_STATUS_LONG_PRESS:
    return UI_INDEX_MENU_SYSTEM_INFO;
    break;
  }

  return -1;
}
