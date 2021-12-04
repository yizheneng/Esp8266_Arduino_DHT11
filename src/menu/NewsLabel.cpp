#include "NewsLabel.h"
#include "../utils/news.h"

extern News news;

NewsLabel::NewsLabel(uint8_t x, uint8_t y, uint8_t w, uint8_t h) :
    KLabel("", x, y, w, h)
{
}

NewsLabel::~NewsLabel()
{
}

int NewsLabel::event(const KEventCode& event)
{
    switch (K_EVENT_CLASS(event)) {
        case K_EVENT_CLASS_TICK_ONCE:
            if(!isScroll)
                break;

            // Serial.printf("strlen:%d\r\n", this->getStringWidth(text.c_str()));
#define START_WAIT_TIME_COUNT 20
#define END_WAIT_TIME_COUNT   20
            static uint16_t startWaitTimeCounter = 0;
            static uint16_t endWaitTimeCounter = 0;
            if(this->getStringWidth(text.c_str()) > w) {
                if((startWaitTimeCounter < 20) && (this->currentPose == 0)) {
                    startWaitTimeCounter ++;
                } else {
                    this->currentPose += 2;
                }
                
                if(this->currentPose >= (this->getStringWidth(text.c_str()) - w)) {
                    if(endWaitTimeCounter >= END_WAIT_TIME_COUNT) {
                        this->currentPose = 0;
                        startWaitTimeCounter = 0;
                        endWaitTimeCounter = 0;
                        setText(news.getNextNews());
                    } else {
                        endWaitTimeCounter ++;
                    }
                }
            } else {
                this->currentPose = 0;
                setText(news.getNextNews());
            }
            break;
        default:
            break;
    }
    return 0;
}