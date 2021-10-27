#include "KButton.h"

KButton::KButton(std::string text, uint8_t x, uint8_t y, uint8_t w, uint8_t h) :
    KLabel(text, x, y, w, h)
{
}

KButton::~KButton()
{
}

void KButton::paint()
{
    uint8_t stringX = this->x, stringY = this->y;

    if(alignmentFlag & KWidget::AlignLeft) {
        stringX += 2;
    } else if(alignmentFlag & KWidget::AlignRight) {
        uint8_t stringWidth = this->getStringWidth(text.c_str());
        stringX = x + w - stringWidth;
    } else if(alignmentFlag & KWidget::AlignHCenter) {
        uint8_t stringWidth = this->getStringWidth(text.c_str());
        stringX = (w - stringWidth) / 2 + x;
    }

    if(alignmentFlag & KWidget::AlignTop) {
        stringY = y + 2;
    } else if(alignmentFlag & KWidget::AlignBottom) {
        stringY = h - this->fontHeight + y;
    } else if(alignmentFlag & KWidget::AlignVCenter) {
        stringY = (h - this->fontHeight) / 2 + y;
    }

    this->drawRect(x, y, w, h, mode, false);

    if(isFoused) {
        this->drawRect(x + 2, y + 2, w - 4, h - 4, mode, true);
        this->showString(stringX, stringY, text.c_str(), 0);
    } else {
        this->showString(stringX, stringY, text.c_str(), 1);
    }
}