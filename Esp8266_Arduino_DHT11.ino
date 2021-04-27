#include <DHT.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include "SSD1306SPI.h"
#include "weathericon.h"
//#include "badapple.h"
#include "button.h"
#include "weather.h"
#include "MainUI.h"
#include "WeatherUI.h"
#include "SystemInfoUI.h"
#include "SystemInfoMenuUI.h"
#include "WeatherMenuUI.h"

DHT dht(D1, DHT11);
SSD1306SPI oled(D6, D4, D5, D2, D3);
WiFiUDP ntpUDP;
WiFiClient weatherClient;
NTPClient timeClient(ntpUDP, 8 * 60 * 60);
Weather weather(weatherClient);

char ssid[] = "Cnbot-Work";
char pass[] = "Cnbot001";

char ssid1[] = "2291"; 
char pass1[] = "2911.2911"; 

Button buttonL(D0);
Button buttonC(D7);
Button buttonR(D8);

UIInterface* uiPointers[3];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  WiFi.begin(ssid1, pass1);
  dht.begin();
  oled.begin();
  timeClient.begin();

  uiPointers[UI_INDEX_MAIN_UI] = new MainUI();
  uiPointers[UI_INDEX_WEATHER_UI] = new WeatherUI();
  uiPointers[UI_INDEX_SYSTEM_INFO_UI] = new SystemInfoUI();
  uiPointers[UI_INDEX_MENU_SYSTEM_INFO] = new SystemInfoMenuUI();
  uiPointers[UI_INDEX_MENU_WEATHER] = new WeatherMenuUI();
}

void loop() {
  int i = 0;
  int currentUIIndex = UI_INDEX_MAIN_UI;

  while(1) {
    if(WiFi.status() == WL_CONNECTED) {
      timeClient.update();
      weather.tickOnce();
    } else {
      static bool connectFlag = false;
      if(!connectFlag) {
        byte numSsid = WiFi.scanNetworks();
        for (int i = 0; i < numSsid; i++) {
          Serial.println(WiFi.SSID(i));
          if(WiFi.SSID(i) == ssid) {
            WiFi.begin(ssid, pass);
            connectFlag = true;
          } else if(WiFi.SSID(i) == ssid1) {
            WiFi.begin(ssid1, pass1);
            connectFlag = true;
          }
        }  
      }
    }

TICK_ONCE:
    int8_t temp = uiPointers[currentUIIndex]->tickOnce();
    if(temp >= 0) {
      if(temp < UI_INDEX_MAX) {
        Serial.printf("Switch to:%d - %d\r\n", currentUIIndex, temp);
        currentUIIndex = temp;
        uiPointers[currentUIIndex]->enter();
        goto TICK_ONCE;
      }
    }
    
    oled.syncDisplay(uiPointers[currentUIIndex]->getGRam());
    
    delay(10);
  }
}
