#include "MainUI.h"
#include <DHT.h>
#include <NTPClient.h>
#include "weather.h"
#include "weathericon.h"

extern DHT dht;
extern NTPClient timeClient;
extern Weather weather;

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
  
  return -1;
}
