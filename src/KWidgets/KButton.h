#ifndef _K_BUTTON_H_
#define _K_BUTTON_H_
#include "KLabel.h"
#include <string>

class KButton : public KLabel
{
public:
    KButton(std::string text, uint8_t x, uint8_t y, uint8_t w, uint8_t h);
    ~KButton();

private:
    void paint();
};

#endif
