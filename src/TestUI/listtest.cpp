#include "listtest.h"
#include "../KWidgets/KCheckBox.h"
#include "../KWidgets/KListSelect.h"

ListTest::ListTest() :
    KWidget(0, 0, 128, 64)
{
//    KCheckBox* checkBox = new KCheckBox("请选择", 0, 0, 100, 16);
//    checkBox->setChecked(true);
//    checkBox->setFoused(true);

    KListSelect* listSelect = new KListSelect(0, 0, 100, 64 - 16);
    listSelect->addChild("条目1");
    listSelect->addChild("条目2");
    listSelect->addChild("条目3");
    listSelect->addChild("条目4");

    listSelect->setSelectedIndex(0);

//    addChild(checkBox);
    addChild(listSelect);
}

void ListTest::tickOnce()
{
    this->paint();
}
