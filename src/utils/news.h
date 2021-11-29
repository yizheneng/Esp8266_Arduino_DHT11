#ifndef _NEWS_H_
#define _NEWS_H_
#include <ArduinoHttpClient.h>
#include <stdint.h>
#include <list>
#include <string>

class News
{
public:
    News(Client& aClient);
    ~News();

    void tickOnce();

    std::string getNextNews();
private:
    void update();

    HttpClient client;
    bool updateFlag;
    int lastUpdateTime;
    std::list<std::string>::iterator newsIter;
    std::list<std::string> newsList;
};

#endif
