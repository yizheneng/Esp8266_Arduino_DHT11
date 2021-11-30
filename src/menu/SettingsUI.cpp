#include "SettingsUI.h"
#include "../icon/systemicon.h"
#include "../button/button.h"
extern Button buttonL;
extern Button buttonC;
extern Button buttonR;

// 主界面
SettingsUI::SettingsUI() :
  UIInterface(),
  state(SETTINGS_UI_STATE_WIFI_SETTINGS)
{
}

void SettingsUI::enter()
{
  clearDisplay();
  setXY(0, 0);
  setFont(OLED_FONT_12X6);
  setDisplayMode(0);
  printf("      Settings     ");
}

int8_t SettingsUI::tickOnce()
{
  if(buttonR.isClicked()) {
    state ++;
  }

  if(buttonL.isClicked()) {
    state --;
  }

  if(state > (SETTINGS_UI_STATE_MAX - 1)) {
    state = 0;
  }

  if(state < 0) {
    state = (SETTINGS_UI_STATE_MAX - 1);
  }

  if(buttonC.isClicked()) {
    switch (state)
    {
    case SETTINGS_UI_STATE_WIFI_SETTINGS:
      break;
    case SETTINGS_UI_STATE_TIME_SETTINGS:
      break;
    case SETTINGS_UI_STATE_LOCAL_SETTINGS:
      break;
    case SETTINGS_UI_STATE_EXIT:
      return UI_INDEX_MENU_SETTINGS_UI;
      break;
    default:
      break;
    }
  }
  

  updateMenu(state);
  return -1;
}

void SettingsUI::updateMenu(int currentIdex)
{
  setFont(OLED_FONT_8X6);
  setDisplayMode(1);
  setXY(0, 18);
  printf("  Wifi Settings\r\n");
  printf("  Time Settings\r\n");
  printf("  Local Settings\r\n");
  printf("  Exit\r\n");

  drawCircle(5, 18 + currentIdex * 8 + 4, 3);
}

