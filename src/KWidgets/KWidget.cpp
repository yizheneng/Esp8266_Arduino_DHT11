#include "KWidget.h"

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
            if(i == 0) {
                child->setFoused(true);
            }
            return;
        }
    }
}


int KWidget::event(const KEventCode& event)
{
    if(!isVisible) {
        return 0;
    }

    switch (K_EVENT_CLASS(event)) {
    case K_EVENT_CLASS_KEY: {
        int8_t currentFused = 0;
        for(int i = 0; i < K_WIDGET_MAX_CHILD_NUM; i++) {
            if((childs[i] != 0) && childs[i]->isVisible && childs[i]->isFoused) {
                currentFused = i;
                 childs[i]->setFoused(false);
            }
        }

        if((K_EVENT_DATA(event) == K_EVENT_KEY_UP)
                || (K_EVENT_DATA(event) == K_EVENT_KEY_LEFT)) {
            currentFused --;
            if(currentFused < 0) {
                currentFused = childNum() - 1;
            }
        }

        if((K_EVENT_DATA(event) == K_EVENT_KEY_DOWN)
                || (K_EVENT_DATA(event) == K_EVENT_KEY_RIGHT)) {
            currentFused ++;
            if(currentFused >= childNum()) {
                currentFused = 0;
            }
        }

        childs[currentFused]->setFoused(true);
        childs[currentFused]->event(event);
        break;
    }
    default:
        for(int i = 0; i < K_WIDGET_MAX_CHILD_NUM; i++) {
            if((childs[i] != 0) && childs[i]->isVisible) {
                childs[i]->event(event);
            }
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

uint8_t KWidget::childNum()
{
    for(int i = 0; i < K_WIDGET_MAX_CHILD_NUM; i++) {
        if(childs[i] == 0) {
            return i;
        }
    }

    return 0;
}
