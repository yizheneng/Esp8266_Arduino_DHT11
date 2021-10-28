#ifndef _K_EVENT_H_
#define _K_EVENT_H_
#include <stdint.h>
typedef uint64_t KEventCode;

#define K_EVENT(class,data)  ((class<<32&0xffffffff00000000)|(data&0xffffffff))
#define K_EVENT_CLASS(event) (event>>32)
#define K_EVENT_DATA(event)  (event&0xffffffff)

enum KEventClass {
    K_EVENT_CLASS_USER_BUTTON = 0,
    K_EVENT_CLASS_KEY,
    K_EVENT_CLASS_TICK_ONCE,
};

enum KEventKey {
    K_EVENT_KEY_UP = 0,
    K_EVENT_KEY_DOWN,
    K_EVENT_KEY_LEFT,
    K_EVENT_KEY_RIGHT,
};

// 需匹配按键的状态
enum KEventUserButton {
  K_EVENT_USER_BUTTON_NO_PRESS = 0,
  K_EVENT_USER_BUTTON_PRESSING,
  K_EVENT_USER_BUTTON_SHORT_PRESS,
  K_EVENT_USER_BUTTON_LONG_PRESS,
};

// class KEvent
// {
// public:
//     KEvent(KEventCode code);
//     ~KEvent();

//     uint32_t getClass();

//     uint32_t getData();
// private:
//     KEventCode code; 
// };

#endif
