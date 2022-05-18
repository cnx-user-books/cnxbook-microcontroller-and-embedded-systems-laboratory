/*******************************************************************************
 ELEC 226 Lab 2

 Use breakpoints, watch variables, and/or use the locals window to help
 observe what this program is doing.
*******************************************************************************/

#include <msp430x16x.h>
#include <__cross_studio_io.h>

void main(void){
  int i,j,tmp;
  int a[20]={0x000C,0x0C62,0x0180,0x0D4A,0x00F0,0x0CCF,0x0C35,0x096E,0x02E4,
  0x0BDB,0x0788,0x0AD7,0x0AC9,0x0D06,0x00EB,0x05CC,0x0AE3,0x05B7,0x001D,0x0000};

  for (i=0; i<19; i++){
    for (j=0; j<19-i; j++){
      if (a[j+1] < a[j]) {
        tmp = a[j];
        a[j] = a[j+1];
        a[j+1] = tmp;
      }
    }
  }
  while(1);
}