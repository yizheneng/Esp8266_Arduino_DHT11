#include "MainUI.h"
#include <DHT.h>
#include <time.h>
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
extern Button buttonUser;

// 主界面
MainUI::MainUI() :
  UIInterface()
{
}

void MainUI::enter()
{
  
}

static const uint8_t MONS[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};//平年
static const uint8_t LEAPMONS[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};//闰年

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

  time_t rawtime = timeClient.getEpochTime();
  struct tm *info;
  info = localtime( &rawtime );
  
  painter.setFontSize(OLED_FONT_16X8);
  painter.setXY(32, 0);
  painter.printf("  %02d:%02d:%02d", info->tm_hour, info->tm_min, info->tm_sec);
  painter.setXY(32, 16);

  painter.printf(" %04d-%02d-%02d", info->tm_year + 1900, info->tm_mon + 1, info->tm_mday);
  painter.setXY(0, 32);
  painter.printf("LOW:%d  HIGH:%d", weather.getWeathers()[0].lowTemp, weather.getWeathers()[0].highTemp);
  painter.setXY(0, 48);
  painter.printf("TEMP:%d  HUM:%d", (int)dht.readTemperature(), (int)dht.readHumidity());

  switch (buttonUser.pressStatus())
  {
  case PRESS_STATUS_SHORT_PRESS:
    return UI_INDEX_MENU_WEATHER;
    break;
  case PRESS_STATUS_LONG_PRESS:
    return UI_INDEX_MENU_SETTINGS_UI;
    break;
  }

  return -1;
}
