#include "SystemInfoUI.h"
#include <DHT.h>
#include <NTPClient.h>
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
  setFont(OLED_FONT_8X6);
  setDisplayMode(0);
  printf("     System Info     ");
  setDisplayMode(1);
  setXY(0, 8);
  printf("Model:ESP12(esp8266)\r\n");
  setXY(0, 8 + 8);
  printf("Flash Size:32Mbit\r\n");
  setXY(0, 8 + 8 + 8); 
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
  setXY(0, 32);
  printf("SSID:%s\r\n", WiFi.SSID().c_str());
  setXY(0, 32 + 8);
  printf("IP:%s", WiFi.localIP().toString().c_str());
  setXY(0, 32 + 8 + 8);
  printf("CPU:%d    ", cpuUsage);
}
