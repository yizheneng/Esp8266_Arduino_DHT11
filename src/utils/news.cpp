#include "news.h"
#include <Arduino_JSON.h>

#define NEWS_ADDR   "v.juhe.cn"
#define NEWS_PARMAS "/toutiao/index?type=&page=&page_size=10&is_filter=&key=bd3299d85f864648cf33ddaacb8cf7d2"

News::News(Client& aClient) :
  client(aClient, NEWS_ADDR),
  updateFlag(false),
  lastUpdateTime(0)
{
}

News::~News()
{
}

void News::tickOnce()
{
  if(!updateFlag || ((millis() - lastUpdateTime) > 1000*60*60)) {
    this->update();
  }
}

void News::update()
{
  int err = client.get(NEWS_PARMAS);
  if (err == 0)
  {
    Serial.println("startedRequest ok");

    err = client.responseStatusCode();
    if (err >= 0)
    {
      Serial.print("Got status code: ");
      Serial.println(err);
      
      int bodyLen = client.contentLength();
      String content = client.responseBody();
      Serial.println(content);

      JSONVar rootObject = JSON.parse(content);
      if (JSON.typeof(rootObject) != "object") {
        Serial.print("Parsing root failed:");
        Serial.println(JSON.typeof(rootObject));
        return;
      }

      if(!rootObject.hasOwnProperty("result")) {
        Serial.println("Parsing results failed!");
        return;
      }

      if(JSON.typeof(rootObject["result"]) != "object") {
        Serial.println("results is't array!");
        return;
      }
      
      if(1 != atoi(rootObject["result"]["stat"])) {
        Serial.println("stat error!");
        return;
      }

      if(JSON.typeof(rootObject["result"]["data"]) != "array") {
        Serial.println("data is't array!");
        return;
      }

      newsList.clear();
      for(int i = 0; i < rootObject["result"]["data"].length(); i++) {
          Serial.println(rootObject["result"]["data"][i]["title"]);
          newsList.push_back(std::string(rootObject["result"]["data"][i]["title"]));
          updateFlag = true;
          lastUpdateTime = millis();
      }
      newsIter = newsList.begin();
    }
  } else {
    Serial.println("Request error!");
  }
}

std::string News::getNextNews()
{
  if(newsList.size() <= 0) {
    return "";
  }

  newsIter ++;
  if(newsIter == newsList.end()) {
    newsIter = newsList.begin();
  }

  return *newsIter;
}
