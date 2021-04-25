#include "SSD1306SPI.h"
#include <Arduino.h>


#define SSD1306_Max_X                 127
#define SSD1306_Max_Y                 63

#define PAGE_MODE                     01
#define HORIZONTAL_MODE               02

#define SSD1306_Address               0x3C
#define SSD1306_Command_Mode          0x80
#define SSD1306_Data_Mode             0x40
#define SSD1306_Display_Off_Cmd       0xAE
#define SSD1306_Display_On_Cmd        0xAF
#define SSD1306_Normal_Display_Cmd    0xA6
#define SSD1306_Inverse_Display_Cmd   0xA7
#define SSD1306_Activate_Scroll_Cmd   0x2F
#define SSD1306_Dectivate_Scroll_Cmd  0x2E
#define SSD1306_Set_Brightness_Cmd    0x81

#define Scroll_Left                   0x00
#define Scroll_Right                  0x01

#define Scroll_2Frames                0x7
#define Scroll_3Frames                0x4
#define Scroll_4Frames                0x5
#define Scroll_5Frames                0x0
#define Scroll_25Frames               0x6
#define Scroll_64Frames               0x1
#define Scroll_128Frames              0x2
#define Scroll_256Frames              0x3

SSD1306SPI::SSD1306SPI(int csPin, int resPin, int dcPin, int sclkPin, int sdioPin) :
  csPin(csPin),
  resPin(resPin),
  dcPin(dcPin),
  sclkPin(sclkPin),
  sdioPin(sdioPin)
{
  
}

void SSD1306SPI::begin()
{
  pinMode(csPin, OUTPUT);
  pinMode(resPin, OUTPUT);
  pinMode(dcPin, OUTPUT);
  pinMode(sclkPin, OUTPUT);
  pinMode(sdioPin, OUTPUT);

  digitalWrite(csPin, HIGH);
  digitalWrite(resPin, HIGH);
  digitalWrite(dcPin, HIGH);
  digitalWrite(sclkPin, HIGH);
  digitalWrite(sdioPin, HIGH);
  init();
}

void SSD1306SPI::write(int8_t data, bool isData)
{
  digitalWrite(dcPin, isData ? HIGH : LOW);
  digitalWrite(csPin, LOW);
  for(int i = 0; i < 8; i ++) {
      digitalWrite(sclkPin, LOW);
      //delay(1);
      digitalWrite(sdioPin, (data & 0x80) > 0 ? HIGH : LOW);
      digitalWrite(sclkPin, HIGH);
      //delay(1);
      data <<= 1;
  }
  digitalWrite(csPin, HIGH);
  digitalWrite(dcPin, HIGH);
}

void SSD1306SPI::sendCommand(int8_t cmd)
{
  write(cmd, false);
}

void SSD1306SPI::sendData(int8_t data)
{
  write(data, true);
}

void SSD1306SPI::init(void)
{
  digitalWrite(resPin, LOW);
  delay(200);
  digitalWrite(resPin, HIGH);
  
  sendCommand(0xAE);//--turn off oled panel
  sendCommand(0x00);//---set low column address
  sendCommand(0x10);//---set high column address
  sendCommand(0x40);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
  sendCommand(0x81);//--set contrast control register
  sendCommand(0xCF);// Set SEG Output Current Brightness
  sendCommand(0xA1);//--Set SEG/Column Mapping     0xa0左右反置 0xa1正常
  sendCommand(0xC8);//Set COM/Row Scan Direction   0xc0上下反置 0xc8正常
  sendCommand(0xA6);//--set normal display
  sendCommand(0xA8);//--set multiplex ratio(1 to 64)
  sendCommand(0x3f);//--1/64 duty
  sendCommand(0xD3);//-set display offset Shift Mapping RAM Counter (0x00~0x3F)
  sendCommand(0x00);//-not offset
  sendCommand(0xd5);//--set display clock divide ratio/oscillator frequency
  sendCommand(0x80);//--set divide ratio, Set Clock as 100 Frames/Sec
  sendCommand(0xD9);//--set pre-charge period
  sendCommand(0xF1);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
  sendCommand(0xDA);//--set com pins hardware configuration
  sendCommand(0x12);
  sendCommand(0xDB);//--set vcomh
  sendCommand(0x40);//Set VCOM Deselect Level
  sendCommand(0x20);//-Set Page Addressing Mode (0x00/0x01/0x02)
  sendCommand(0x02);//
  sendCommand(0x8D);//--set Charge Pump enable/disable
  sendCommand(0x14);//--set(0x10) disable
  sendCommand(0xA4);// Disable Entire Display On (0xa4/0xa5)
  sendCommand(0xA6);// Disable Inverse Display On (0xa6/a7) 
  clearDisplay();
  sendCommand(0xAF);
  sendCommand(SSD1306_Display_On_Cmd);
}

void SSD1306SPI::clearDisplay()
{
  u8 i,n;
  for(i=0;i<8;i++)
  {
     sendCommand(0xb0+i); //设置行起始地址
     sendCommand(0x00);   //设置低列起始地址
     sendCommand(0x10);   //设置高列起始地址
     for(n=0;n<128;n++)
      sendData(0x00);
  }
}

//更新显存到OLED  
void SSD1306SPI::syncDisplay(uint8_t* gram)
{
  uint8_t (*p)[8] = (uint8_t (*)[8])gram;
  u8 i,n;
  for(i=0;i<8;i++)
  {
     sendCommand(0xb0+i); //设置行起始地址
     sendCommand(0x00);   //设置低列起始地址
     sendCommand(0x10);   //设置高列起始地址
     for(n=0;n<128;n++)
      sendData(p[n][i]);
  }
}
