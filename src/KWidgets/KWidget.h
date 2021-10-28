#ifndef _K_WIDGET_H_
#define _K_WIDGET_H_
#include "KEvent.h"
#include "../displayDrivers/DrawOnMemory.h"
#define K_WIDGET_MAX_CHILD_NUM 15

class KWidget : public DrawOnMemory
{
public:
    enum AlignmentFlag {
        AlignLeft = 0x01,
        AlignRight = 0x02,
        AlignHCenter = 0x04,
        AlignTop = 0x10,
        AlignBottom = 0x20,
        AlignVCenter = 0x40,
    };
    /**
     * x,y,w,h is in screen coord
     * w,h is now invalid
    */
    KWidget(uint8_t x, uint8_t y, uint8_t w, uint8_t h);
    ~KWidget();

    void addChild(KWidget*);

    void removeChild(KWidget*);

    void setVisible(bool isVisible);

    void setAlignment(uint8_t val);

    void setFoused(bool val);

    virtual int event(const KEventCode&);
    
protected:
    virtual void paint();

    bool isVisible;

    uint8_t x, y, w, h;

    uint8_t alignmentFlag;

    bool isFoused;
private:
    KWidget* childs[K_WIDGET_MAX_CHILD_NUM];
};

#endif
