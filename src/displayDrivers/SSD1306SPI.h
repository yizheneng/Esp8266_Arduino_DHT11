#ifndef _SSD_1306_SPI_
#define _SSD_1306_SPI_
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

class SSD1306SPI 
{
public:
  SSD1306SPI(int csPin, int resPin, int sclkPin, int sdioPin);

  void begin();

  void syncDisplay(uint8_t* gram);
  
  void clearDisplay();
private:
  void sendCommand(int8_t cmd);

  void sendData(int8_t data);

  void write(int8_t data, bool isData);

  bool putChar(unsigned char ch);

  void init(void);

  int csPin;
  int resPin;
  int sclkPin;
  int sdioPin;
};

#endif
