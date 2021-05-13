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
  painter.clearDisplay();
  painter.setXY(0, 0);
  painter.setFontSize(OLED_FONT_12X6);
  painter.setDisplayMode(0);
  painter.printf("      Settings     ");
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
  painter.setFontSize(OLED_FONT_8X6);
  painter.setDisplayMode(1);
  painter.setXY(0, 18);
  painter.printf("  Wifi Settings\r\n");
  painter.printf("  Time Settings\r\n");
  painter.printf("  Local Settings\r\n");
  painter.printf("  Exit\r\n");

  painter.drawCircle(5, 18 + currentIdex * 8 + 4, 3);
}

