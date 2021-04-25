#include "DrawOnMemory.h"
#include "oledfont.h"
#include <Arduino.h>
#define DRAW_MAX_X 128
#define DRAW_MAX_Y 64

DrawOnMemory::DrawOnMemory(uint8_t* gramPtr) :
    gramPtr(gramPtr),
    font(OLED_FONT_8X6),
    x(0),
    y(0),
    fontWidth(6),
    fontHeight(8)
{

}

//画点 
//x:0~127
//y:0~63
//t:1 填充 0,清空  
void DrawOnMemory::drawPoint(uint8_t x,uint8_t y,uint8_t t)
{
  uint8_t i,m,n;
  i=y/8;
  m=y%8;
  n=1<<m;
  uint8_t (*p)[8] = (uint8_t (*)[8])gramPtr;
  if(t){p[x][i]|=n;}
  else
  {
    p[x][i]=~p[x][i];
    p[x][i]|=n;
    p[x][i]=~p[x][i];
  }
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
void DrawOnMemory::showChar(uint8_t x,uint8_t y,uint8_t chr,uint8_t size1,uint8_t mode)
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
void DrawOnMemory::showString(uint8_t x,uint8_t y,const char *chr,uint8_t size1,uint8_t mode)
{
  while((*chr>=' ')&&(*chr<='~')) {
    showChar(x,y,*chr,size1,mode);
    if(size1==8)x+=6;
    else x+=size1/2;
    chr++;
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
  u8 i,n;
  for(i=0;i<8;i++) {
     for(n=0;n<128;n++) {
       p[n][i]=0x00;//清除所有数据
    }
  }
}

void DrawOnMemory::setFontSize(const OledFont font)
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

void DrawOnMemory::showString(const char* chr)
{
  while(((*chr>=' ') && (*chr<='~')) || (*chr == '\r') ||  (*chr == '\n')) {
    showChar(*chr);
    chr++;
  }
}

void DrawOnMemory::showChar(uint8_t chr)
{
  if((x + fontWidth) > (DRAW_MAX_X + 1)) {
    x = 0;
    y += fontHeight;
  }

  if((y + fontHeight) > (DRAW_MAX_Y + 1)) {
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

void DrawOnMemory::printf(char* format, ...)
{
  char buf[100];
  
  int ret;
  va_list ap;
  va_start(ap, format);
  ret = vsniprintf(buf, sizeof(buf), format, ap);
  va_end(ap);
  showString(buf);
}
