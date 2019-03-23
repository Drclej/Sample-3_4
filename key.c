#include <msp430f249.h>
#include "key.h"
#include "Led_disp.h"

extern uchar RunMode;
extern uchar LEDDirection;
extern uchar LEDFlag;
extern uint LEDIndex;
extern uint SystemSpeed;
extern uint SystemSpeedIndex;


uint SpeedCode[] = {1,2,3,5,8,10,10,14,17,20,30,40,50,
    60,70,80,90,100,120,140,160,180,200,300,400,500,600,
    700,800,900,1000};


uchar GetKey(void)
{
  if ((P2IN & 0x07) != 0x07)
  {
    
    if ((P2IN & 0x07) == 0x06) return 0x01;
    else if ((P2IN & 0x07) == 0x05) return 0x02;
    else if ((P2IN & 0x07) == 0x03) return 0x04;
    else return 0x00;
  }
  return 0x00;
}

void SetSpeed(uchar Speed)
{
  SystemSpeed = SpeedCode[Speed];
}

void process_key(uchar Key)
{
  if (Key == 0x01)
  {
    LEDShow(0x0000);
    LEDDirection = 1;
    LEDFlag = 1;
    LEDIndex = 0;
    ++RunMode;
    if (RunMode == 0x08) RunMode = 0x00;
    delayus(100);
  }
  if (Key == 0x02)
  {
    if (SystemSpeedIndex < 28)
    {
      ++SystemSpeedIndex;
      SetSpeed(SystemSpeedIndex);
    }
  }
  if (Key == 0x04)
  {
    if (SystemSpeedIndex > 0)
    {
      --SystemSpeedIndex;
      SetSpeed(SystemSpeedIndex);
    }    
  }
}
