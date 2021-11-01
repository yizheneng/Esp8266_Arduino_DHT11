#include "KListSelect.h"
#include <stdio.h>
#include "KCheckBox.h"
#include <QDebug>

KListSelect::KListSelect(uint8_t x, uint8_t y, uint8_t w, uint8_t h) :
    KWidget(x, y, w, h)
{
}

void KListSelect::addChild(const char *listContent)
{
    for(int i = 0; i < K_WIDGET_MAX_CHILD_NUM; i++) {
        if(childs[i] == 0) {
            childs[i] = new KCheckBox(listContent, x, y + i * 16, w, 16);

            if(i == 0) {
               childs[i]->setFoused(true);
            }
            return;
        }
    }
}

void KListSelect::setSelectedIndex(uint8_t val)
{
    if(val >= K_WIDGET_MAX_CHILD_NUM)
        return;

    if(childs[val] != 0) {
        ((KCheckBox*)childs[val])->setChecked(true);
    } else {
        return;
    }

    for(int i = 0; i < K_WIDGET_MAX_CHILD_NUM; i++) {
        if(childs[i] != 0) {
            ((KCheckBox*)childs[i])->setChecked(false);
        }
    }
}

int KListSelect::event(const KEventCode &e)
{
    if((K_EVENT_CLASS(e) == K_EVENT_CLASS_KEY)
            && (K_EVENT_DATA(e) == K_EVENT_KEY_OK)) {
        for(int i = 0; i < K_WIDGET_MAX_CHILD_NUM; i++) {
            if((childs[i] != 0)) {
                if(childs[i]->isFoused)
                    ((KCheckBox*)childs[i])->setChecked(true);
                else
                    ((KCheckBox*)childs[i])->setChecked(false);
            }
        }
        return 0;
    }

    return KWidget::event(e);
}
