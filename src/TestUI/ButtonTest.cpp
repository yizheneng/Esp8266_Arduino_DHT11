#include "ButtonTest.h"

ButtonTest::ButtonTest(/* args */) :
    KWidget(0, 0, 128, 64)
{
    KButton* okBtn = new KButton("OK_123456789012345678", 0, 64 - 15, 60, 12);
    KButton* cancelBtn = new KButton("Cancel", 64, 64 - 15, 60, 12);
    KLabel* testLabel = new KLabel("飞流直下三千尺,疑是银河落九天.", 10, 10, 100, 20);
    testLabel->setScroll(true);

    // okBtn->setFoused(true);
    okBtn->setFont(OLED_FONT_8X6);
    cancelBtn->setFont(OLED_FONT_8X6);

    addChild(okBtn);
    addChild(cancelBtn);
    addChild(testLabel);
}

ButtonTest::~ButtonTest()
{
}

void ButtonTest::tickOnce()
{
    this->paint();
}
