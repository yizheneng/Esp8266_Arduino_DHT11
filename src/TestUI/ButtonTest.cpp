#include "ButtonTest.h"
#include "../KWidgets/KCheckBox.h"

ButtonTest::ButtonTest(/* args */) :
    KWidget(0, 0, 128, 64)
{
    KButton* okBtn = new KButton("OK", 0, 64 - 15, 60, 12);
    KButton* cancelBtn = new KButton("Cancel", 64, 64 - 15, 60, 12);
    testLabel = new KLabel("你好123456789123456789", 0, 0, 128, 16);
    testLabel->setScroll(true);

    KCheckBox* chooseBox = new KCheckBox("请选择这个选项吧,有惊喜啊", 0, 16, 100, 16);
    chooseBox->setScroll(true);
//    chooseBox->setChecked(true);
//    chooseBox->setFoused(true);

    // okBtn->setFoused(true);
    okBtn->setFont(OLED_FONT_8X6);
    cancelBtn->setFont(OLED_FONT_8X6);

    addChild(okBtn);
    addChild(cancelBtn);
    addChild(testLabel);
//    addChild(chooseBox);
}

ButtonTest::~ButtonTest()
{
}

int ButtonTest::event(const KEventCode &event)
{
    if(K_EVENT_CLASS_TICK_ONCE == K_EVENT_CLASS(event)) {
        this->paint();
    }

    return KWidget::event(event);
}
