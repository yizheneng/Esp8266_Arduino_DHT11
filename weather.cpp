#include "weather.h"
#include "weathericon.h"
#include <ArduinoJson.h>
//const char weatherUri[] = "https://api.seniverse.com/v3/weather/daily.json?key=rrpd2zmqkpwlsckt&location=changsha&language=en&unit=c&start=0&days=3";

Weather::Weather(Client& aClient) :
  client(aClient, "api.seniverse.com"),
  updateFlag(false),
  lastUpdateTime(0)
{
  weatherIcon[0] = WEATHER_ICON_INDEX_SUNNY;
  weatherIcon[1] = WEATHER_ICON_INDEX_NIGHT;
  weatherIcon[2] = WEATHER_ICON_INDEX_SUNNY;
  weatherIcon[3] = WEATHER_ICON_INDEX_NIGHT;
  weatherIcon[4] = WEATHER_ICON_INDEX_CLOUDY;
  weatherIcon[5] = WEATHER_ICON_INDEX_CLOUDY_DAY;
  weatherIcon[6] = WEATHER_ICON_INDEX_CLOUDY_NIGHT;
  weatherIcon[7] = WEATHER_ICON_INDEX_CLOUDY_DAY;
  weatherIcon[8] = WEATHER_ICON_INDEX_CLOUDY_NIGHT;
  weatherIcon[9] = WEATHER_ICON_INDEX_CLOUDY_DAY;
  weatherIcon[10] = WEATHER_ICON_INDEX_THUNDERSHOWER;
  weatherIcon[11] = WEATHER_ICON_INDEX_THUNDERSHOWER;
  weatherIcon[12] = WEATHER_ICON_INDEX_THUNDERSHOWER_DAY;
  weatherIcon[13] = WEATHER_ICON_INDEX_LIGHT_RAIN;
  weatherIcon[14] = WEATHER_ICON_INDEX_MODERATE_RAIN;
  weatherIcon[15] = WEATHER_ICON_INDEX_HEAVY;
  weatherIcon[16] = WEATHER_ICON_INDEX_RAINSTORM;
  weatherIcon[17] = WEATHER_ICON_INDEX_RAINSTORM;
  weatherIcon[18] = WEATHER_ICON_INDEX_RAINSTORM;
  weatherIcon[19] = WEATHER_ICON_INDEX_LIGHT_SNOW;
  weatherIcon[20] = WEATHER_ICON_INDEX_LIGHT_SNOW;
  weatherIcon[21] = WEATHER_ICON_INDEX_LIGHT_SNOW;
  weatherIcon[22] = WEATHER_ICON_INDEX_LIGHT_SNOW;
  weatherIcon[23] = WEATHER_ICON_INDEX_MODERATE_SNOW;
  weatherIcon[24] = WEATHER_ICON_INDEX_MODERATE_SNOW;
  weatherIcon[25] = WEATHER_ICON_INDEX_MODERATE_SNOW;
  weatherIcon[26] = WEATHER_ICON_INDEX_FOG;
  weatherIcon[27] = WEATHER_ICON_INDEX_FOG;
  weatherIcon[28] = WEATHER_ICON_INDEX_GALE;
  weatherIcon[29] = WEATHER_ICON_INDEX_GALE;
  weatherIcon[30] = WEATHER_ICON_INDEX_HEAVY_FOG_DAY;
  weatherIcon[31] = WEATHER_ICON_INDEX_HEAVY_FOG_DAY;
  weatherIcon[32] = WEATHER_ICON_INDEX_GALE;
  weatherIcon[33] = WEATHER_ICON_INDEX_GALE;
  weatherIcon[34] = WEATHER_ICON_INDEX_UNKNOW;
  weatherIcon[35] = WEATHER_ICON_INDEX_UNKNOW;
  weatherIcon[36] = WEATHER_ICON_INDEX_UNKNOW;
  weatherIcon[37] = WEATHER_ICON_INDEX_SONW;
  weatherIcon[38] = WEATHER_ICON_INDEX_SUNNY;
}

void Weather::tickOnce()
{
  if(!updateFlag || ((millis() - lastUpdateTime) > 1000*60*60)) {
    this->updateWeather();
  }
}

void Weather::updateWeather()
{
  int err = client.get("/v3/weather/daily.json?key=SRHcTbDbOf5nYrrQg&location=changsha&language=en&unit=c&start=0&days=3");
  if (err == 0)
  {
    Serial.println("startedRequest ok");

    err = client.responseStatusCode();
    if (err >= 0)
    {
      Serial.print("Got status code: ");
      Serial.println(err);
      
      int bodyLen = client.contentLength();
      Serial.println(client.responseBody());

      DynamicJsonDocument doc(1024);
      deserializeJson(doc, client.responseBody().c_str());
      JsonObject resultObject = doc.as<JsonObject>();
      for(int i = 0; i < resultObject["results"][0]["daily"].size(); i++) {
        weathers[i].weatherCodeDay = atoi(resultObject["results"][0]["daily"][i]["code_day"]);
        weathers[i].highTemp = atoi(resultObject["results"][0]["daily"][i]["high"]);
        weathers[i].lowTemp =  atoi(resultObject["results"][0]["daily"][i]["low"]);
        weathers[i].humidity = atoi(resultObject["results"][0]["daily"][i]["humidity"]);
        Serial.printf("index:%d code_day:%d high:%d low:%d\r\n", i, weathers[i].weatherCodeDay, weathers[i].highTemp, weathers[i].lowTemp);
        updateFlag = true;
        lastUpdateTime = millis();
      }
    }
  } else {
    Serial.println("Request error!");
  }
}
