#ifndef _K_LABEL_H_
#define _K_LABEL_H_
#include "KWidget.h"
#include <string>

class KLabel : public KWidget
{
public:
    KLabel(std::string text, int x, int y, int w, int h);
    ~KLabel();

    void setFont(const uint8_t* fontPtr, uint8_t w, uint8_t h, bool isFontInFlash);

    void setFontSize(OledFont font);

protected:
    void paint(DrawOnMemory& painter);

private:
    std::string text;
    const uint8_t* fontPtr;
    uint8_t fontWidth;
    uint8_t fontHeight;
    bool isFontInFlash;
};

#endif
