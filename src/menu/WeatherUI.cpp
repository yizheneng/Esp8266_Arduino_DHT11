#include "WeatherUI.h"
#include <DHT.h>
#include <NTPClient.h>
#include "../utils/weather.h"
#include "../icon/weathericon.h"
#include "../button/button.h"

extern DHT dht;
extern NTPClient timeClient;
extern Weather weather;
extern Button buttonUser;


// 主界面
WeatherUI::WeatherUI() :
  UIInterface()
{
}

void WeatherUI::enter()
{
  
}

int8_t WeatherUI::tickOnce()
{
  painter.clearDisplay();
  painter.setXY(0, 0);
  painter.setFont(OLED_FONT_12X6);
  painter.setDisplayMode(0);
  painter.printf("       Weather       ");

  if(weather.isUpdated()) {
    painter.showPictureInFlash(0, 16, 32, 32, picture32X32[weather.getWeathers()[0].weatherIconCode]);
    painter.showPictureInFlash(32 + 16, 16, 32, 32, picture32X32[weather.getWeathers()[1].weatherIconCode]);
    painter.showPictureInFlash(32 + 16 + 32 + 16, 16, 32, 32, picture32X32[weather.getWeathers()[2].weatherIconCode]);

    painter.setDisplayMode(1);
    painter.setFont(OLED_FONT_8X6);
    painter.setXY(0, 48);
    painter.printf("L:%d\r\nH:%d", weather.getWeathers()[0].lowTemp, weather.getWeathers()[0].highTemp);

    painter.setXY(32 + 16, 48);
    painter.printf("L:%d", weather.getWeathers()[1].lowTemp);
    painter.setXY(32 + 16, 56);
    painter.printf("H:%d", weather.getWeathers()[1].highTemp);

    painter.setXY(32 + 16 + 32 + 16, 48);
    painter.printf("L:%d", weather.getWeathers()[2].lowTemp);
    painter.setXY(32 + 16 + 32 + 16, 56);
    painter.printf("H:%d", weather.getWeathers()[2].highTemp);
  } else {
    painter.setDisplayMode(1);
    painter.setXY(0, 16);
    painter.setFont(OLED_FONT_24X12);
    painter.showString("Waiting...");
  }
  
  switch (buttonUser.pressStatus())
  {
  case PRESS_STATUS_SHORT_PRESS:
    return UI_INDEX_MENU_WEATHER;
    break;
  }

  return -1;
}
