#include "MainUI.h"
#include <DHT.h>
#include <time.h>
#include <NTPClient.h>
#include "../utils/weather.h"
#include "../icon/weathericon.h"
#include "../button/button.h"
#include "../displayDrivers/font/sseriff.h"
#include "../displayDrivers/UIInterface.h"

extern DHT dht;
extern NTPClient timeClient;
extern Weather weather;
extern Button buttonL;
extern Button buttonC;
extern Button buttonR;
extern Button buttonUser;

// 主界面
MainUI::MainUI() :
  KWidget(0, 0, 128, 64)
{
  timeLabel = new KLabel("00:00:00",   48, 0, 8*16, 16);
  dateLabel = new KLabel("1990-00-00", 40, 16, 8*16, 16);
  
  weatherIcon = new KImage(0, 0, 32, 32);
 
  this->addChild(weatherIcon);
  this->addChild(timeLabel);
  this->addChild(dateLabel);

  this->addChild(new KLabel("低:", 0, 32, 16*2, 16));
  lowTempLabel = new KLabel("00", 24, 32, 2*16, 16);
  this->addChild(lowTempLabel);

  this->addChild(new KLabel("高:", 64, 32, 16*2, 16));
  highTempLabel = new KLabel("00", 24 + 64, 32, 2*16, 16);
  this->addChild(highTempLabel);

  this->addChild(new KLabel("温:", 0, 48, 16*2, 16));
  realTempLabel = new KLabel("00", 24, 48, 2*16, 16);
  this->addChild(realTempLabel);

  this->addChild(new KLabel("湿:", 64, 48, 16*2, 16));
  realHumLabel = new KLabel("00", 24 + 64, 48, 2*16, 16);
  this->addChild(realHumLabel);

  this->addChild(new KButton("Push", 20, 20, 40, 50));
}

void MainUI::enter()
{
  
}

int8_t MainUI::tickOnce()
{
  if(weather.isUpdated()) {
    weatherIcon->setImage((uint8_t*)picture32X32[weather.getWeathers()[0].weatherIconCode], true);
  }

  time_t rawtime = timeClient.getEpochTime();
  struct tm *info;
  info = localtime( &rawtime );
  
  char printBuf[20];
  sprintf(printBuf, "%02d:%02d:%02d", info->tm_hour, info->tm_min, info->tm_sec);            // 时间显示
  timeLabel->setText(printBuf);

  sprintf(printBuf, "%04d-%02d-%02d", info->tm_year + 1900, info->tm_mon + 1, info->tm_mday); // 温度显示
  dateLabel->setText(printBuf);
  
  sprintf(printBuf, "%d", weather.getWeathers()[0].lowTemp);
  lowTempLabel->setText(printBuf);

  sprintf(printBuf, "%d", weather.getWeathers()[0].highTemp);
  highTempLabel->setText(printBuf);

  sprintf(printBuf, "%d", (int)dht.readTemperature());
  realTempLabel->setText(printBuf);

  sprintf(printBuf, "%d", (int)dht.readHumidity());
  realHumLabel->setText(printBuf);

  this->paint();

  switch (buttonUser.pressStatus())
  {
  case PRESS_STATUS_SHORT_PRESS:
    return UI_INDEX_MENU_WEATHER;
    break;
  case PRESS_STATUS_LONG_PRESS:
    return UI_INDEX_MENU_SETTINGS_UI;
    break;
  }

  return -1;
}
