#ifndef _LCD_DRIVER_H
#define _LCD_DRIVER_H



//定义常用颜色
#define RED  	0xf800
#define GREEN	0x07e0
#define GREEN1 0x07FF
#define BLUE 	0x001f
#define WHITE	0xffff
#define BLACK	0x0000
#define YELLOW  0xFFE0
#define GRAY0   0xEF7D   	//灰色0 3165 00110 001011 00101
#define GRAY1   0x8410      	//灰色1      00000 000000 00000
#define GRAY2   0x4208      	//灰色2  1111111111011111

void  SPI_WriteData(unsigned char Data);//向SPI总线传输一个8位数据
void  Lcd_WriteIndex(unsigned char Data);//向液晶屏写一个8位指令
void  Lcd_WriteData(unsigned char Data);//向液晶屏写一个8位数据
void  LCD_WriteData_16Bit(unsigned int Data);//向液晶屏写一个16位数据
void  LCD_GPIO_Init(void);//lcd io口初始化
void  LCD_Init(void);//lcd初始化
void	Lcd_Reset(void);
void  Lcd_SetRegion(unsigned int x_start,unsigned int y_start,unsigned int x_end,unsigned int y_end);//设置lcd显示区域
void  PutPixel(unsigned int x_start,unsigned int y_start,unsigned int color);//写像素点
void  Lcd_Clear(unsigned int Color);    //填充颜色
void  Display_ASCII8X16(unsigned int x0,unsigned int y0, char *s);//显示一个英文字符
void  Fast_DrawFont_GBK16(unsigned int x, unsigned int y, unsigned int fc, unsigned int bc,  char *s);
void  Display_Desc(void);
void dsp_single_colour(int color);
void Lcd_SetXY(unsigned int x,unsigned int y);
void Gui_DrawPoint(unsigned int x,unsigned int y,unsigned int Data);
#endif
