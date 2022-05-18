/****************************************************************
  i2c and adc2 filter initialization
  this sets up i2c and the filters for problem 4.2.x
  call initialize_i2c(); in your main function and everthing
  should work.
   -av
****************************************************************/

#include  <msp430x16x.h>

#define SLAVE1 0x3e
#define SLAVE2 0x3f
#define SLAVE3 0x3d

void initialize_i2c(void);
void set_pcf(char byte, int slave);

void initialize_i2c(void)
{
  unsigned int foo;

  P3SEL |= 0x0A;
  U0CTL |= I2C+SYNC+MST;
  U0CTL &= ~I2CEN;
  // config module
  I2CTCTL |=  I2CSSEL0+I2CSSEL1;
  I2CNDAT = 1; 				// we are only writing 1 byte of data
  I2CPSC = 4; 				// 7.8MHz/4+1 = 1.56MHz
  I2CSCLH = 8;
  I2CSCLL = 8; 				//8+8 = 16 1.56MHz/16 = 10kHz
  I2COA = 0x47;
  U0CTL |= I2CEN;			// turn on i2c

  // the following lines have nothing to do with i2c.
  // they set up the clocks, timers, and filters for the ADC
  P2DIR |= 0x04;			// FILTER_CLK_SWITCH output
  P2OUT &= 0xfb;			// FILTER_CLK_SWITCH output
  P4DIR |= 0x10;			// enable AD_FILTER_CLOCK_TMRB (P4.4)
  P4SEL |= 0x10;			// Select alt function for P4.4

  TBCCR0 = 6;				// PWM Period
  TBCCR4 = TBCCR0/2;		// 50% duty cycle        (adc filter clk)
  TBCCR5 = TBCCR0/2;		// 50% duty cycle        (dac filter clk)
  TBCCTL4 = OUTMOD_7;		// Reset/Set output mode (adc filter clk)
  TBCCTL5 = OUTMOD_7;		// Reset/Set output mode (dac filter clk)
  TBCTL = TBSSEL1 + TBCLR + MC0; //start timer_b

  set_pcf(0x84,SLAVE3);		// enable ANA2_FILTER_ON
}


int transmit_byte(int slave, char byte)
{
  unsigned int foo;
 // U0CTL &= ~I2CEN;
  I2CDRB = byte;
  I2CSA = slave;
  U0CTL |= MST;
  I2CTCTL |= I2CTRX+I2CSTT+I2CSTP;
  // U0CTL |= I2CEN;

  // allows time for 7 segment to update
  for (foo=0;foo<1000;foo++){
    _NOP();
  }

  return 1;
}

void set_pcf(char byte, int slave){
  transmit_byte(slave, byte);
  return;
}




