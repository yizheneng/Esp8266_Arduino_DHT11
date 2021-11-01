#include "KCheckBox.h"

KCheckBox::KCheckBox(std::string text, uint8_t x, uint8_t y, uint8_t w, uint8_t h) :
    KLabel(text, x, y, w, h),
    isChecked(false)
{

}

void KCheckBox::setChecked(bool val)
{
    isChecked = val;
}

int KCheckBox::event(const KEventCode& event)
{
    switch (K_EVENT_CLASS(event)) {
        case K_EVENT_CLASS_TICK_ONCE:
            if(!isScroll)
                break;

            if(this->getStringWidth(text.c_str()) > (w - 18)) {
                this->currentPose ++;
                if(this->currentPose >= (this->getStringWidth(text.c_str()) - (w - 18))) {
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

void KCheckBox::paint()
{
    this->drawRect(x + 2, y + 2, 16 - 4, 16 - 4, 1, false);
    if(isChecked) {
        this->drawRect(x + 5, y + 5, 16 - 9, 16 - 10, 1, true);
    } else {
        this->drawRect(x + 5, y + 5, 16 - 9, 16 - 10, 0, true);
    }

    uint8_t tempMinX, tempMinY, tempMaxX, tempMaxY;

    tempMinX = x + 18;
    tempMinY = y;
    tempMaxX = x + w;
    tempMaxY = y + h;

    if(isScroll) {
        this->showString(x - this->currentPose, y, text.c_str(), !isFoused, tempMinX, tempMinY, tempMaxX, tempMaxY);
    } else {
        this->showString(x + 18, y, text.c_str(), !isFoused, tempMinX, tempMinY, tempMaxX, tempMaxY);
    }
}
