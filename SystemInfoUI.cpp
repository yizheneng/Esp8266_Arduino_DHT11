#include "SystemInfoUI.h"
#include <DHT.h>
#include <NTPClient.h>
#include "weather.h"
#include "weathericon.h"
#include "button.h"

extern DHT dht;
extern NTPClient timeClient;
extern Weather weather;
extern Button buttonL;
extern Button buttonC;
extern Button buttonR;

// 主界面
SystemInfoUI::SystemInfoUI() :
  UIInterface()
{
}

void SystemInfoUI::enter()
{
  
}

int8_t SystemInfoUI::tickOnce()
{
  painter.clearDisplay();
  painter.setXY(0, 0);
  painter.setFontSize(OLED_FONT_12X6);
  painter.setDisplayMode(0);
  painter.printf("     System Info     ");

  painter.setFontSize(OLED_FONT_8X6);
  painter.setDisplayMode(1);
  painter.setXY(0, 18);
  painter.printf("Model:ESP12(esp8266)\r\n");
  painter.printf("Flash Size:32Mbit\r\n");
  painter.printf("Memory Size:4Mbit\r\n");
  painter.printf("Processor:32-bit RISC\r\n");
  
  if(buttonL.isClicked()) {
    return UI_INDEX_WEATHER_UI;
  } 

  if(buttonR.isClicked()) {
    return UI_INDEX_MAIN_UI;
  }

  return -1;
}
