#include "WeatherMenuUI.h"
#include <DHT.h>
#include <NTPClient.h>
#include "../utils/weather.h"
#include "../icon/systemicon.h"
#include "../button/button.h"
#include "SystemInfoMenuUI.h"

extern DHT dht;
extern NTPClient timeClient;
extern Weather weather;
extern Button buttonL;
extern Button buttonC;
extern Button buttonR;
// extern Button buttonUser;

// 天气菜单
WeatherMenuUI::WeatherMenuUI() :
  UIInterface()
{
  
}

void WeatherMenuUI::enter()
{
  UIInterface::enter();

  clearDisplay();
  showPicture(40, 0, 48, 48, systemIcon48X48[SYSTEM_ICON_WEATHER]);
  setXY(40, 48);
  setFont(OLED_FONT_12X6);
  printf("Weather");

  Serial.println("Weather ui enter!");
}

int WeatherMenuUI::event(const KEventCode& event)
{
  switch (K_EVENT_CLASS(event))
  {
  case K_EVENT_CLASS_KEY:
    if(K_EVENT_DATA(event) == K_EVENT_KEY_LEFT) {
      nextWidget = UI_INDEX_MENU_SYSTEM_INFO;
      break;
    }

    if(K_EVENT_DATA(event) == K_EVENT_KEY_RIGHT) {
      nextWidget = UI_INDEX_MAIN_UI;
      break; 
    }

    if(K_EVENT_DATA(event) == K_EVENT_KEY_OK) {
      nextWidget = UI_INDEX_WEATHER_UI;
      break;
    }
    break;
  case K_EVENT_CLASS_TICK_ONCE:
    // updateDisplay();
    break;
  }

  return KWidget::event(event);
}

// void WeatherMenuUI::updateDisplay()
// {
// }
