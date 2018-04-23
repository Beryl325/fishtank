#include <Relay.h>
#include <delay.h>

#define pump1 P41
#define pump2 P12
#define lamp P13
#define fan P11
#define hot P01
#define cold P00


void relay_init(void)
{
		 // Configure P as Output mode  
    GPIO_SetMode(P4, BIT1, GPIO_PMD_OUTPUT);
	  GPIO_SetMode(P1, BIT3, GPIO_PMD_OUTPUT);
	  GPIO_SetMode(P1, BIT2, GPIO_PMD_OUTPUT);
	  GPIO_SetMode(P1, BIT1, GPIO_PMD_OUTPUT);
  	GPIO_SetMode(P0, BIT0, GPIO_PMD_OUTPUT);
  	GPIO_SetMode(P0, BIT1, GPIO_PMD_OUTPUT);
	
	P11=0;
	P12=0;
	P13=0;
	P41=0;
	P00=0;
	P01=0;
}



