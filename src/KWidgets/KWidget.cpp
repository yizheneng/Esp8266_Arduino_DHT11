#include "KWidget.h"
#include <string.h>
#define bzero(a, b)             memset(a, 0, b)

extern uint8_t OLED_GRAM[144][8];

KWidget::KWidget(uint8_t x, uint8_t y, uint8_t w, uint8_t h) :
    DrawOnMemory((uint8_t*)OLED_GRAM, x, y, w, h),
    isVisible(true),
    x(x),
    y(y),
    w(w),
    h(h),
    alignmentFlag(AlignHCenter|AlignVCenter),
    isFoused(false)
{
    bzero(childs, sizeof(childs));
}

KWidget::~KWidget()
{
}

void KWidget::setVisible(bool isVisible)
{
    this->isVisible = isVisible;
}

void KWidget::addChild(KWidget* child)
{
    for(int i = 0; i < K_WIDGET_MAX_CHILD_NUM; i++) {
        if(childs[i] == 0) {
            childs[i] = child;
            return;
        }
    }
}

int KWidget::event(const KEventCode& event)
{
    if(!isVisible) {
        return 0;
    }

    for(int i = 0; i < K_WIDGET_MAX_CHILD_NUM; i++) {
        if((childs[i] != 0) && childs[i]->isVisible) {
            childs[i]->event(event);
        }
    }

    return 0;
}

void KWidget::paint()
{
    if(!isVisible) {
        return;
    }

    for(int i = 0; i < K_WIDGET_MAX_CHILD_NUM; i++) {
        if((childs[i] != 0) && childs[i]->isVisible) {
            childs[i]->paint();
        }
    }
}

void KWidget::setAlignment(uint8_t val)
{
    alignmentFlag = val;
}

void KWidget::setFoused(bool val)
{
    isFoused = val;
}
