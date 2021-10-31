#include "ButtonTest.h"
#include "../KWidgets/KChooseBox.h"

ButtonTest::ButtonTest(/* args */) :
    KWidget(0, 0, 128, 64)
{
    KButton* okBtn = new KButton("OK", 0, 64 - 15, 60, 12);
    KButton* cancelBtn = new KButton("Cancel", 64, 64 - 15, 60, 12);
    KLabel* testLabel = new KLabel("你好123456789456123", 0, 0, 100, 16);
    testLabel->setScroll(true);

    KChooseBox* chooseBox = new KChooseBox("请选择这个选项吧,有惊喜啊", 0, 16, 100, 16);
    chooseBox->setScroll(true);
    chooseBox->setSelected(true);
    chooseBox->setFoused(true);

    // okBtn->setFoused(true);
    okBtn->setFont(OLED_FONT_8X6);
    cancelBtn->setFont(OLED_FONT_8X6);

    addChild(okBtn);
    addChild(cancelBtn);
    addChild(testLabel);
    addChild(chooseBox);
}

ButtonTest::~ButtonTest()
{
}

void ButtonTest::tickOnce()
{
    this->paint();
}
