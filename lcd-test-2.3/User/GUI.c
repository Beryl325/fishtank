#include <GUI.h>
#include <stdio.h>
#include <M051Series.h>
#include <Lcd_Driver.h>
#include <font.h>


//ºº×Ö
void Gui_DrawFont_C(unsigned int x, unsigned int y, unsigned int fc, unsigned int bc, unsigned int num)
{
			unsigned char i,j,k,c;

    for(i=0;i<16;i++)
	{
		for(j=0;j<2;j++){
			c=*(hz10+num*32+i*2+j);
			for (k=0;k<8;k++)	
			{
				
		    	if(c&(0x80>>k))	Gui_DrawPoint(x+j*8+k,y+i,fc);
				else {
					if (fc!=bc) Gui_DrawPoint(x+j*8+k,y+i,bc);
				}
			}
		}
	}
}
//Êý×Ö
void Gui_DrawFont_S(unsigned int x, unsigned int y, unsigned int fc, unsigned int bc, unsigned int num)
{
			unsigned char i,j,k,c;

    for(j=0;j<2;j++)
	{
		for(i=0;i<8;i++){
			c=*(hz12+num*16+i+j*8);
			for (k=0;k<8;k++)	
			{
				
		    	if(c&(0x80>>k))	Gui_DrawPoint(x+k,y+i+j*8,fc);//Ð´×Ö
				else {
					if (fc!=bc) Gui_DrawPoint(x+k,y+i+j*8,bc);
				}
			}
		}
	}
}
