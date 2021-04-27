#include "SystemInfoUI.h"
#include <DHT.h>
#include <NTPClient.h>
#include "weather.h"
#include "weathericon.h"
#include "button.h"
#include <ESP8266WiFi.h>

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
}

int8_t SystemInfoUI::tickOnce()
{
  painter.setXY(0, 42);
  painter.printf("SSID:%s\r\n", WiFi.SSID().c_str());
  painter.printf("IP:%s", WiFi.localIP().toString().c_str());

  if(buttonC.isClicked()) {
    return UI_INDEX_MENU_SYSTEM_INFO;
  } 

  return -1;
}
