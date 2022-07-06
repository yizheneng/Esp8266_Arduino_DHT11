#ifndef _UI_INTERFACE_
#define _UI_INTERFACE_
#include <stdint.h>
#include "../KWidgets/KWidget.h"
#include "DrawOnMemory.h"

enum  UIIndex {
  UI_INDEX_MAIN_UI = 0,   // 主界面（首屏）
  UI_INDEX_WEATHER_UI,    // 天气界面
  UI_INDEX_SYSTEM_INFO_UI,// 系统信息界面
  UI_INDEX_MENU_WEATHER,  // 天气菜单
  UI_INDEX_MENU_SYSTEM_INFO, // 系统信息菜单
  UI_INDEX_MENU_SETTINGS_UI, // 系统配置菜单
  UI_INDEX_SETTINGS_UI, // 系统配置界面
  UI_INDEX_MAX
};

extern uint8_t OLED_GRAM[144][8];

class UIInterface : public KWidget {
public:
  UIInterface() :
    KWidget(0, 0, 128, 64),
    nextWidget(-1) {
  };

  UIInterface(uint8_t x, uint8_t y, uint8_t w, uint8_t h) :
    KWidget(x, y, w, h) {
  };

  virtual void enter() { // 切换界面时，会调用此函数
    nextWidget = -1;
  }      

  uint8_t* getGRam() {     // 获取当前页的页面缓存
    return (uint8_t*)OLED_GRAM;
  }

  int8_t getNextWidget() {
    return nextWidget;
  }

protected:
  int8_t nextWidget; // 下一个要切入的界面,-1:不需要切换界面
};

#endif
