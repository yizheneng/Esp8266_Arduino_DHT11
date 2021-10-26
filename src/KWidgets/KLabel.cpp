#include "KLabel.h"
#include "../displayDrivers/font/ascii_font.h"
#include "../displayDrivers/font/sseriff.h"

KLabel::KLabel(std::string text, uint8_t x, uint8_t y, uint8_t w, uint8_t h) :
    KWidget(x, y, w, h),
    text(text)
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

void KLabel::paint()
{
    this->showString(x, y, text.c_str(), 1);
}
