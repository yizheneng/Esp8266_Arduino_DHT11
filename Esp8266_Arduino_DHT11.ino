#include <DHT.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include "SSD1306SPI.h"
//#include "weathericon.h"
#include "badapple.h"
#include "button.h"

DHT dht(D1, DHT11);
SSD1306SPI oled(D6, D4, D5, D2, D3);
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, 8 * 60 * 60);

char ssid[] = "Cnbot-Work";
char pass[] = "Cnbot001";

char ssid1[] = "2291"; 
char pass1[] = "2911.2911"; 

Button buttonL(D0);
Button buttonC(D7);
Button buttonR(D8);

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
  oled.setFontSize(OLED_FONT_8X6);
  int i = 0;
  int buttonCCounter = 0, buttonLCounter = 0, buttonRCounter = 0;
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
            oled.setXY(0, 32);
            OLED_PRINT("SSID:%s\r\n", ssid);
            connectFlag = true;
          } else if(WiFi.SSID(i) == ssid1) {
            WiFi.begin(ssid1, pass1);
            oled.setXY(0, 32);
            OLED_PRINT("SSID:%s\r\n", ssid1);
            connectFlag = true;
          }
        }  
      }
    }
    
    oled.setXY(0, 40);
    // ip address
    OLED_PRINT("IP:%s\r\ntime:%s\r\ntemp:%d hum:%d\r\n", WiFi.localIP().toString().c_str(), 
                                                        timeClient.getFormattedTime().c_str(),
                                                        (int)dht.readTemperature(),
                                                        (int)dht.readHumidity());
    oled.setXY(0,0);

    if(buttonL.isClicked()) {
      buttonLCounter ++;
    }

    if(buttonC.isClicked()) {
      buttonCCounter ++;
    }

    if(buttonR.isClicked()) {
      buttonRCounter ++;
    }
    OLED_PRINT("Button L:%d\r\nButton C:%d\r\nButton R:%d\r\n", buttonLCounter, buttonCCounter, buttonRCounter)
    /*if(i >= 704) {
      i = 0;
    }
    //oled.showPictureInFlash(32, 0, 32, 32, picture32X32[i]);
    oled.showPictureInFlash(22, 0, 85, 64, picture85X64[i]);
    i++;*/
    oled.sync();
    delay(30);
  }
}
