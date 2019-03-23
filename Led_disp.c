#include "Led_disp.h"
#include <msp430f249.h>
extern uchar RunMode;
extern uchar LEDDirection,LEDFlag;//LEDDirection为1时向左，LEDFlag为1时全亮
extern uint LEDIndex; //初始为0


void (*run[8])(void) = 
{Mode_0,Mode_1,Mode_2,Mode_3,Mode_4,Mode_5,Mode_6,Mode_7};


void LEDShow(uint LEDStatus) //输入16位数，1为亮，实现点亮LED
{
  P1OUT =~ (LEDStatus & 0x00FF);
  P4OUT =~ ((LEDStatus >> 8) & 0x00FF);
}

void delayus(uint t) //延时
{
  uint i;
  while (t--)
  {
    for(i=1000;i>0;i--);
  }
}
void Mode_0() //以LED0，1，2的顺序点亮，到LED15时重新开始
{
  LEDShow(0x0001 << LEDIndex);
  LEDIndex = (LEDIndex + 1) %16;
}

void Mode_1()//以LED15，14，13的顺序点亮，到LED0时重新开始
{
  LEDShow(0x8000 >> LEDIndex);
  LEDIndex = (LEDIndex + 1) %16;
}

void Mode_2()//LEDDirection为1时从LED0开始亮，到LED15时返回
{
  if (LEDDirection) //1为向左
    LEDShow(0x0001 << LEDIndex);
  else
    LEDShow(0x8000 >> LEDIndex);
  if (LEDIndex == 15) //到15取反
    LEDDirection =! LEDDirection;
  LEDIndex = (LEDIndex + 1) % 16; //自加1  
}

void Mode_3()//初始全亮，LEDDirection为1时从LED0开始暗，到LED15时返回
{
  if (LEDDirection) //1为向左
    LEDShow(~(0x0001 << LEDIndex));
  else
    LEDShow(~(0x8000 >> LEDIndex));
  if (LEDIndex == 15) //到15取反
    LEDDirection =! LEDDirection;
  LEDIndex = (LEDIndex + 1) % 16; //自加1  
}

void Mode_4()//花式移动
{
  if (LEDDirection) //1为向左
  {
    if (LEDFlag) //1为全亮
      LEDShow(0xFFFE << LEDIndex);  
    else //全暗
      LEDShow(~(0x7FFF >> LEDIndex));
  }
  else //向右
  {
    if (LEDFlag) //1为全亮
      LEDShow(0x7FFF >> LEDIndex);  
    else //全暗
      LEDShow(~(0xFFFE << LEDIndex));
  }
  if (LEDIndex == 15) //到15取反
  {
    LEDDirection =! LEDDirection;
    if (!LEDDirection) LEDFlag =! LEDFlag; //按（1,1),(0,0),(1,0),(0,1)的顺序
  }
  LEDIndex = (LEDIndex + 1) % 16; //自加1  
}

void Mode_5() //连续四个亮
{
  if (LEDDirection) //1为向左
    LEDShow(0x000F << LEDIndex);
  else
    LEDShow(0xF000 >> LEDIndex);
  if (LEDIndex == 11) //到11取反
    LEDDirection =! LEDDirection;
  LEDIndex = (LEDIndex + 1) % 12; //自加1  
}

void Mode_6() //连续四个暗
{
  if (LEDDirection) //1为向左
    LEDShow(~(0x000F << LEDIndex));
  else
    LEDShow(~(0xF000 >> LEDIndex));
  if (LEDIndex == 11) //到11取反
    LEDDirection =! LEDDirection;
  LEDIndex = (LEDIndex + 1) % 12; //自加1  
}

void Mode_7() //二进制加法
{
  LEDShow(++LEDIndex);
}







