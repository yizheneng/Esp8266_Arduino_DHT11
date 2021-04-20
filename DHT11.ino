#include <DHT.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include "SSD1306SPI.h"

DHT dht(D1, DHT11);
SSD1306SPI oled(D6, D4, D5, D2, D3);
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, 8 * 60 * 60);

char ssid[] = "Cnbot-Work";
char pass[] = "Cnbot001";

char ssid1[] = "2291"; 
char pass1[] = "2911.2911"; 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  WiFi.begin(ssid1, pass1);
  dht.begin();
  oled.begin();
  timeClient.begin();
}

void loop() {
  char printBuf[100];
  while(1) {
    if(WiFi.status() == WL_CONNECTED) {
      timeClient.update();
    } else {
      static bool connectFlag = false;
      if(!connectFlag) {
        byte numSsid = WiFi.scanNetworks();
        for (int i = 0; i < numSsid; i++) {
          Serial.println(WiFi.SSID(i));
          if(WiFi.SSID(i) == ssid) {
            WiFi.begin(ssid, pass);
            oled.setXY(0, 0);
            OLED_PRINT("SSID:%s\r\n", ssid);
            connectFlag = true;
          } else if(WiFi.SSID(i) == ssid1) {
            WiFi.begin(ssid1, pass1);
            oled.setXY(0, 0);
            OLED_PRINT("SSID:%s\r\n", ssid1);
            connectFlag = true;
          }
        }  
      }
    }
    
    oled.setXY(0, 8);
    // ip address
    OLED_PRINT("IP:%s\r\ntime:%s\r\ntemp:%d hum:%d\r\n", WiFi.localIP().toString().c_str(), 
                                                        timeClient.getFormattedTime().c_str(),
                                                        (int)dht.readTemperature(),
                                                        (int)dht.readHumidity());
    oled.sync();
    delay(1000);
  }
}
