#include <delay.h>

void delay_ms(unsigned int time)  //1ms
{
 unsigned int i,j;
  for(i=0;i<time;i++)
   for(j=0;j<2000;j++);
}

void delay_us(unsigned int time)//5us
{
   unsigned int i,j;
   for(i=0;i<time;i++)
   for(j=0;j<5;j++);
}

void delay_1us(unsigned int time)//1us
{

}
