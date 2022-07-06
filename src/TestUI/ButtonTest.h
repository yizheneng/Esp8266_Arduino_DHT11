#ifndef _BUTTON_TEST_H_
#define _BUTTON_TEST_H_
#include "../KWidgets/KWidget.h"
#include "../KWidgets/KButton.h"
#include "../KWidgets/KLabel.h"

class ButtonTest : public KWidget
{
public:
    ButtonTest(/* args */);
    ~ButtonTest();

    virtual int event(const KEventCode&);
    
private:
    KLabel* testLabel;
};


#endif
