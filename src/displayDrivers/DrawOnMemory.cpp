#include "DrawOnMemory.h"
#include "font/ascii_font.h"
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
using namespace std;

DrawOnMemory::DrawOnMemory(uint8_t* gramPtr) :
    gramPtr(gramPtr),
    lastX(0),
    lastY(0),
    fontWidth(6),
    fontHeight(8),
    isFontInFlash(false),
    fontPtr((uint8_t*)asc2_0806),
    mode(1),
    minX(0),
    minY(0),
    maxX(DRAW_MAX_X),
    maxY(DRAW_MAX_Y),
    x(0),
    y(0),
    w(DRAW_MAX_X),
    h(DRAW_MAX_Y)
{

}

DrawOnMemory::DrawOnMemory(uint8_t* gramPtr, uint8_t x, uint8_t y, uint8_t w, uint8_t h) :
  gramPtr(gramPtr),
  lastX(0),
  lastY(0),
  fontWidth(6),
  fontHeight(8),
  isFontInFlash(false),
  fontPtr((uint8_t*)asc2_0806),
  mode(1),
  minX(x),
  minY(y),
  maxX(x + w),
  maxY(y + h + 1),
  x(x),
  y(y),
  w(w),
  h(h)
{

}

void DrawOnMemory::setGeometry(uint8_t x, uint8_t y, uint8_t w, uint8_t h)
{
  minX = x;
  minY = y;
  maxX = x + w;
  maxY = y + h + 1;
  this->x = x;
  this->y = y;
  this->w = w;
  this->h = h;
}

//画点 
//x:0~127
//y:0~63
//t:1 填充 0,清空  
void DrawOnMemory::drawPoint(int16_t x,int16_t y,uint8_t t)
{
  drawPoint(x, y, t, minX, minY, maxX, maxY);
}

void DrawOnMemory::drawPoint(int16_t x, int16_t y, uint8_t mode, int16_t tempMinX, int16_t tempMinY, int16_t tempMaxX, int16_t tempMaxY)
{
    int16_t i,m,n;
    lastX = x;
    lastY = y;

    if((x >= DRAW_MAX_X)
       || (y >= DRAW_MAX_Y)
       || (x < tempMinX)
       || (y < tempMinY)
       || (x > tempMaxX)
       || (y > tempMaxY)) {
      return;
    }

    i=y/8;
    m=y%8;
    n=1<<m;
    uint8_t (*p)[8] = (uint8_t (*)[8])gramPtr;
    if(mode) {
      p[x][i]|=n;
    } else {
      p[x][i]=~p[x][i];
      p[x][i]|=n;
      p[x][i]=~p[x][i];
    }
}

void DrawOnMemory::drawRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t mode, uint8_t isFull)
{
  if(isFull) {
    for(int i = 0; i <= h; i ++) {
      drawLine(x, y + i, x + w, y + i, mode);
    }
  } else {
    drawLine(x, y, x + w, y, mode);
    drawLine(x + w, y, x + w, y + h, mode);
    drawLine(x, y, x, y + h, mode);
    drawLine(x, y + h, x + w + 1, y + h, mode);
  }
}

void DrawOnMemory::drawProcessBar(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t mode, uint8_t per)
{
  drawRect(x, y, w, h, mode, false);

  if(per >= 100) {
    per = 100;
  }

  uint16_t tempW = (w - 4) * per / 100;
  drawRect(x + 2, y + 2, tempW, h - 4, mode, true);
}

//x,y:圆心坐标
//r:圆的半径
void DrawOnMemory::drawCircle(uint8_t x,uint8_t y,uint8_t r)
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

void DrawOnMemory::drawLine(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2,uint8_t mode)
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
void DrawOnMemory::showChar(int16_t x, int16_t y, uint16_t chr, uint8_t mode)
{
    showChar(x, y, chr, mode, minX, minY, maxX, maxY);
}

void DrawOnMemory::showChar(int16_t x, int16_t y, uint16_t chr, uint8_t mode, int16_t tempMinX, int16_t tempMinY, int16_t tempMaxX, int16_t tempMaxY)
{
    int16_t i,m,temp,chr1;
    int16_t x0=x,y0=y;

    if(isFontInFlash) {
      int tempFontWidth = fontWidth;

      if(chr < 0x7F) {
        tempFontWidth = fontWidth/2;
      }

      int byteSize = fontHeight*tempFontWidth/8;
      uint8_t* tempData = (uint8_t*)calloc(byteSize, sizeof(char));
      if(chr <= 0x7F) {
        memcpy(tempData, fontPtr + chr*byteSize, byteSize);
      } else {
        chr = chr - 0x4E00;
        memcpy(tempData, fontPtr + chr*byteSize + 128 * 16, byteSize);
      }

      for(int i=0; i < byteSize; i++) {
        temp = tempData[i];
        for(m=0;m<8;m++) {
          if(temp&0x01)
              drawPoint(x, y, mode, tempMinX, tempMinY, tempMaxX, tempMaxY);
          else
              drawPoint(x, y, !mode, tempMinX, tempMinY, tempMaxX, tempMaxY);

          temp>>=1;
          y++;
        }
        x++;
        if((x-x0)%tempFontWidth == 0) {
          x = x0;
          y0 = y0+8;
        }
        y=y0;
      }
      free(tempData);
    } else {
       int byteSize = 0;
       if(fontHeight==8)
        byteSize=6;
      else
        byteSize=(fontHeight/8+((fontHeight%8)?1:0))*(fontHeight/2);  //得到字体一个字符对应点阵集所占的字节数
      chr1=chr-' ';  //计算偏移后的值
      for(i=0;i<byteSize;i++) {
        temp=fontPtr[chr1*byteSize + i]; //调用0806字体
        for(m=0;m<8;m++) {
          if(temp&0x01) drawPoint(x, y, mode, tempMinX, tempMinY, tempMaxX, tempMaxY);
          else drawPoint(x, y, !mode, tempMinX, tempMinY, tempMaxX, tempMaxY);
          temp>>=1;
          y++;
        }
        x++;
        if((fontHeight!=8)&&((x-x0)==fontHeight/2)) {x=x0;y0=y0+8;}
        y=y0;
      }
    }
}

uint16_t Utf8ToUnicode(uint8_t* buf, uint8_t*& nextPtr) {
    uint16_t result = 0;
    if(!(buf[0] & 0x80)) {
        nextPtr = buf + 1;
        result = buf[0];
        return result;
    }

    if(!(buf[0] & 0x20)) {
        nextPtr = buf + 2;
        result = (buf[0] << 11 & 0xf800) | (buf[1] & 0x3F);
        return result;
    }

    if(!(buf[0] & 0x10)) {
        nextPtr = buf + 3;
        result = (buf[0] << 12 & 0xf000) | (buf[1] << 6 & 0xfc0) | (buf[2] & 0x3F);
        return result;
    }

    return result;
}

//显示字符串
//x,y:起点坐标  
//size1:字体大小 
//*chr:字符串起始地址 
//mode:0,反色显示;1,正常显示
void DrawOnMemory::showString(int16_t x, int16_t y, const char *chr, uint8_t mode)
{
    showString(x, y, chr, mode, minX, minY, maxX, maxY);
}

void DrawOnMemory::showString(int16_t x, int16_t y, const char* chr, uint8_t mode, int16_t tempMinX, int16_t tempMinY, int16_t tempMaxX, int16_t tempMaxY)
{
    if(isFontInFlash) {
      uint8_t* next = (uint8_t*)chr;
      uint16_t code = 0;
      while (next[0]) {
        code = Utf8ToUnicode(next, next);
        showChar(x, y, code, mode, tempMinX, tempMinY, tempMaxX, tempMaxY);
        if(code <= 0x7F) {
          x += fontWidth/2; // 英文字符的宽度是中文的一半
        } else {
          x += fontWidth;
        }
      }
    } else {
      while((*chr>=' ')&&(*chr<='~')) {
        showChar(x, y, *chr, mode, tempMinX, tempMinY, tempMaxX, tempMaxY);
        x += fontWidth;
        chr++;
      }
    }
}

int16_t DrawOnMemory::getStringWidth(const char* chr)
{
  uint8_t* next = (uint8_t*)chr;
  uint16_t code = 0;
  uint16_t width = 0;
  if(fontHeight >= 16) { // 判断为中文字符集
    while (next[0]) {
      code = Utf8ToUnicode(next, next);
      if(code <= 0x7F) {
        width += fontWidth/2; // 英文字符的宽度是中文的一半
      } else {
        width += fontWidth;
      }
    }  
    return width;
  } else {
    return strlen(chr) * fontWidth;
  }
  
}

void DrawOnMemory::showPicture(uint8_t x, uint8_t y, uint8_t width, uint8_t height, const uint8_t* data)
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

void DrawOnMemory::showPictureInFlash(uint8_t x, uint8_t y, uint8_t width, uint8_t height, const uint8_t* data)
{
  uint8_t* tempData = (uint8_t*)calloc(width*height, sizeof(char));
  memcpy(tempData, data, width*height);
  showPicture(x, y, width, height, tempData);
  free(tempData);
}

void DrawOnMemory::clearDisplay()
{
  uint8_t (*p)[8] = (uint8_t (*)[8])gramPtr;
  uint8_t i,n;
  for(i=0;i<8;i++) {
     for(n=0;n<128;n++) {
       p[n][i]=0x00;//清除所有数据
    }
  }
}

void DrawOnMemory::setFont(const uint8_t* fontPtr, uint8_t w, uint8_t h, bool isFontInFlash)
{
  this->fontPtr = fontPtr;
  this->fontWidth = w;
  this->fontHeight = h;
  this->isFontInFlash = isFontInFlash;
}

void DrawOnMemory::setFont(OledFont font)
{
  switch (font)
  {
  case OLED_FONT_8X6:
    setFont((uint8_t*)asc2_0806, 6, 8, false);
    break;
  case OLED_FONT_12X6:
    setFont((uint8_t*)asc2_1206, 6, 12, false);
    break;
  case OLED_FONT_16X8:
    setFont((uint8_t*)asc2_1608, 8, 16, false);
    break;
  case OLED_FONT_24X12:
    setFont((uint8_t*)asc2_2412, 12, 24, false);
    break;
  default:
    break;
  }
}

void DrawOnMemory::showString(const char* chr)
{
  showString(lastX,lastY,chr,mode);
}

void DrawOnMemory::showChar(uint8_t chr)
{
  if((lastX + fontWidth) > (DRAW_MAX_X + 1)) {
    lastX = 0;
    lastY += fontHeight;
  }

  if((lastY + fontHeight) > (DRAW_MAX_Y + 1)) {
    lastY = 0;
  }

  if(chr == '\r') {
    lastX = 0;
    return;
  }

  if(chr == '\n') {
    lastY += fontHeight;
    return;
  }
  showChar(lastX, lastY, chr, mode);
  lastX += fontWidth;
}

void DrawOnMemory::printf(char* format, ...)
{
  char buf[100];
  
  int ret;
  va_list ap;
  va_start(ap, format);
  ret = vsnprintf(buf, sizeof(buf), format, ap);
  va_end(ap);
  showString(buf);
}
