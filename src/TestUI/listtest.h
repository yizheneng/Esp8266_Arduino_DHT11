#ifndef LISTTEST_H
#define LISTTEST_H
#include "../KWidgets/KWidget.h"
class ListTest  : public KWidget
{
public:
    ListTest();

    virtual int event(const KEventCode&);
};

#endif // LISTTEST_H
