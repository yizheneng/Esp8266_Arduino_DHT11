#include "WeatherUI.h"
#include <DHT.h>
#include <NTPClient.h>
#include "../utils/weather.h"
#include "../icon/weathericon.h"
#include "../button/button.h"

extern DHT dht;
extern NTPClient timeClient;
extern Weather weather;
// extern Button buttonUser;


// 主界面
WeatherUI::WeatherUI() :
  UIInterface()
{
}

void WeatherUI::enter()
{
    UIInterface::enter();
}

int WeatherUI::event(const KEventCode& event)
{
  switch (K_EVENT_CLASS(event))
  {
  case K_EVENT_CLASS_KEY:
    if(K_EVENT_DATA(event) == K_EVENT_KEY_OK) {
      nextWidget = UI_INDEX_MENU_WEATHER;
      break;
    }
    break;
  case K_EVENT_CLASS_TICK_ONCE:
    updateDisplay();
    break;
  }

  return KWidget::event(event);
}

void WeatherUI::updateDisplay()
{
  clearDisplay();
  setXY(0, 0);
  setFont(OLED_FONT_12X6);
  setDisplayMode(0);
  printf("       Weather       ");

  if(weather.isUpdated()) {
    showPictureInFlash(0, 16, 32, 32, picture32X32[weather.getWeathers()[0].weatherIconCode]);
    showPictureInFlash(32 + 16, 16, 32, 32, picture32X32[weather.getWeathers()[1].weatherIconCode]);
    showPictureInFlash(32 + 16 + 32 + 16, 16, 32, 32, picture32X32[weather.getWeathers()[2].weatherIconCode]);

    setDisplayMode(1);
    setFont(OLED_FONT_8X6);
    setXY(0, 48);
    printf("L:%d\r\nH:%d", weather.getWeathers()[0].lowTemp, weather.getWeathers()[0].highTemp);

    setXY(32 + 16, 48);
    printf("L:%d", weather.getWeathers()[1].lowTemp);
    setXY(32 + 16, 56);
    printf("H:%d", weather.getWeathers()[1].highTemp);

    setXY(32 + 16 + 32 + 16, 48);
    printf("L:%d", weather.getWeathers()[2].lowTemp);
    setXY(32 + 16 + 32 + 16, 56);
    printf("H:%d", weather.getWeathers()[2].highTemp);
  } else {
    setDisplayMode(1);
    setXY(0, 16);
    setFont(OLED_FONT_24X12);
    showString("Waiting...");
  }
}
