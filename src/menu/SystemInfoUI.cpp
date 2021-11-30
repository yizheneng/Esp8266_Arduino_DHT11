#include "SystemInfoUI.h"
#include <DHT.h>
#include <NTPClient.h>
#include "../button/button.h"
#include <ESP8266WiFi.h>

extern DHT dht;
extern NTPClient timeClient;
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
  clearDisplay();
  setXY(0, 0);
  setFont(OLED_FONT_12X6);
  setDisplayMode(0);
  printf("     System Info     ");

  setFont(OLED_FONT_8X6);
  setDisplayMode(1);
  setXY(0, 18);
  printf("Model:ESP12(esp8266)\r\n");
  printf("Flash Size:32Mbit\r\n");
  printf("Memory Size:4Mbit\r\n");
}

int8_t SystemInfoUI::tickOnce()
{
  setXY(0, 42);
  printf("SSID:%s\r\n", WiFi.SSID().c_str());
  printf("IP:%s", WiFi.localIP().toString().c_str());

  if(buttonC.isClicked()) {
    return UI_INDEX_MENU_SYSTEM_INFO;
  } 

  return -1;
}
