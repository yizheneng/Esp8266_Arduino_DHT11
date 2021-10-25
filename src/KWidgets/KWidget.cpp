#include "KWidget.h"

KWidget::KWidget(int x, int y, int w, int h) :
    isVisible(true),
    x(x),
    y(y),
    w(w),
    h(h)
{
    memset(childs, 0, sizeof(childs));
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
        }
    }
}

int KWidget::event(const KEvent&)
{
    return 0;
}

void KWidget::paint(DrawOnMemory& painter)
{
    if(!isVisible) {
        return;
    }

    for(int i = 0; i < K_WIDGET_MAX_CHILD_NUM; i++) {
        if((childs[i] != 0) && childs[i]->isVisible) {
            childs[i]->paint(painter);
        }
    }
}