#include "KWidget.h"
#include <string.h>

extern uint8_t OLED_GRAM[144][8];

KWidget::KWidget(uint8_t x, uint8_t y, uint8_t w, uint8_t h) :
    DrawOnMemory((uint8_t*)OLED_GRAM),
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

int KWidget::event(const KEvent&)
{
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
