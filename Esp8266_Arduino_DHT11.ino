#include <DHT.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include "src/displayDrivers/SSD1306SPI.h"
#include "src/icon/weathericon.h"
//#include "badapple.h"
#include "src/button/button.h"
#include "src/utils/weather.h"
#include "src/utils/news.h"
#include "src/menu/MainUI.h"
#include "src/menu/WeatherUI.h"
#include "src/menu/SystemInfoUI.h"
#include "src/menu/SystemInfoMenuUI.h"
#include "src/menu/WeatherMenuUI.h"
#include "src/menu/SettingsMenuUI.h"
#include "src/menu/SettingsUI.h"
#include "src/TestUI/ButtonTest.h"

/**
 * TODO List:
 * 1.每天重要新闻推送
 * 2.点阵显示界面框架
 *   1) KWidget基类
 *      方法:paint 调用时更新控件绘图
 *           event 接收键盘等事件
 *           addChild 添加子控件
 *   2）KLabel  类 显示文字
 *   3）KButton 类 点击产生事件
 *   4）KImage  类 显示图片（点阵图片）
 *   5）KLineEdit 类 编辑单行文本
 *   6）KSpinBox  类 编辑整数
 *   7) KDoubleSpinBox 类 编辑浮点数
 *   8）KTextEdit 类 编辑多行文本
 *   9) KListSelect 类 列表选择控件
 *   10) KProcess   类 进度条显示控件
 *   11) KChooseBox 类 选择显示控件
 * 3.天气界面根据日出日落时间来进行图标切换
 * 
*/

DHT dht(D1, DHT11);
SSD1306SPI oled(D6, D4, D2, D0);
WiFiUDP ntpUDP;
WiFiClient weatherClient;
NTPClient timeClient(ntpUDP, 8 * 60 * 60);
Weather weather(weatherClient);
WiFiClient newsClient;
News news(newsClient);
uint8_t OLED_GRAM[144][8];     // 页面显示缓存

char ssid[] = "Cnbot-Work";
char pass[] = "Cnbot001";

char ssid1[] = "2291";
char pass1[] = "2911.2911";

Button buttonL(D6);
Button buttonC(D7);
Button buttonR(D5);
Button buttonUser(D3);

UIInterface *uiPointers[UI_INDEX_MAX];

void setup()
{
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
  uiPointers[UI_INDEX_MENU_SETTINGS_UI] = new SettingsMenuUI();
  uiPointers[UI_INDEX_SETTINGS_UI] = new SettingsUI();
}

void loop()
{
  int i = 0;
  int currentUIIndex = UI_INDEX_MAIN_UI;
  uint32_t count100msCount = millis();

  uiPointers[currentUIIndex]->enter();
  while (1)  {
    if (WiFi.status() == WL_CONNECTED) {
      static uint32_t count5S = millis();
      if((millis() - count5S) > 5000) {
        count5S = millis();
        timeClient.update();
        weather.tickOnce();
        news.tickOnce();
      }
    } else {
      static bool connectFlag = false;
      if (!connectFlag) {
        byte numSsid = WiFi.scanNetworks();
        for (int i = 0; i < numSsid; i++) {
          Serial.println(WiFi.SSID(i));
          if (WiFi.SSID(i) == ssid) {
            WiFi.begin(ssid, pass);
            connectFlag = true;
          } else if (WiFi.SSID(i) == ssid1) {
            WiFi.begin(ssid1, pass1);
            connectFlag = true;
          }
        }
      }
    }

  TICK_ONCE:
    int8_t temp = uiPointers[currentUIIndex]->tickOnce();
    if (temp >= 0) { // 大于0需要切换界面
      if (temp < UI_INDEX_MAX) {
        Serial.printf("Switch to:%d - %d\r\n", currentUIIndex, temp);
        currentUIIndex = temp;
        uiPointers[currentUIIndex]->enter();
        goto TICK_ONCE;
      }
    }

    // buttonTest->tickOnce();
    uiPointers[currentUIIndex]->event(K_EVENT(K_EVENT_CLASS_TICK_ONCE, 100)); // 滴答信号输入
    uiPointers[currentUIIndex]->event(K_EVENT(K_EVENT_CLASS_USER_BUTTON, buttonUser.pressStatus())); // 按钮信号输入

    oled.syncDisplay((uint8_t*)OLED_GRAM);

#define MAIN_LOOP_WAIT_TIME 100 // 100ms
    uint32_t delayVal = (MAIN_LOOP_WAIT_TIME - (millis() - count100msCount)); // 计算需要等待的时间

    if(delayVal < MAIN_LOOP_WAIT_TIME) {
      delay(delayVal);
    }
    count100msCount = millis();
  }
}
