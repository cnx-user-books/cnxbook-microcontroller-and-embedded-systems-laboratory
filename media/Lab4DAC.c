#include <__cross_studio_io.h>
#include          "msp430x16x.h"
/**
*  this code is going to test the DAC
*  the DAC output 1 will output a waveform (sawtooth to 2.5)
* uses basic interrupt and DAC 
*/
  static unsigned int index = 0;
void
main(void)
{
  WDTCTL = WDTPW+WDTHOLD;               // Stop watchdog timer
  // enables interrupts
  ADC12CTL0 = REF2_5V + REFON;                    // Internal 2.5V ref on 
  DAC12_1CTL = DAC12AMP0+DAC12AMP1+DAC12AMP2+DAC12ENC+DAC12IE+DAC12IFG+DAC12LSEL0+DAC12IR;
  _EINT(); 
 DAC12_1DAT = 0x00;

  while(1);
}
void DAC12ISR (void) __interrupt[DACDMA_VECTOR] 
{
  DAC12_1CTL &= ~DAC12IFG;
  DAC12_1DAT = index++;// set new value
  if(index == 4095){
    index = 0;
  } 
}
  
