#ifndef _K_LABEL_H_
#define _K_LABEL_H_
#include "KWidget.h"
#include <string>

class KLabel : public KWidget
{
public:
    KLabel(std::string text, uint8_t x, uint8_t y, uint8_t w, uint8_t h);
    ~KLabel();

    void setText(std::string text);

    void setScroll(bool val);

    std::string getText();

    virtual int event(const KEventCode&);

protected:
    virtual void paint();

    std::string text;
    bool isScroll;
    int16_t currentPose;
};

#endif
