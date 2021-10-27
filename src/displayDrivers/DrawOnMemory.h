#ifndef _DRAW_ON_MEMORY_H_
#define _DRAW_ON_MEMORY_H_
#include <stdint.h>
enum OledFont { // 这些字库内不含ASCII码以外的字符
  OLED_FONT_8X6 = 8,
  OLED_FONT_12X6 = 12,
  OLED_FONT_16X8 = 16,
  OLED_FONT_24X12 = 24, 
};

class DrawOnMemory
{
public:
    DrawOnMemory(uint8_t* gramPtr);

    void drawPoint(uint8_t x, uint8_t y, uint8_t t);

    void drawCircle(uint8_t x, uint8_t y, uint8_t r);

    void drawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t mode);

    void drawRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t mode, uint8_t isFull);

    void drawProcessBar(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t mode, uint8_t per);

    void showChar(uint8_t x, uint8_t y, uint16_t chr, uint8_t mode);

    void showChar(uint8_t chr);

    void showString(uint8_t x, uint8_t y, const char* chr, uint8_t mode);

    void showString(const char* chr);

    void showPicture(uint8_t x, uint8_t y, uint8_t width, uint8_t height, const uint8_t* data);

    void showPictureInFlash(uint8_t x, uint8_t y, uint8_t width, uint8_t height, const uint8_t* data);

    void setFont(const uint8_t* fontPtr, uint8_t w, uint8_t h, bool isFontInFlash);

    void setFont(OledFont font);

    void clearDisplay();

    void printf(char* format, ...);

    int16_t getStringWidth(const char* chr);

    void setXY(const int8_t x, const int8_t y) {
      this->x = x;
      this->y = y;
    } 

    // 0 反色显示 1 正常显示
    void setDisplayMode(int val) {
      mode = val;
    }

protected:
    int8_t x, y, mode, lastX, lastY;

    const uint8_t* fontPtr;
    int8_t fontWidth;
    int8_t fontHeight;
    bool isFontInFlash;

    uint8_t* gramPtr;
};


#endif