#include <DS18B20.h>
#include <delay.h>

#define DATA P37
/****************************************************************
复位
*****************************************************************/
unsigned int reset_ds18b20(void)
{
   unsigned int presence;
   DATA=0;						  
   delay_us(144);      //延时480~960us
   DATA=1;	
   delay_us(5);	  //延时 15 - 60  us 
	 presence=DATA; //presence=0初始化成功，=1初始化失败
	 delay_us(21);   //18b20发出存在脉冲，延时 60 - 240  us 
	 DATA=1;
	delay_us(96); 
   return(presence);

}
/****************************************************************
写一个bit
*****************************************************************/
void write_bit_ds18b20(unsigned char dat)
{
	DATA=0;        //置0 无需延时
	delay_us(1);	
	if(dat==1)
		  DATA=1;
	delay_us(15);	 //延时 60 - 120  us
	
 	DATA=1;
	delay_us(1);	 //延时 1 - ∞  us
}
/****************************************************************
写一个byte
*****************************************************************/
void write_byte_ds18b20(unsigned char dat)
{
     unsigned char i,j;
	 for(i=0;i<8;i++)
	 {
	     j=((dat>>i)&0x01);
		 write_bit_ds18b20(j);
		 //delay_us(1);      //延时 1 - ∞  us
	 }


}  
/****************************************************************
读一个bit
*****************************************************************/
 unsigned char read_bit_ds18b20(void)
{
	unsigned char i;
	DATA=1;
	delay_1us(1);
	DATA=0;
	delay_1us(1);    //延时 1us  也可以不延时
	DATA=1;
  for(i=0;i<3;i++);	
	return(DATA);
} 
/****************************************************************
读一个byte
*****************************************************************/
unsigned char read_byte_ds18b20(void)
{
	unsigned char dat=0;
	unsigned char i;
	for(i=0;i<8;i++)
	 {
	   if(read_bit_ds18b20())
	     dat|=0x01<<i;
	   delay_us(12);	   //延时5  us
	 
	 }
	 return(dat); 	  
}
/****************************************************************
初始化
*****************************************************************/
void ds18b20_init(void)
{
	  /* Configure P as Output mode  */
    GPIO_SetMode(P3, BIT7, GPIO_PMD_OUTPUT);
		    /* Configure P to default Quasi-bidirectional mode */
    GPIO_SetMode(P3, BIT7, GPIO_PMD_QUASI);
}
/****************************************************************
读一个温度
*****************************************************************/
int read_temp_ds18b20(void)
{
   unsigned char templ=0,temph=0;
   int temp=0;
   reset_ds18b20();//复位
   write_byte_ds18b20(0xcc); //跳过ROM
   write_byte_ds18b20(0x44); //发动温度转换
   delay_ms(750);     //750ms
		//向DS18B20发送读取数据命令
   reset_ds18b20();
   write_byte_ds18b20(0xcc); //跳过ROM
   write_byte_ds18b20(0xbe); //准备好数据（开始温度转换采集）
   templ=read_byte_ds18b20();//读低字节温度值
   temph=read_byte_ds18b20();//读低字节温度值
   temp=(templ+(temph*256));
   return(temp);
}










