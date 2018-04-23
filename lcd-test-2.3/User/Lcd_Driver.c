#include <stdio.h>
#include <M051Series.h>
#include <Lcd_Driver.h>
#include <delay.h>
#include <string.h>

#define SCL                 P17
#define SDA									P15
#define RES									P42
#define DC									P34
#define CS									P14
#define BL									P43

#define uchar unsigned char
#define uint unsigned int

#define X_MAX_PIXEL	        128
#define Y_MAX_PIXEL	        160

//向SPI总线传输一个8位数据
void  SPI_WriteData(unsigned char Data)
{
	unsigned char i=0;
	for(i=8;i>0;i--)
	{
		if(Data&0x80)	
		SDA=1; //输出数据
		else SDA=0;
		SCL=0;
//		delay_us(1);
		SCL=1;
		Data<<=1;
	}
}
//向液晶屏写一个8位指令
void  Lcd_WriteIndex(unsigned char Data)
{
		
		CS=0;
		DC=0;
		SPI_WriteData(Data); 		
		CS=1;
}
//向液晶屏写一个8位数据
void  Lcd_WriteData(unsigned char Data)
{	
	
		CS=0;
		DC=1;
		SPI_WriteData(Data); 	
		CS=1;
}
//向液晶屏写一个16位数据
void  LCD_WriteData_16Bit(unsigned int Data)
{
	
	CS=0;
	DC=1;
	SPI_WriteData(Data>>8); 	//写入高8位数据
	SPI_WriteData(Data); 			//写入低8位数据
	CS=1;

}

void Lcd_Reset(void)
{
	RES=0;
	delay_ms(100);
	RES=1;
	delay_ms(50);
}

void  LCD_GPIO_Init(void)//lcd io口初始化
{
	    /* Configure P as Output mode  */
    GPIO_SetMode(P1, BIT5, GPIO_PMD_OUTPUT);
		GPIO_SetMode(P1, BIT7, GPIO_PMD_OUTPUT);
		GPIO_SetMode(P4, BIT2, GPIO_PMD_OUTPUT);
		GPIO_SetMode(P3, BIT4, GPIO_PMD_OUTPUT);
		GPIO_SetMode(P1, BIT4, GPIO_PMD_OUTPUT);
		GPIO_SetMode(P4, BIT3, GPIO_PMD_OUTPUT);
		    /* Configure P to default Quasi-bidirectional mode */
    GPIO_SetMode(P1, BIT7, GPIO_PMD_QUASI);
		GPIO_SetMode(P1, BIT5, GPIO_PMD_QUASI);
		GPIO_SetMode(P4, BIT2, GPIO_PMD_QUASI);
		GPIO_SetMode(P3, BIT4, GPIO_PMD_QUASI);
		GPIO_SetMode(P1, BIT4, GPIO_PMD_QUASI);
    GPIO_SetMode(P4, BIT3, GPIO_PMD_QUASI);
	
}




//////lcd初始化
void  LCD_Init(void)
{
	LCD_GPIO_Init();
	Lcd_Reset();
	BL=1;
		
	//LCD Init For 1.44Inch LCD Panel with ST7735R.
	Lcd_WriteIndex(0x11);//Sleep exit 
	delay_ms (120);
		
	//ST7735R Frame Rate
	Lcd_WriteIndex(0xB1); 
	Lcd_WriteData(0x01); 
	Lcd_WriteData(0x2C); 
	Lcd_WriteData(0x2D); 

	Lcd_WriteIndex(0xB2); 
	Lcd_WriteData(0x01); 
	Lcd_WriteData(0x2C); 
	Lcd_WriteData(0x2D); 

	Lcd_WriteIndex(0xB3); 
	Lcd_WriteData(0x01); 
	Lcd_WriteData(0x2C); 
	Lcd_WriteData(0x2D); 
	Lcd_WriteData(0x01); 
	Lcd_WriteData(0x2C); 
	Lcd_WriteData(0x2D); 
	
	Lcd_WriteIndex(0xB4); //Column inversion 
	Lcd_WriteData(0x07); 
	
	//ST7735R Power Sequence
	Lcd_WriteIndex(0xC0); 
	Lcd_WriteData(0xA2); 
	Lcd_WriteData(0x02); 
	Lcd_WriteData(0x84); 
	Lcd_WriteIndex(0xC1); 
	Lcd_WriteData(0xC5); 

	Lcd_WriteIndex(0xC2); 
	Lcd_WriteData(0x0A); 
	Lcd_WriteData(0x00); 

	Lcd_WriteIndex(0xC3); 
	Lcd_WriteData(0x8A); 
	Lcd_WriteData(0x2A); 
	Lcd_WriteIndex(0xC4); 
	Lcd_WriteData(0x8A); 
	Lcd_WriteData(0xEE); 
	
	Lcd_WriteIndex(0xC5); //VCOM 
	Lcd_WriteData(0x0E); 
	
	Lcd_WriteIndex(0x36); //MX, MY, RGB mode 
	Lcd_WriteData(0xC0); 
#ifdef USE_LANDSCAPE
	Lcd_WriteData(0xA8); //竖屏C8 横屏08 A8
#else
	Lcd_WriteData(0xC8); //竖屏C8 横屏08 A8
#endif		
	//ST7735R Gamma Sequence
	Lcd_WriteIndex(0xe0); 
	Lcd_WriteData(0x0f); 
	Lcd_WriteData(0x1a); 
	Lcd_WriteData(0x0f); 
	Lcd_WriteData(0x18); 
	Lcd_WriteData(0x2f); 
	Lcd_WriteData(0x28); 
	Lcd_WriteData(0x20); 
	Lcd_WriteData(0x22); 
	Lcd_WriteData(0x1f); 
	Lcd_WriteData(0x1b); 
	Lcd_WriteData(0x23); 
	Lcd_WriteData(0x37); 
	Lcd_WriteData(0x00); 	
	Lcd_WriteData(0x07); 
	Lcd_WriteData(0x02); 
	Lcd_WriteData(0x10); 

	Lcd_WriteIndex(0xe1); 
	Lcd_WriteData(0x0f); 
	Lcd_WriteData(0x1b); 
	Lcd_WriteData(0x0f); 
	Lcd_WriteData(0x17); 
	Lcd_WriteData(0x33); 
	Lcd_WriteData(0x2c); 
	Lcd_WriteData(0x29); 
	Lcd_WriteData(0x2e); 
	Lcd_WriteData(0x30); 
	Lcd_WriteData(0x30); 
	Lcd_WriteData(0x39); 
	Lcd_WriteData(0x3f); 
	Lcd_WriteData(0x00); 
	Lcd_WriteData(0x07); 
	Lcd_WriteData(0x03); 
	Lcd_WriteData(0x10);  
	
	Lcd_WriteIndex(0x2a);
	Lcd_WriteData(0x00);
	Lcd_WriteData(0x00);
	Lcd_WriteData(0x00);
	Lcd_WriteData(0x7f);

	Lcd_WriteIndex(0x2b);
	Lcd_WriteData(0x00);
	Lcd_WriteData(0x00);
	Lcd_WriteData(0x00);
	Lcd_WriteData(0x9f);
	
	Lcd_WriteIndex(0xF0); //Enable test command  
	Lcd_WriteData(0x01); 
	Lcd_WriteIndex(0xF6); //Disable ram power save mode 
	Lcd_WriteData(0x00); 
	
	Lcd_WriteIndex(0x3A); //65k mode 
	Lcd_WriteData(0x05); 
	
	
	Lcd_WriteIndex(0x29);//Display on
}

/////////设置显示区域
void  Lcd_SetRegion(unsigned int x_start,unsigned int y_start,unsigned int x_end,unsigned int y_end)
{
	Lcd_WriteIndex(0x2a);
	Lcd_WriteData(0x00);
	Lcd_WriteData(x_start+2);
	Lcd_WriteData(0x00);
	Lcd_WriteData(x_end+2);

	Lcd_WriteIndex(0x2b);
	Lcd_WriteData(0x00);
	Lcd_WriteData(y_start+1);
	Lcd_WriteData(0x00);
	Lcd_WriteData(y_end+1);
	
	Lcd_WriteIndex(0x2c);
	
}

/////////////////////写像素点
void PutPixel(uint x_start,uint y_start,uint color)  
{
	Lcd_SetRegion(x_start,y_start,x_start+1,y_start+1);
	LCD_WriteData_16Bit(color);
	
}
/*************************************************
函数名：LCD_Set_XY
功能：设置lcd显示起始点
入口参数：xy坐标
返回值：无
*************************************************/
void Lcd_SetXY(unsigned int x,unsigned int y)
{
  	Lcd_SetRegion(x,y,x,y);
}

/*************************************************
函数名：LCD_DrawPoint
功能：画一个点
入口参数：无
返回值：无
*************************************************/
void Gui_DrawPoint(unsigned int x,unsigned int y,unsigned int Data)
{
	Lcd_SetRegion(x,y,x+1,y+1);
	LCD_WriteData_16Bit(Data);

}

/////////////////////
void dsp_single_colour(int color)
{
 	uchar i,j;
	Lcd_SetRegion(0,0,128-1,160-1);
 	for (i=0;i<160;i++)
    	for (j=0;j<128;j++)
        	LCD_WriteData_16Bit(color);
}

/*************************************************
函数名：Lcd_Clear
功能：全屏清屏函数
入口参数：填充颜色COLOR
返回值：无
*************************************************/
void Lcd_Clear(unsigned int Color)               
{	
   unsigned int i,m;
   Lcd_SetRegion(0,0,127,159);
   Lcd_WriteIndex(0x2C);
   for(i=0;i<128;i++)
    for(m=0;m<160;m++)
    {	
	  	LCD_WriteData_16Bit(Color);
    }   
}




