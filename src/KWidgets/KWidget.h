#ifndef _K_WIDGET_H_
#define _K_WIDGET_H_
#include "KEvent.h"
#include "../displayDrivers/DrawOnMemory.h"
#define K_WIDGET_MAX_CHILD_NUM 10

class KWidget
{
public:
    /**
     * x,y,w,h is in screen coord
     * w,h is now invalid
    */
    KWidget(int x, int y, int w, int h);
    ~KWidget();

    void addChild(KWidget*);

    void removeChild(KWidget*);

    void setVisible(bool isVisible);
protected:
    virtual int event(const KEvent&);

    virtual void paint(DrawOnMemory& painter);

    bool isVisible;

    int x, y, w, h;
private:
    KWidget* childs[K_WIDGET_MAX_CHILD_NUM];
};

#endif
