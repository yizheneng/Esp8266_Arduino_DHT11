#include "listtest.h"
#include "../KWidgets/KCheckBox.h"
#include "../KWidgets/KListSelect.h"

ListTest::ListTest() :
    KWidget(0, 0, 128, 64)
{
//    KCheckBox* checkBox = new KCheckBox("请选择", 0, 0, 100, 16);
//    checkBox->setChecked(true);
//    checkBox->setFoused(true);

    KListSelect* listSelect = new KListSelect(0, 0, 128, 64);
    listSelect->addChild("条目1");
    listSelect->addChild("条目2");
    listSelect->addChild("条目32265511588");
    listSelect->addChild("条目4");

    listSelect->setSelectedIndex(0);

//    addChild(checkBox);
    addChild(listSelect);
}

int ListTest::event(const KEventCode &event)
{
    if(K_EVENT_CLASS_TICK_ONCE == K_EVENT_CLASS(event)) {
        this->paint();
    }

    return KWidget::event(event);
}
