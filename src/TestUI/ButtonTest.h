#ifndef _BUTTON_TEST_H_
#define _BUTTON_TEST_H_
#include "../KWidgets/KWidget.h"
#include "../KWidgets/KButton.h"

class ButtonTest : public KWidget
{
public:
    ButtonTest(/* args */);
    ~ButtonTest();

    void tickOnce();
private:
    /* data */
};


#endif