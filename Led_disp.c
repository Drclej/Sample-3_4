#include "Led_disp.h"
#include <msp430f249.h>
extern uchar RunMode;
extern uchar LEDDirection,LEDFlag;//LEDDirectionΪ1ʱ����LEDFlagΪ1ʱȫ��
extern uint LEDIndex; //��ʼΪ0


void (*run[8])(void) = 
{Mode_0,Mode_1,Mode_2,Mode_3,Mode_4,Mode_5,Mode_6,Mode_7};


void LEDShow(uint LEDStatus) //����16λ����1Ϊ����ʵ�ֵ���LED
{
  P1OUT =~ (LEDStatus & 0x00FF);
  P4OUT =~ ((LEDStatus >> 8) & 0x00FF);
}

void delayus(uint t) //��ʱ
{
  uint i;
  while (t--)
  {
    for(i=1000;i>0;i--);
  }
}
void Mode_0() //��LED0��1��2��˳���������LED15ʱ���¿�ʼ
{
  LEDShow(0x0001 << LEDIndex);
  LEDIndex = (LEDIndex + 1) %16;
}

void Mode_1()//��LED15��14��13��˳���������LED0ʱ���¿�ʼ
{
  LEDShow(0x8000 >> LEDIndex);
  LEDIndex = (LEDIndex + 1) %16;
}

void Mode_2()//LEDDirectionΪ1ʱ��LED0��ʼ������LED15ʱ����
{
  if (LEDDirection) //1Ϊ����
    LEDShow(0x0001 << LEDIndex);
  else
    LEDShow(0x8000 >> LEDIndex);
  if (LEDIndex == 15) //��15ȡ��
    LEDDirection =! LEDDirection;
  LEDIndex = (LEDIndex + 1) % 16; //�Լ�1  
}

void Mode_3()//��ʼȫ����LEDDirectionΪ1ʱ��LED0��ʼ������LED15ʱ����
{
  if (LEDDirection) //1Ϊ����
    LEDShow(~(0x0001 << LEDIndex));
  else
    LEDShow(~(0x8000 >> LEDIndex));
  if (LEDIndex == 15) //��15ȡ��
    LEDDirection =! LEDDirection;
  LEDIndex = (LEDIndex + 1) % 16; //�Լ�1  
}

void Mode_4()//��ʽ�ƶ�
{
  if (LEDDirection) //1Ϊ����
  {
    if (LEDFlag) //1Ϊȫ��
      LEDShow(0xFFFE << LEDIndex);  
    else //ȫ��
      LEDShow(~(0x7FFF >> LEDIndex));
  }
  else //����
  {
    if (LEDFlag) //1Ϊȫ��
      LEDShow(0x7FFF >> LEDIndex);  
    else //ȫ��
      LEDShow(~(0xFFFE << LEDIndex));
  }
  if (LEDIndex == 15) //��15ȡ��
  {
    LEDDirection =! LEDDirection;
    if (!LEDDirection) LEDFlag =! LEDFlag; //����1,1),(0,0),(1,0),(0,1)��˳��
  }
  LEDIndex = (LEDIndex + 1) % 16; //�Լ�1  
}

void Mode_5() //�����ĸ���
{
  if (LEDDirection) //1Ϊ����
    LEDShow(0x000F << LEDIndex);
  else
    LEDShow(0xF000 >> LEDIndex);
  if (LEDIndex == 11) //��11ȡ��
    LEDDirection =! LEDDirection;
  LEDIndex = (LEDIndex + 1) % 12; //�Լ�1  
}

void Mode_6() //�����ĸ���
{
  if (LEDDirection) //1Ϊ����
    LEDShow(~(0x000F << LEDIndex));
  else
    LEDShow(~(0xF000 >> LEDIndex));
  if (LEDIndex == 11) //��11ȡ��
    LEDDirection =! LEDDirection;
  LEDIndex = (LEDIndex + 1) % 12; //�Լ�1  
}

void Mode_7() //�����Ƽӷ�
{
  LEDShow(++LEDIndex);
}







