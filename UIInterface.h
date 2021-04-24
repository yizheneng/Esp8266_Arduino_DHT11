#ifndef _UI_INTERFACE_
#define _UI_INTERFACE_
#include <stdint.h>

class UIInterface {
public:
  virtual void enter() = 0;      // 切换界面时，会调用此函数
  virtual int8_t tickOnce() = 0; // 定时调用该接口用于刷新界面逻辑,当前界面需要退出时，将返回要进入的界面ID即可，不需退出时，则返回-1

  const uint8_t* getGRam() {     // 获取当前页的页面缓存
    return (uint8_t*)OLED_GRAM;
  }
protected:
  uint8_t OLED_GRAM[144][8];     // 当前页面缓存
};

#endif
