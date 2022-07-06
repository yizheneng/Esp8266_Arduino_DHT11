#ifndef _K_EVENT_H_
#define _K_EVENT_H_
#include <stdint.h>
typedef uint64_t KEventCode;

#define K_EVENT(class,data)  ((class<<16&0xffff0000)|(data&0xffff))
#define K_EVENT_CLASS(event) (event>>16&0xffff)
#define K_EVENT_DATA(event)  (event&0xffff)

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
    K_EVENT_KEY_OK,
};

// 需匹配按键的状态
enum KEventUserButton {
  K_EVENT_USER_BUTTON_NO_PRESS = 0,
  K_EVENT_USER_BUTTON_PRESSING,
  K_EVENT_USER_BUTTON_SHORT_PRESS,
  K_EVENT_USER_BUTTON_LONG_PRESS,
};

#endif
