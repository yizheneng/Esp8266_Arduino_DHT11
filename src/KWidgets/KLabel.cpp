#include "KLabel.h"
#include "../displayDrivers/font/ascii_font.h"
#include "../displayDrivers/font/sseriff.h"

KLabel::KLabel(std::string text, int x, int y, int w, int h) :
    KWidget(x, y, w, h),
    text(text)
{
    setFont((uint8_t*)FONT_SSERIFF, 16, 16, true);
}

KLabel::~KLabel()
{
}

void KLabel::setFont(const uint8_t* fontPtr, uint8_t w, uint8_t h, bool isFontInFlash)
{
    this->fontPtr = fontPtr;
    this->fontWidth = w;
    this->fontHeight = h;
    this->isFontInFlash = isFontInFlash;
}

void KLabel::setFontSize(OledFont font)
{
    switch (font) {
    case OLED_FONT_8X6:
        setFont((uint8_t*)asc2_0806, 6, 8, false);
        break;
    case OLED_FONT_12X6:
        setFont((uint8_t*)asc2_1206, 6, 12, false);
        break;
    case OLED_FONT_16X8:
        setFont((uint8_t*)asc2_1608, 8, 16, false);
        break;
    case OLED_FONT_24X12:
        setFont((uint8_t*)asc2_2412, 12, 24, false);
        break;
    default:
        break;  
    }
}

void KLabel::paint(DrawOnMemory& painter)
{
    painter.setFont(fontPtr, fontWidth, fontHeight, isFontInFlash);
    painter.showString(x, y, text.c_str(), true);
}
