#include <stdint.h>

#ifdef __AVR__
  #include <avr/pgmspace.h>
  #define OLEDFONT(name) static const uint8_t __attribute__ ((progmem)) name[]
#elif defined(ESP8266)
  #include <pgmspace.h>
  #define OLEDFONT(name) static const uint8_t name[]
#else
  #define pgm_read_byte(addr) (*(const unsigned char *)(addr))
  #define OLEDFONT(name) static const uint8_t name[]
#endif

#define OLED_PRINT(...) {\
                        snprintf(printBuf, sizeof(printBuf) - 1, __VA_ARGS__);\
                        oled.showString(printBuf);} // must define(char printBuf[100];) printBuf before use

enum OledFont {
  OLED_FONT_8X6 = 8,
  OLED_FONT_12X6 = 12,
  OLED_FONT_16X8 = 16,
  OLED_FONT_24X12 = 24,
};

class SSD1306SPI 
{
public:
  SSD1306SPI(int csPin, int resPin, int dcPin, int sclkPin, int sdioPin);

  void begin();

  void drawPoint(uint8_t x, uint8_t y, uint8_t t);

  void drawCircle(uint8_t x, uint8_t y, uint8_t r);

  void drawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t mode);
 
  void showChar(uint8_t x, uint8_t y, uint8_t chr, uint8_t size1, uint8_t mode);

  void showChar(uint8_t chr);

  void showString(uint8_t x, uint8_t y, const char* chr, uint8_t size1, uint8_t mode);

  void showString(const char* chr);

  void sync(void);

  void setFontSize(const OledFont font);

  void setXY(const int8_t x, const int8_t y) {
    this->x = x;
    this->y = y;
  }
  
private:
  void sendCommand(int8_t cmd);

  void sendData(int8_t data);

  void write(int8_t data, bool isData);

  void setFont(const uint8_t* font, bool inverse = false);

  void clearDisplay();

  bool putChar(unsigned char ch);

  void init(void);

  int csPin;
  int resPin;
  int dcPin;
  int sclkPin;
  int sdioPin;

  OledFont font;
  int8_t x;
  int8_t y;
  int8_t fontWidth;
  int8_t fontHeight;

  uint8_t OLED_GRAM[144][8];  // cache
};
