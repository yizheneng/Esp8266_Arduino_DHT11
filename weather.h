#ifndef _WEATHER_H_
#define _WEATHER_H_
#include <ArduinoHttpClient.h>
#include <stdint.h>

struct WeatherInfo {
  uint8_t weatherCodeDay; // 早上的天气代码
  int8_t highTemp;        // 最高温度
  int8_t lowTemp;         // 最低温度
  int8_t humidity;        // 湿度
};

class Weather {
public:
  Weather(Client& aClient);

  void tickOnce();

  bool isUpdated() {
    return updateFlag;
  }

  WeatherInfo* getWeathers() {
    return weathers;
  }

  uint8_t getIconIndex(uint8_t weathersIndex) {
    if(weathersIndex < sizeof(weatherIcon)) {
      return weatherIcon[weathersIndex];
    } else {
      return 0;
    }
  }
private:
  void updateWeather();
  
  HttpClient client;
  WeatherInfo weathers[3];
  bool updateFlag;
  int lastUpdateTime;
  uint8_t weatherIcon[39];
};

#endif
