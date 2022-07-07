#ifndef _NEWS_LABEL_H_
#define _NEWS_LABEL_H_
#include "../../KWidgets/KLabel.h"

class NewsLabel : public KLabel
{
public:
    NewsLabel(uint8_t x, uint8_t y, uint8_t w, uint8_t h);
    ~NewsLabel();

    virtual int event(const KEventCode&);
private:
    /* data */
};

#endif

