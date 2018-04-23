#ifndef _LCD_DRIVER_H
#define _LCD_DRIVER_H



//���峣����ɫ
#define RED  	0xf800
#define GREEN	0x07e0
#define GREEN1 0x07FF
#define BLUE 	0x001f
#define WHITE	0xffff
#define BLACK	0x0000
#define YELLOW  0xFFE0
#define GRAY0   0xEF7D   	//��ɫ0 3165 00110 001011 00101
#define GRAY1   0x8410      	//��ɫ1      00000 000000 00000
#define GRAY2   0x4208      	//��ɫ2  1111111111011111

void  SPI_WriteData(unsigned char Data);//��SPI���ߴ���һ��8λ����
void  Lcd_WriteIndex(unsigned char Data);//��Һ����дһ��8λָ��
void  Lcd_WriteData(unsigned char Data);//��Һ����дһ��8λ����
void  LCD_WriteData_16Bit(unsigned int Data);//��Һ����дһ��16λ����
void  LCD_GPIO_Init(void);//lcd io�ڳ�ʼ��
void  LCD_Init(void);//lcd��ʼ��
void	Lcd_Reset(void);
void  Lcd_SetRegion(unsigned int x_start,unsigned int y_start,unsigned int x_end,unsigned int y_end);//����lcd��ʾ����
void  PutPixel(unsigned int x_start,unsigned int y_start,unsigned int color);//д���ص�
void  Lcd_Clear(unsigned int Color);    //�����ɫ
void  Display_ASCII8X16(unsigned int x0,unsigned int y0, char *s);//��ʾһ��Ӣ���ַ�
void  Fast_DrawFont_GBK16(unsigned int x, unsigned int y, unsigned int fc, unsigned int bc,  char *s);
void  Display_Desc(void);
void dsp_single_colour(int color);
void Lcd_SetXY(unsigned int x,unsigned int y);
void Gui_DrawPoint(unsigned int x,unsigned int y,unsigned int Data);
#endif
