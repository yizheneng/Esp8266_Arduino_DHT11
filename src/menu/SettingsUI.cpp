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
  UIInterface::enter();

  clearDisplay();
  setXY(0, 0);
  setFont(OLED_FONT_12X6);
  setDisplayMode(0);
  printf("      Settings     ");
}

int SettingsUI::event(const KEventCode& event)
{
  switch (K_EVENT_CLASS(event))
  {
  case K_EVENT_CLASS_KEY:
    if(K_EVENT_DATA(event) == K_EVENT_KEY_LEFT) {
      state --;
    }

    if(K_EVENT_DATA(event) == K_EVENT_KEY_RIGHT) {
      state ++;
    }

    if(K_EVENT_DATA(event) == K_EVENT_KEY_OK) {
      if( state == SETTINGS_UI_STATE_EXIT) {
        nextWidget = UI_INDEX_MENU_SETTINGS_UI;
        break;
      }
    }

    updateDisplay();
    break;
  case K_EVENT_CLASS_TICK_ONCE:
    break;
  }

  return KWidget::event(event);
}

void SettingsUI::updateDisplay()
{
  if(state > (SETTINGS_UI_STATE_MAX - 1)) {
    state = 0;
  }

  if(state < 0) {
    state = (SETTINGS_UI_STATE_MAX - 1);
  }
  
  updateMenu(state);
}

void SettingsUI::updateMenu(int currentIdex)
{
  setFont(OLED_FONT_8X6);
  setDisplayMode(1);
  setXY(0, 18);
  printf("  Wifi Settings\r\n");
  setXY(0, 18 + 8);
  printf("  Time Settings\r\n");
  setXY(0, 18 + 8 + 8);
  printf("  Local Settings\r\n");
  setXY(0, 18 + 8 + 8 + 8);
  printf("  Exit\r\n");

  drawCircle(5, 18 + currentIdex * 8 + 4, 3);
}

