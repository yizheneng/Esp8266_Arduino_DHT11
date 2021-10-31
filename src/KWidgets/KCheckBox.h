#ifndef _K_CHOOSEBOX_H_
#define _K_CHOOSEBOX_H_
#include "../KWidgets/KLabel.h"
#include <string>

class KCheckBox : public KLabel
{
public:
    KCheckBox(std::string text, uint8_t x, uint8_t y, uint8_t w, uint8_t h);
    ~KCheckBox();

    void setChecked(bool val);

    virtual int event(const KEventCode&);

protected:
    virtual void paint();

    bool isChecked;
};

#endif
