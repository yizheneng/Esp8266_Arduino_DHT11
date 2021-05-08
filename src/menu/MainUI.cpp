#include "MainUI.h"
#include <DHT.h>
#include <NTPClient.h>
#include "../weather/weather.h"
#include "../icon/weathericon.h"
#include "../button/button.h"

extern DHT dht;
extern NTPClient timeClient;
extern Weather weather;
extern Button buttonL;
extern Button buttonC;
extern Button buttonR;

// 主界面
MainUI::MainUI() :
  UIInterface()
{
}

void MainUI::enter()
{
  
}

int8_t MainUI::tickOnce()
{
  if(weather.isUpdated()) {
    painter.clearDisplay();
    painter.showPictureInFlash(0, 0, 32, 32, picture32X32[weather.getWeathers()[0].weatherIconCode]);
  } else {
    painter.setXY(0, 0);
    painter.setFontSize(OLED_FONT_24X12);
    painter.showString("Waiting...");
  }
  
  painter.setFontSize(OLED_FONT_16X8);
  painter.setXY(32, 0);
  painter.printf("  %s", timeClient.getFormattedTime().c_str());
  painter.setXY(32, 16);
  painter.printf(" 2020-04-05");
  painter.setXY(0, 32);
  painter.printf("LOW:%d  HIGH:%d", weather.getWeathers()[0].lowTemp, weather.getWeathers()[0].highTemp);
  painter.setXY(0, 48);
  painter.printf("TEMP:%d  HUM:%d", (int)dht.readTemperature(), (int)dht.readHumidity());

  if(buttonR.isClicked()) {
    return UI_INDEX_MENU_WEATHER;
  }

   if(buttonL.isClicked()) {
    return UI_INDEX_MENU_SYSTEM_INFO;
  } 

  return -1;
}
