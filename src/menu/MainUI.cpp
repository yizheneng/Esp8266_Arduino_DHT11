#include "MainUI.h"
#include <DHT.h>
#include <time.h>
#include <NTPClient.h>
#include "../utils/weather.h"
#include "../utils/news.h"
#include "../icon/weathericon.h"
#include "../button/button.h"
#include "../displayDrivers/font/sseriff.h"
#include "../displayDrivers/UIInterface.h"
#include "NewsLabel.h"

extern DHT dht;
extern NTPClient timeClient;
extern Weather weather;
extern Button buttonL;
extern Button buttonC;
extern Button buttonR;
// extern Button buttonUser;

// 主界面
MainUI::MainUI() :
  UIInterface(0, 0, 128, 64)
{
  timeLabel = new KLabel("00:00:00",   48, 0, 8*16, 16);
  dateLabel = new KLabel("1990-00-00", 40, 16, 8*16, 16);

  tempAndHumLabel = new KLabel("", 0, 31, 128, 16);
  tempAndHumLabel->setScroll(true);
  
  weatherIcon = new KImage(0, 0, 32, 32);
 
  this->addChild(weatherIcon);
  this->addChild(timeLabel);
  this->addChild(dateLabel);
  this->addChild(tempAndHumLabel);

  newsLabel = new NewsLabel(0, 47, 128, 16);
  newsLabel->setScroll(true);
  this->addChild(newsLabel);
}

void MainUI::enter()
{
  UIInterface::enter();
  Serial.println("Test 5!");
  clearDisplay();
}

int MainUI::event(const KEventCode& event)
{
  switch (K_EVENT_CLASS(event))
  {
  case K_EVENT_CLASS_KEY:
    if(K_EVENT_DATA(event) == K_EVENT_KEY_LEFT) {
      nextWidget = UI_INDEX_MENU_WEATHER;
      break;
    }

    if(K_EVENT_DATA(event) == K_EVENT_KEY_RIGHT) {
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

void MainUI::updateDisplay()
{
  if(weather.isUpdated()) {
    weatherIcon->setImage((uint8_t*)picture32X32[weather.getWeathers()[0].weatherIconCode], true);
  }

  time_t rawtime = timeClient.getEpochTime();
  struct tm *info;
  info = localtime( &rawtime );
  
  char printBuf[40];
  sprintf(printBuf, "%02d:%02d:%02d", info->tm_hour, info->tm_min, info->tm_sec);            // 时间显示
  timeLabel->setText(printBuf);

  sprintf(printBuf, "%04d-%02d-%02d", info->tm_year + 1900, info->tm_mon + 1, info->tm_mday); // 温度显示
  dateLabel->setText(printBuf);

  sprintf(printBuf, "高温:%2d 低温:%2d 温度:%2d 湿度:%2d      ", weather.getWeathers()[0].highTemp, 
                                                          weather.getWeathers()[0].lowTemp,
                                                          (int)dht.readTemperature(), 
                                                          (int)dht.readHumidity());
  tempAndHumLabel->setText(printBuf);

  this->paint();
}
