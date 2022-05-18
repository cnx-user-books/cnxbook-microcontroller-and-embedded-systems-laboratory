/*******************************************************************************
Lab 2.  Breakpoints

this program doesnt really do anything but it should be
used to practice using differnt types of breakpoints.

*******************************************************************************/

#include <msp430x16x.h>
int foo(int x);

void main(void)
{
  int i;
  int j=0;

  for(i=0;i<10000;i++){
    j=j+i;

    if (j>100){
      foo(j);
    }
  }
}

int foo(int x)
{
    x=x+10000;
    return x;
}

