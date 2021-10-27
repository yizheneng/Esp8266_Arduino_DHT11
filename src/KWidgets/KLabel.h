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

    std::string getText();

protected:
    void paint();

    std::string text;

private:
    
};

#endif
