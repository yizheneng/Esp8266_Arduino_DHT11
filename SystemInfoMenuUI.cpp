#include "SystemInfoMenuUI.h"
#include <DHT.h>
#include <NTPClient.h>
#include "systemicon.h"
#include "button.h"

extern DHT dht;
extern NTPClient timeClient;
extern Button buttonL;
extern Button buttonC;
extern Button buttonR;


// 主界面
SystemInfoMenuUI::SystemInfoMenuUI() :
  UIInterface()
{
  painter.showPicture(40, 0, 48, 48, systemIcon48X48[SYSTEM_ICON_INFO]);
  painter.setXY(30, 48);
  painter.setFontSize(OLED_FONT_12X6);
  painter.printf("System Info");
}

void SystemInfoMenuUI::enter()
{
  
}

int8_t SystemInfoMenuUI::tickOnce()
{
  if(buttonC.isClicked()) {
    return UI_INDEX_SYSTEM_INFO_UI;
  }

  if(buttonL.isClicked()) {
    return UI_INDEX_MENU_WEATHER;
  }

  // if(buttonR.isClicked()) {
  //   return UI_INDEX_MAIN_UI;
  // }

  return -1;
}
