#include "SSD1306SPI.h"
#include <Arduino.h>
#include "oledfont.h"

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
  sdioPin(sdioPin),
  font(OLED_FONT_8X6),
  x(0),
  y(0),
  fontWidth(6),
  fontHeight(8)
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
  sync();
}

//画点 
//x:0~127
//y:0~63
//t:1 填充 0,清空  
void SSD1306SPI::drawPoint(uint8_t x,uint8_t y,uint8_t t)
{
  uint8_t i,m,n;
  i=y/8;
  m=y%8;
  n=1<<m;
  if(t){OLED_GRAM[x][i]|=n;}
  else
  {
    OLED_GRAM[x][i]=~OLED_GRAM[x][i];
    OLED_GRAM[x][i]|=n;
    OLED_GRAM[x][i]=~OLED_GRAM[x][i];
  }
}

//x,y:圆心坐标
//r:圆的半径
void SSD1306SPI::drawCircle(uint8_t x,uint8_t y,uint8_t r)
{
  int a, b,num;
  a = 0;
  b = r;
  while(2 * b * b >= r * r) {
      drawPoint(x + a, y - b,1);
      drawPoint(x - a, y - b,1);
      drawPoint(x - a, y + b,1);
      drawPoint(x + a, y + b,1);

      drawPoint(x + b, y + a,1);
      drawPoint(x + b, y - a,1);
      drawPoint(x - b, y - a,1);
      drawPoint(x - b, y + a,1);
      
      a++;
      num = (a * a + b * b) - r*r;//计算画的点离圆心的距离
      if(num > 0) {
          b--;
          a--;
      }
  }
}

void SSD1306SPI::drawLine(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2,uint8_t mode)
{
  uint16_t t; 
  int xerr=0,yerr=0,delta_x,delta_y,distance;
  int incx,incy,uRow,uCol;
  delta_x=x2-x1; //计算坐标增量 
  delta_y=y2-y1;
  uRow=x1;//画线起点坐标
  uCol=y1;
  if(delta_x>0)incx=1; //设置单步方向 
  else if (delta_x==0)incx=0;//垂直线 
  else {incx=-1;delta_x=-delta_x;}
  if(delta_y>0)incy=1;
  else if (delta_y==0)incy=0;//水平线 
  else {incy=-1;delta_y=-delta_x;}
  if(delta_x>delta_y)distance=delta_x; //选取基本增量坐标轴 
  else distance=delta_y;
  for(t=0;t<distance+1;t++) {
    drawPoint(uRow,uCol, mode);//画点
    xerr+=delta_x;
    yerr+=delta_y;
    if(xerr>distance) {
      xerr-=distance;
      uRow+=incx;
    }
    
    if(yerr>distance) {
      yerr-=distance;
      uCol+=incy;
    }
  }
}

//在指定位置显示一个字符,包括部分字符
//x:0~127
//y:0~63
//size1:选择字体 6x8/6x12/8x16/12x24
//mode:0,反色显示;1,正常显示
void SSD1306SPI::showChar(uint8_t x,uint8_t y,uint8_t chr,uint8_t size1,uint8_t mode)
{
  uint8_t i,m,temp,size2,chr1;
  uint8_t x0=x,y0=y;
  if(size1==8)size2=6;
  else size2=(size1/8+((size1%8)?1:0))*(size1/2);  //得到字体一个字符对应点阵集所占的字节数
  chr1=chr-' ';  //计算偏移后的值
  for(i=0;i<size2;i++) {
    if(size1==8) {temp=asc2_0806[chr1][i];} //调用0806字体
    else if(size1==12) {temp=asc2_1206[chr1][i];} //调用1206字体
    else if(size1==16) {temp=asc2_1608[chr1][i];} //调用1608字体
    else if(size1==24) {temp=asc2_2412[chr1][i];} //调用2412字体
    else return;
    for(m=0;m<8;m++) {
      if(temp&0x01) drawPoint(x,y,mode);
      else drawPoint(x,y,!mode);
      temp>>=1;
      y++;
    }
    x++;
    if((size1!=8)&&((x-x0)==size1/2)) {x=x0;y0=y0+8;}
    y=y0;
  }
}

//显示字符串
//x,y:起点坐标  
//size1:字体大小 
//*chr:字符串起始地址 
//mode:0,反色显示;1,正常显示
void SSD1306SPI::showString(uint8_t x,uint8_t y,const char *chr,uint8_t size1,uint8_t mode)
{
  while((*chr>=' ')&&(*chr<='~')) {
    showChar(x,y,*chr,size1,mode);
    if(size1==8)x+=6;
    else x+=size1/2;
    chr++;
  }
}

void SSD1306SPI::showPicture(uint8_t x, uint8_t y, uint8_t width, uint8_t height, const uint8_t* data)
{
  uint16_t j=0;
  uint8_t i,n,temp,m;
  uint8_t x0=x, y0=y;
  height = height/8+((height%8)?1:0);
  for(n=0;n<height;n++) {
     for(i=0;i<width;i++) {
        temp = data[j];
        j++;
        for(m=0;m<8;m++) {
          if(temp&0x01) 
            drawPoint(x, y, 1);
          else 
            drawPoint(x, y, !1);
          temp>>=1;
          y++;
        }
        x++;
        if((x-x0)==width) {
          x=x0;
          y0=y0+8;
        }
        y=y0;
    }
  }
}

void SSD1306SPI::showPictureInFlash(uint8_t x, uint8_t y, uint8_t width, uint8_t height, const uint8_t* data)
{
  uint8_t* tempData = (uint8_t*)calloc(width*height, sizeof(char));
  memcpy(tempData, data, width*height);
  showPicture(x, y, width, height, tempData);
  free(tempData);
}

void SSD1306SPI::clearDisplay()
{
  u8 i,n;
  for(i=0;i<8;i++) {
     for(n=0;n<128;n++) {
       OLED_GRAM[n][i]=0x00;//清除所有数据
    }
  }
  sync();//更新显示
}

//更新显存到OLED  
void SSD1306SPI::sync(void)
{
  u8 i,n;
  for(i=0;i<8;i++)
  {
     sendCommand(0xb0+i); //设置行起始地址
     sendCommand(0x00);   //设置低列起始地址
     sendCommand(0x10);   //设置高列起始地址
     for(n=0;n<128;n++)
      sendData(OLED_GRAM[n][i]);
  }
}

void SSD1306SPI::setFontSize(const OledFont font)
{
  this->font = font;
  switch (font) {
    case OLED_FONT_8X6:
      fontWidth = 6;
      fontHeight = 8;
      break;
    case OLED_FONT_12X6:
      fontWidth = 6;
      fontHeight = 12;
      break;
    case OLED_FONT_16X8:
      fontWidth = 8;
      fontHeight = 16;
      break;
    case OLED_FONT_24X12:
      fontWidth = 12;
      fontHeight = 24;
      break;
  }
}

void SSD1306SPI::showString(const char* chr)
{
  while(((*chr>=' ') && (*chr<='~')) || (*chr == '\r') ||  (*chr == '\n')) {
    showChar(*chr);
    chr++;
  }
}

void SSD1306SPI::showChar(uint8_t chr)
{
  if((x + fontWidth) > (SSD1306_Max_X + 1)) {
    x = 0;
    y += fontHeight;
  }

  if((y + fontHeight) > (SSD1306_Max_Y + 1)) {
    y = 0;
  }

  if(chr == '\r') {
    x = 0;
    return;
  }

  if(chr == '\n') {
    x = 0;
    y += fontHeight;
    return;
  }
  showChar(x, y, chr, font, 1);
  x += fontWidth;
}
