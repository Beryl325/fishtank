#include <DS18B20.h>
#include <delay.h>

#define DATA P37
/****************************************************************
��λ
*****************************************************************/
unsigned int reset_ds18b20(void)
{
   unsigned int presence;
   DATA=0;						  
   delay_us(144);      //��ʱ480~960us
   DATA=1;	
   delay_us(5);	  //��ʱ 15 - 60  us 
	 presence=DATA; //presence=0��ʼ���ɹ���=1��ʼ��ʧ��
	 delay_us(21);   //18b20�����������壬��ʱ 60 - 240  us 
	 DATA=1;
	delay_us(96); 
   return(presence);

}
/****************************************************************
дһ��bit
*****************************************************************/
void write_bit_ds18b20(unsigned char dat)
{
	DATA=0;        //��0 ������ʱ
	delay_us(1);	
	if(dat==1)
		  DATA=1;
	delay_us(15);	 //��ʱ 60 - 120  us
	
 	DATA=1;
	delay_us(1);	 //��ʱ 1 - ��  us
}
/****************************************************************
дһ��byte
*****************************************************************/
void write_byte_ds18b20(unsigned char dat)
{
     unsigned char i,j;
	 for(i=0;i<8;i++)
	 {
	     j=((dat>>i)&0x01);
		 write_bit_ds18b20(j);
		 //delay_us(1);      //��ʱ 1 - ��  us
	 }


}  
/****************************************************************
��һ��bit
*****************************************************************/
 unsigned char read_bit_ds18b20(void)
{
	unsigned char i;
	DATA=1;
	delay_1us(1);
	DATA=0;
	delay_1us(1);    //��ʱ 1us  Ҳ���Բ���ʱ
	DATA=1;
  for(i=0;i<3;i++);	
	return(DATA);
} 
/****************************************************************
��һ��byte
*****************************************************************/
unsigned char read_byte_ds18b20(void)
{
	unsigned char dat=0;
	unsigned char i;
	for(i=0;i<8;i++)
	 {
	   if(read_bit_ds18b20())
	     dat|=0x01<<i;
	   delay_us(12);	   //��ʱ5  us
	 
	 }
	 return(dat); 	  
}
/****************************************************************
��ʼ��
*****************************************************************/
void ds18b20_init(void)
{
	  /* Configure P as Output mode  */
    GPIO_SetMode(P3, BIT7, GPIO_PMD_OUTPUT);
		    /* Configure P to default Quasi-bidirectional mode */
    GPIO_SetMode(P3, BIT7, GPIO_PMD_QUASI);
}
/****************************************************************
��һ���¶�
*****************************************************************/
int read_temp_ds18b20(void)
{
   unsigned char templ=0,temph=0;
   int temp=0;
   reset_ds18b20();//��λ
   write_byte_ds18b20(0xcc); //����ROM
   write_byte_ds18b20(0x44); //�����¶�ת��
   delay_ms(750);     //750ms
		//��DS18B20���Ͷ�ȡ��������
   reset_ds18b20();
   write_byte_ds18b20(0xcc); //����ROM
   write_byte_ds18b20(0xbe); //׼�������ݣ���ʼ�¶�ת���ɼ���
   templ=read_byte_ds18b20();//�����ֽ��¶�ֵ
   temph=read_byte_ds18b20();//�����ֽ��¶�ֵ
   temp=(templ+(temph*256));
   return(temp);
}










