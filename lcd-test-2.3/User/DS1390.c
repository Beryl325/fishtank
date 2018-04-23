#include <DS1390.h>
#include <delay.h>
#include <spi.h>

#define CS2 P04
#define IN2 P05
#define OUT2 P06
#define CLK2 P07
#define INT1 P33

void InitDs1390(void)
{

		    SPI_WRITE_TX0(SPI1, 0x8d18);
       SPI_TRIGGER(SPI1);  //155us low				
       while(SPI_IS_BUSY(SPI1));
        SPI_READ_RX0(SPI1);

}

unsigned int readtime()  
{  
	unsigned int i,x[2],re;
			SPI_WRITE_TX0(SPI1, 0x0101);
			/* Trigger SPI data transfer */
       SPI_TRIGGER(SPI1);  //155us low				
			/* Check SPI0 busy status */
       while(SPI_IS_BUSY(SPI1));
       /* Read received data */
       i= SPI_READ_RX0(SPI1)&0x7f;
	     x[0]=(i&0xf0)>>4;
	     x[1]=(i&0xf);
	     re=x[0]*10+x[1];
			 
			SPI_WRITE_TX0(SPI1, 0x0202);
			/* Trigger SPI data transfer */
       SPI_TRIGGER(SPI1);  //155us low				
			/* Check SPI0 busy status */
       while(SPI_IS_BUSY(SPI1));
       /* Read received data */
       i= SPI_READ_RX0(SPI1)&0x7f;
	     x[0]=(i&0xf0)>>4;
	     x[1]=(i&0xf);
			 re=re|((x[0]*10+x[1])<<8);
//	     printf("\n\nmin: %d%d \n",x[0],x[1]);
			 
			  SPI_WRITE_TX0(SPI1, 0x0303);
			///Trigger SPI data transfer
       SPI_TRIGGER(SPI1);  //155us low				
		//	Check SPI0 busy status
       while(SPI_IS_BUSY(SPI1));
     //   Read received data 
       i= SPI_READ_RX0(SPI1)&0x7f;
			 if(i&0x40)  //12hour
			 {
				 if(i&0x20) //pm
				 {
					 x[0]=(i&0x10)>>4;
					 x[1]=i&0xf;
//					 printf("\n\nhour: %d%d pm\n",x[0],x[1]);
				 }
				 else
				 {
					 x[0]=(i&0x10)>>4;
					 x[1]=i&0xf;
//					 printf("\n\nhour: %d%d am\n",x[0],x[1]);
				 }
			 }
			 else
			 {
				 if(i&0x20)
				 {
					 x[0]=2;
					 x[1]=i&0xf;
//					 printf("\n\nhour: %d%d \n",x[0],x[1]);
				 }
				 else
				 {
					 x[0]=(i&0x10)>>4;
					 x[1]=i&0xf;
//					 printf("\n\nhour: %d%d \n",x[0],x[1]);
				 }
			 }
			 re=re|((x[0]*10+x[1])<<16);
	     				

			SPI_WRITE_TX0(SPI1, 0x0404);
			/* Trigger SPI data transfer */
       SPI_TRIGGER(SPI1);  //155us low				
			/* Check SPI0 busy status */
       while(SPI_IS_BUSY(SPI1));
       /* Read received data */
       i= SPI_READ_RX0(SPI1)&0x7;
//	     printf("\n\nday: %d \n",i);
			return re;

}

unsigned int readtime2()
{
		unsigned int i,x[2],re;
				SPI_WRITE_TX0(SPI1, 0x0505);
			///Trigger SPI data transfer
       SPI_TRIGGER(SPI1);  //155us low				
		//	Check SPI0 busy status
       while(SPI_IS_BUSY(SPI1));
     //   Read received data 
       i= SPI_READ_RX0(SPI1)&0x3f;
			 x[0]=(i&0x30)>>4;
			 x[1]=i&0xf;
//	     printf("\n\ndate: %d%d \n",x[0],x[1]);
			 re=x[0]*10+x[1];

			SPI_WRITE_TX0(SPI1, 0x0606);
			/* Trigger SPI data transfer */
       SPI_TRIGGER(SPI1);  //155us low				
			/* Check SPI0 busy status */
       while(SPI_IS_BUSY(SPI1));
       /* Read received data */
       i= SPI_READ_RX0(SPI1)&0x1f;
			 x[0]=(i&0x10)>>4;
	     x[1]=i&0xf;
//	     printf("\n\nmonth: %d%d \n",x[0],x[1]);
			 re=re|((x[0]*10+x[1])<<8);

			 SPI_WRITE_TX0(SPI1, 0x0707);
			/* Trigger SPI data transfer */
       SPI_TRIGGER(SPI1);  //155us low				
			/* Check SPI0 busy status */
       while(SPI_IS_BUSY(SPI1));
       /* Read received data */
       i= SPI_READ_RX0(SPI1)&0xff;
	     x[0]=(i&0xf0)>>4;
	     x[1]=i&0xf;
//	     printf("\n\nyear: %d%d \n",x[0],x[1]);
			 re=re|((x[0]*10+x[1])<<16);
			 return re;
}

void Settime(unsigned char year,unsigned char month,unsigned char date,unsigned char day,unsigned char hour,unsigned char min,unsigned char sec)  
{  
	     int i,x[2];
				SPI_WRITE_TX0(SPI1, 0x8000);   //msec
			/* Trigger SPI data transfer */
       SPI_TRIGGER(SPI1);  //155us low				
			/* Check SPI0 busy status */
       while(SPI_IS_BUSY(SPI1));
       /* Read received data */
      SPI_READ_RX0(SPI1);
	     
	     x[0]=sec/10;
	     x[1]=sec%10;
	     i=(0x8100|(x[0]<<4))|x[1];
	    SPI_WRITE_TX0(SPI1, i);    //sec,0
			/* Trigger SPI data transfer */
       SPI_TRIGGER(SPI1);  //155us low				
			/* Check SPI0 busy status */
       while(SPI_IS_BUSY(SPI1));
       /* Read received data */
       SPI_READ_RX0(SPI1);
	   
		 SPI_WRITE_TX0(SPI1, 0x0101);
			/* Trigger SPI data transfer */
       SPI_TRIGGER(SPI1);  //155us low				
			/* Check SPI0 busy status */
       while(SPI_IS_BUSY(SPI1));
       /* Read received data */
       i= SPI_READ_RX0(SPI1);
	     printf("\n\nsec: %d \n",i);
		 
	     x[0]=min/10;
	     x[1]=min%10;
	     i=(0x8200|(x[0]<<4))|x[1];
	    SPI_WRITE_TX0(SPI1, i);    //min,57
			/* Trigger SPI data transfer */
       SPI_TRIGGER(SPI1);  //155us low				
			/* Check SPI0 busy status */
       while(SPI_IS_BUSY(SPI1));
       /* Read received data */
       SPI_READ_RX0(SPI1);
			 
			 
			 SPI_WRITE_TX0(SPI1, 0x0202);
			/* Trigger SPI data transfer */
       SPI_TRIGGER(SPI1);  //155us low				
			/* Check SPI0 busy status */
       while(SPI_IS_BUSY(SPI1));
       /* Read received data */
       i= SPI_READ_RX0(SPI1);
	     printf("\n\nmin: %d \n",i);
	    
	     x[0]=hour/10;
	     x[1]=hour%10;
	     i=(0x8300|(x[0]<<4))|x[1];
	    SPI_WRITE_TX0(SPI1, i);     //hour,24小时制，13时
			/* Trigger SPI data transfer */
       SPI_TRIGGER(SPI1);  //155us low				
			/* Check SPI0 busy status */
       while(SPI_IS_BUSY(SPI1));
       /* Read received data */
       SPI_READ_RX0(SPI1);
			 
			 SPI_WRITE_TX0(SPI1, 0x0303);
			/* Trigger SPI data transfer */
       SPI_TRIGGER(SPI1);  //155us low				
			/* Check SPI0 busy status */
       while(SPI_IS_BUSY(SPI1));
       /* Read received data */
       i= SPI_READ_RX0(SPI1);
	     printf("\n\nhour: %d \n",i);
	     
      i=0x8400|day;
	    SPI_WRITE_TX0(SPI1, i);     //day,周二
			/* Trigger SPI data transfer */
       SPI_TRIGGER(SPI1);  //155us low				
			/* Check SPI0 busy status */
       while(SPI_IS_BUSY(SPI1));
       /* Read received data */
       SPI_READ_RX0(SPI1);
			 
			 SPI_WRITE_TX0(SPI1, 0x0404);
			/* Trigger SPI data transfer */
       SPI_TRIGGER(SPI1);  //155us low				
			/* Check SPI0 busy status */
       while(SPI_IS_BUSY(SPI1));
       /* Read received data */
       i= SPI_READ_RX0(SPI1);
	     printf("\n\nday: %d \n",i);
	     
	     x[0]=date/10;
	     x[1]=date%10;
	     i=(0x8500|(x[0]<<4))|x[1];
	    SPI_WRITE_TX0(SPI1, i);      //date,30
			/* Trigger SPI data transfer */
       SPI_TRIGGER(SPI1);  //155us low				
			/* Check SPI0 busy status */
       while(SPI_IS_BUSY(SPI1));
       /* Read received data */
       SPI_READ_RX0(SPI1);
			 
			 SPI_WRITE_TX0(SPI1, 0x0505);
			/* Trigger SPI data transfer */
       SPI_TRIGGER(SPI1);  //155us low				
			/* Check SPI0 busy status */
       while(SPI_IS_BUSY(SPI1));
       /* Read received data */
       i= SPI_READ_RX0(SPI1);
	     printf("\n\ndate: %d \n",i);
	    
	     x[0]=month/10;
	     x[1]=month%10;
	     i=(0x8600|(x[0]<<4))|x[1];
	    SPI_WRITE_TX0(SPI1, i);       //month,12月
			/* Trigger SPI data transfer */
       SPI_TRIGGER(SPI1);  //155us low				
			/* Check SPI0 busy status */
       while(SPI_IS_BUSY(SPI1));
       /* Read received data */
       SPI_READ_RX0(SPI1);
			 
			 SPI_WRITE_TX0(SPI1, 0x0606);
			/* Trigger SPI data transfer */
       SPI_TRIGGER(SPI1);  //155us low				
			/* Check SPI0 busy status */
       while(SPI_IS_BUSY(SPI1));
       /* Read received data */
       i= SPI_READ_RX0(SPI1);
	     printf("\n\nmonth: %d \n",i);
	     
	     x[0]=year/10;
	     x[1]=year%10;
	     i=(0x8700|(x[0]<<4))|x[1];
	    SPI_WRITE_TX0(SPI1, i);       //year,18年
			/* Trigger SPI data transfer */
       SPI_TRIGGER(SPI1);  //155us low				
			/* Check SPI0 busy status */
       while(SPI_IS_BUSY(SPI1));
       /* Read received data */
       SPI_READ_RX0(SPI1);
			 
			 SPI_WRITE_TX0(SPI1, 0x0707);
			/* Trigger SPI data transfer */
       SPI_TRIGGER(SPI1);  //155us low				
			/* Check SPI0 busy status */
       while(SPI_IS_BUSY(SPI1));
       /* Read received data */
       i= SPI_READ_RX0(SPI1);
	     printf("\n\nyear: %d \n",i);

} 

