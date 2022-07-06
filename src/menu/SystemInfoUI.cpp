#include "SystemInfoUI.h"
#include <DHT.h>
#include <NTPClient.h>
#include "../button/button.h"
#include <ESP8266WiFi.h>
extern uint8_t cpuUsage;

// 主界面
SystemInfoUI::SystemInfoUI() :
  UIInterface()
{
}

void SystemInfoUI::enter()
{
  UIInterface::enter();
  clearDisplay();

  setXY(0, 0);
  setFont(OLED_FONT_12X6);
  setDisplayMode(0);
  printf("     System Info     ");

  setFont(OLED_FONT_8X6);
  setDisplayMode(1);
  setXY(0, 18);
  printf("Model:ESP12(esp8266)\r\n");
  setXY(0, 18 + 8);
  printf("Flash Size:32Mbit\r\n");
  setXY(0, 18 + 8 + 8); 
  printf("Memory Size:4Mbit\r\n");
}

int SystemInfoUI::event(const KEventCode& event)
{
  switch (K_EVENT_CLASS(event))
  {
  case K_EVENT_CLASS_KEY:
    if(K_EVENT_DATA(event) == K_EVENT_KEY_OK) {
      nextWidget = UI_INDEX_MENU_SYSTEM_INFO;
      break;
    }
    break;
  case K_EVENT_CLASS_TICK_ONCE:
    updateDisplay();
    break;
  }

  return KWidget::event(event);
}

void SystemInfoUI::updateDisplay()
{
  setXY(0, 42);
  printf("SSID:%s\r\n", WiFi.SSID().c_str());
  setXY(0, 42 + 8);
  printf("IP:%s", WiFi.localIP().toString().c_str());
  setXY(0, 42 + 8 + 8);
  printf("CPU:%d    ", cpuUsage);
}
