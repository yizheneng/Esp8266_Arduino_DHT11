#ifndef _K_EVENT_H_
#define _K_EVENT_H_
#include <stdint.h>
typedef uint64_t KEventCode;

class KEvent
{
public:
    KEvent(KEventCode code);
    ~KEvent();

    uint32_t getClass();

    uint32_t getData();
private:
    KEventCode code; 
};

#endif
