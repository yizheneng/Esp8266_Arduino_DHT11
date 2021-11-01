#ifndef _K_LISTSELECT_H_
#define _K_LISTSELECT_H_
#include "../KWidgets/KWidget.h"

#define MAX_LIST_ITEM_NUM 10

class KListSelect : public KWidget
{
public:
    KListSelect(uint8_t x, uint8_t y, uint8_t w, uint8_t h);

    void addChild(const char* listContent);

    void setSelectedIndex(uint8_t val);

    virtual int event(const KEventCode&);
};

#endif
