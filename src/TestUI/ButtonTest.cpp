#include "ButtonTest.h"

ButtonTest::ButtonTest(/* args */) :
    KWidget(0, 0, 128, 64)
{
    KButton* okBtn = new KButton("OK", 0, 64 - 13, 60, 12);
    KButton* cancelBtn = new KButton("Cancel", 64, 64 - 13, 60, 12);

    okBtn->setFoused(true);
    okBtn->setFont(OLED_FONT_8X6);
    cancelBtn->setFont(OLED_FONT_8X6);

    addChild(okBtn);
    addChild(cancelBtn);
}

ButtonTest::~ButtonTest()
{
}

void ButtonTest::tickOnce()
{
    this->paint();
}
