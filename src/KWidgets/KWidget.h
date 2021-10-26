#ifndef _K_WIDGET_H_
#define _K_WIDGET_H_
#include "KEvent.h"
#include "../displayDrivers/DrawOnMemory.h"
#define K_WIDGET_MAX_CHILD_NUM 15

class KWidget : public DrawOnMemory
{
public:
    /**
     * x,y,w,h is in screen coord
     * w,h is now invalid
    */
    KWidget(uint8_t x, uint8_t y, uint8_t w, uint8_t h);
    ~KWidget();

    void addChild(KWidget*);

    void removeChild(KWidget*);

    void setVisible(bool isVisible);

protected:
    virtual int event(const KEvent&);

    virtual void paint();

    bool isVisible;

    uint8_t x, y, w, h;
private:
    KWidget* childs[K_WIDGET_MAX_CHILD_NUM];
};

#endif
