#include "KLabel.h"
#include "../displayDrivers/font/ascii_font.h"
#include "../displayDrivers/font/sseriff.h"

KLabel::KLabel(std::string text, uint8_t x, uint8_t y, uint8_t w, uint8_t h) :
    KWidget(x, y, w, h),
    text(text),
    isScroll(false),
    currentPose(0)
{
    setFont((uint8_t*)FONT_SSERIFF, 16, 16, true);
}

KLabel::~KLabel()
{
}

void KLabel::setText(std::string text)
{
    this->text = text;
}

std::string KLabel::getText()
{
    return text;
}

int KLabel::event(const KEventCode& event)
{
    switch (K_EVENT_CLASS(event)) {
        case K_EVENT_CLASS_TICK_ONCE:
            if(!isScroll)
                break;

            // Serial.printf("strlen:%d\r\n", this->getStringWidth(text.c_str()));
            if(this->getStringWidth(text.c_str()) > w) {
                this->currentPose ++;
                if(this->currentPose >= (this->getStringWidth(text.c_str()) - w)) {
                    this->currentPose = 0;
                }
            } else {
                this->currentPose = 0;
            }
            break;
        default:
            break;
    }
    return 0;
}

void KLabel::paint()
{
    if(isScroll) {
        this->showString(x - this->currentPose, y, text.c_str(), !isFoused);
        // Serial.printf("this->currentPose:%d\r\n", this->currentPose);
    } else {
        this->showString(x, y, text.c_str(), !isFoused);
    }
}

void KLabel::setScroll(bool val)
{
    this->isScroll = val;
}
