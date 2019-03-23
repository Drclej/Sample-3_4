#include <msp430f249.h>
#include "key.h"
#include "Led_disp.h"
#define uchar unsigned char
#define uint unsigned int


uchar RunMode;
uint SystemSpeed,SystemSpeedIndex;
uchar LEDDirection = 1;
uchar LEDFlag = 1;
uint LEDIndex = 0;
extern void(*run[8])(void);

void system_initial(void)
{
  P1DIR = 0xFF;
  P2DIR = 0x00;
  P4DIR = 0xFF;
  P1SEL = 0x00;
  P4SEL = 0x00;
  P1OUT = 0xFF;
  P4OUT = 0xFF;
  RunMode = 0x07;
  SystemSpeedIndex = 10;
  SetSpeed(SystemSpeedIndex); 
}



void main( void )
{
  uchar key;
  WDTCTL = WDTPW + WDTHOLD;
  system_initial();
  while (1)
  {
    key = GetKey();
    if (key != 0x00)
    {
      process_key(key);
    }
    run[RunMode]();
    delayus(SystemSpeed);
  }

}
