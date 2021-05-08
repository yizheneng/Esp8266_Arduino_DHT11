#include "WeatherMenuUI.h"
#include <DHT.h>
#include <NTPClient.h>
#include "weather.h"
#include "systemicon.h"
#include "button.h"
#include "SystemInfoMenuUI.h"

extern DHT dht;
extern NTPClient timeClient;
extern Weather weather;
extern Button buttonL;
extern Button buttonC;
extern Button buttonR;


// 天气菜单
WeatherMenuUI::WeatherMenuUI() :
  UIInterface()
{
  painter.showPicture(40, 0, 48, 48, systemIcon48X48[SYSTEM_ICON_WEATHER]);
  painter.setXY(40, 48);
  painter.setFontSize(OLED_FONT_12X6);
  painter.printf("Weather");
}

void WeatherMenuUI::enter()
{
  
}

int8_t WeatherMenuUI::tickOnce()
{
  if(buttonL.isClicked()) {
    return UI_INDEX_MAIN_UI;
  } 

  if(buttonR.isClicked()) {
    return UI_INDEX_MENU_SYSTEM_INFO;
  } 

  if(buttonC.isClicked()) {
    return UI_INDEX_WEATHER_UI;
  } 
  return -1;
}
