/**************************************************************************//**
 * @file     main.c
 * @version  V1.00
 * $Revision: 0 $
 * $Date: 18/01/17 $
 * @brief    test for nuvoton lcd
 *
 * @note
 * Copyright 
 ******************************************************************************/
#include <stdio.h>
#include <M051Series.h>
#include <Lcd_Driver.h>
#include <delay.h>
#include <GUI.h>
#include <demo.h>
#include <DS18B20.h>
#include <DS1390.h>
#include <Relay.h>

#define PLL_CLOCK           50000000
#define S1 P20   ///功能
#define S2 P21   ///上
#define S3 P22   ///下
#define S4 P23     ///确认
#define S5 P24     ///灯
#define S8 P27         ///开关
#define S6 P25       ///高位浮球
#define S7 P26       ///低位浮球

#define pump1 P41     ///回水泵
#define pump2 P12     ///出水泵
#define lamp P13
#define fan P11
#define hot P01
#define cold P00

#define CS3 P45  //29
#define OUT3 P44    //28
#define CLK3 P40    //24


#define uchar unsigned char
#define uint unsigned int
///定义函数
void  SPI_WriteData2(int Data);
void checkself(void);
//全局变量
float tempset=25,tempdiff=2;  //
float tempErr=0;   //温度校验差
int tempset1,tempdiff1,tempErr1;
uchar s[5]={0};   //按键,s[0]菜单，s[1]确认，s[2]上，s[3]下，s[4]照明
uchar mode=0;     //mode=0自动，mode=1制热，mode=2制冷
int count=0;   //计数，20次，采集温度
uchar lampstate=0;   //记录灯的状态,0关闭，1开
uchar hotstate=0;  //记录加热制冷状态=1加热，=0制冷
uchar symbol=0;   //正=0，负=1；
uint32_t u32Data,u32Addr,u32[6];
unsigned char   msec=0,sec=0x00, min=0x1e,  hour=0xc, day=1, date=0xe, month=0x3, year=0x12;
uchar valid[3]={0};  //三组定时有效，无效，=0无效，=1有效
unsigned char second[6]={0},minite[6]={0},hr[6]={0};  //第一组启动时间second[0],第一组关闭时间second[1]，类推
uchar s8_state=0; //开关状态
uchar un_state=0; //出水泵故障状态，0正常，1不正常
uchar state_count=0;  //低位浮球开后，计数
float temp=0;
/*************************************************************************************************************/
//计时中断
void TMR0_IRQHandler(void)
{
	


	unsigned int t1,t2;
  if(TIMER_GetIntFlag(TIMER0) == 1)
  {

    if(s[0]==0)
		{
									  ///水泵工作		
					if(S6==0)
					{
						pump1=0;   //关回水泵			
					}
					else
					{ 
					 //开回水泵
						pump1=1;
					}
					/**********************/
					if(S7==0)
					{
						pump2=0;   //关出水泵	
						cold=0;
						hot=0;
						fan=0;	
            state_count=0;						
					}
					else
					{
						 //开出水泵
						pump2=1;
					}
			
		}			
		if(s[0]==0||s[0]==99)
		{

								/////读时钟芯片ds1390.  1.5秒一次
			    t1=readtime();
					t2=readtime2();
					sec=t1&0xff;
					min=(t1&0xff00)>>8;
					hour=(t1&0xff0000)>>16;
			    date=t2&0xff;
					month=(t2&0xff00)>>8;
					year=(t2&0xff0000)>>16;
					time_now1( sec, min, hour, day, date, month, year);
			/////三组定时验证
					if(valid[0]==1&&hr[0]==hour&&minite[0]==min)
					{
						lampstate=1;
						lamp=1;
					}
					if(valid[0]==1&&hr[1]==hour&&minite[1]==min)
					{
						lampstate=0;
						lamp=0;
					}
					if(valid[1]==1&&hr[2]==hour&&minite[2]==min)
					{
						lampstate=1;
						lamp=1;
					}
					if(valid[1]==1&&hr[3]==hour&&minite[3]==min)
					{
						lampstate=0;
						lamp=0;
					}
					if(valid[2]==1&&hr[4]==hour&&minite[4]==min)
					{
						lampstate=1;
						lamp=1;
					}
					if(valid[2]==1&&hr[5]==hour&&minite[5]==min)
					{
						lampstate=0;
						lamp=0;
					}
			
		}


     if(s[0]==0&&un_state==0)
		 {
				count++;////1.5秒测一次水泵
				printf("\n timer0 up\n");
				 if(count==5)
				 {
					 count=0;
					 temp=temp_dq(tempErr,symbol);
				 }

			////采集温度,自动模式
					if(mode==0)
					{

							if(temp<(tempset-tempdiff)&&P26==1)  //加热
							{
								fan=1;
								cold=0;	
								hot=1;								
								hotstate=1;
								hoting();
								printf("\nhot1\n");
							}

							if(temp>(tempset+tempdiff)&&P26==1)  //制冷
							{
								fan=1;
								hot=0;
								cold=1;
								
								hotstate=0;
								colding();
							}
							if((temp>=tempset)&&P26==1&&hotstate==1)  //停止加热
							{
								cold=0;
								hot=0;
								fan=0;			
								normal();
							}
							if((temp<=tempset)&&P26==1&&hotstate==0)  ///停止制冷
							{
								cold=0;
								hot=0;
								fan=0;

								normal();
							}
							if(S7==0)
							{
								cold=0;
								hot=0;
								fan=0;
								un_state=1;
								unnormal();
							}
						}
			////////采集温度，加热模式
					if(mode==1)
					{
							if(temp<(tempset-tempdiff)&&P26==1)  //加热
							{
								fan=1;
								cold=0;	
								hot=1;								
								hotstate=1;
								hoting();
							}
							if((temp>tempset)&&P26==1&&hotstate==1)  //停止加热
							{
								cold=0;
								hot=0;
								fan=0;
				
								normal();
							}
							if((temp<tempset)&&P26==1&&hotstate==0)  //停止加热
							{
								cold=0;
								hot=0;
								fan=0;
		
								normal();
							}
							if(P26==0)
							{
								cold=0;
								hot=0;
								fan=0;
			          un_state=1;
								unnormal();
							}							
					}
			////采集温度,制冷模式
					if(mode==2)
					{
							if(temp>(tempset+tempdiff)&&P26==1)  //制冷
							{
								fan=1;
								hot=0;
								cold=1;
								
								hotstate=0;
								colding();
							}
							if((temp>tempset)&&P26==1&&hotstate==1)  //停止制冷
							{
								cold=0;
								hot=0;
								fan=0;
		
								normal();
							}
							if((temp<tempset)&&P26==1&&hotstate==0)
							{
								cold=0;
								hot=0;			
								fan=0;			
								normal();
							}
							if(P26==0)
							{
								cold=0;
								hot=0;
								fan=0;
                un_state=1;
								unnormal();
							}
			   }					
		 }
		if(un_state==1&&state_count<80)
		{
			state_count++;		
		}
		if(un_state==1&&state_count>=80)
		{
			   un_state=0;
			   state_count=0;		
		}			 
			TIMER_ClearIntFlag(TIMER0);  // 清除中断标志 
      
    }
}

/*--------------------------------------------------------------------------------------------------------------*/

/*  EINT1_IRQHandler()  外部中断                                                                                                      */

/*----------------------------------------------------------------------------------------------------------------*/
void EINT1_IRQHandler(void)
{
		unsigned int t1,t2;
    /* Re-enable P3.3 debounce function */
    GPIO_ENABLE_DEBOUNCE(P3, BIT3);
	/**   菜单              **/
		if(S1==1)
		{
			menu();
			s[0]=1;
			s[2]=3;
			s[3]=0;
			pump1=0;
			pump1=0;
			pump2=0;
			hot=0;
			cold=0;
			fan=0;
						
			printf("s1 Interrupt!\n");
		}
/***************************************************************************/
/******按键确认*******/
/***************************************************************************/
		if(S4==1)
		{
//////////进入工作模式首页
			if(s[0]==1&&s[2]==3&&s[3]==0)
			{
				menu1();
				s[0]=2;
				s[2]=2;
				s[3]=0;
				return;
			}
       /////选择自动模式,返回到温度显示页面
			if(s[0]==2&&s[2]==2&&s[3]==0)
			{
			  menu();
			  s[0]=1;
			  s[2]=3;
			  s[3]=0;
				mode=0;
				return;
			}
       /////选择制热模式,返回到温度显示页面
			if(s[0]==2&&s[2]==1&&s[3]==1)
			{
				mode=1;
			  menu();
			  s[0]=1;
			  s[2]=3;
			  s[3]=0;
				return;
			}
       ////选择制冷模式,返回到温度显示页面
			if(s[0]==2&&s[2]==0&&s[3]==2)
			{		
				mode=2;
			  menu();
			  s[0]=1;
			  s[2]=3;
			  s[3]=0;
				return;
			}
//////////进入定时设置首页////////////////////////////////////////////////
			if(s[0]==1&&s[2]==2&&s[3]==1)
			{
				menu2();
				s[0]=3;
				s[2]=3;
				s[3]=0;
				return;
			}
			///选择第一组
			if(s[0]==3&&s[2]==3&&s[3]==0)
			{
				menu21(valid[0]);
				s[0]=5;
				s[2]=3;
				s[3]=0;
				s[1]=1;
				return;
			}
			///选择第一组启动时间
			if(s[0]==5&&s[1]==1&&s[2]==3&&s[3]==0)
			{
				menu211(second[0],minite[0],hr[0]);
				s[0]=51;
				s[1]=0;
				s[2]=3;
				s[3]=0;
				return;
			}
			///选择第一组关闭时间
			if(s[0]==5&&s[1]==1&&s[2]==2&&s[3]==1)
			{
				menu212(second[1],minite[1],hr[1]);
				s[0]=54;
				s[1]=0;
				s[2]=3;
				s[3]=0;
				return;
			}
			///选择第一组有效/无效
			if(s[0]==5&&s[1]==1&&s[2]==1&&s[3]==2)
			{
					menu21_21(valid[0]);
					s[0]=57;
				  s[2]=0;
				  s[3]=0;
				  s[1]=0;
					s[4]=0;
        return;
			}
			///选择第一组返回
			if(s[0]==5&&s[1]==1&&s[2]==0&&s[3]==3)
			{
				menu2();
				s[0]=3;
				s[2]=3;
				s[3]=0;
				s[1]=0;
						SYS_UnlockReg();
						 FMC_Open();
					/* Read Data Flash base address */
					u32Addr = FMC_ReadDataFlashBaseAddr();
					printf("  Data Flash Base Address ............... [0x%08x]\n", u32Addr); 
					/*读dataflash地址0*/ 
					u32[0] = FMC_Read(u32Addr);
					u32[1] = FMC_Read(u32Addr+4);
					u32[2] = FMC_Read(u32Addr+8);
					u32[3] = FMC_Read(u32Addr+12);
					u32[4] = FMC_Read(u32Addr+16);
					u32[5] = FMC_Read(u32Addr+20);				
				  ////把第一组的数据写进去
				  u32[1]=u32[1]&0x6000000;
				  u32[1]=u32[1]|(second[0]&0xff);
				  u32[1]=u32[1]|((minite[0]&0xff)<<8);
					u32[1]=u32[1]|((hr[0]&0xff)<<16);
					u32[1]=u32[1]|((valid[0]&0x1)<<24);
					u32[2]=u32[2]&0xff000000;
				  u32[2]=u32[2]|(second[1]&0xff);
				  u32[2]=u32[2]|((minite[1]&0xff)<<8);
					u32[2]=u32[2]|((hr[1]&0xff)<<16);
							/* 擦除一个page */ 
					 FMC_Erase(u32Addr);
					/*写4 Bytes到dataflash地址0*/ 
					 FMC_Write(u32Addr,u32[0]);
					 FMC_Write(u32Addr+4,u32[1]);
					 FMC_Write(u32Addr+8,u32[2]);
					 FMC_Write(u32Addr+12,u32[3]);
					 FMC_Write(u32Addr+16,u32[4]);
					 FMC_Write(u32Addr+20,u32[5]);
						/* Disable FMC ISP function */
						FMC_Close();
						/* Lock protected registers */
						SYS_LockReg();
        return;
			}			
			///确定第一组有效/无效
			if(s[0]==57&&s[1]==1) 
			{
				menu21_2(valid[0]);
				s[0]=5;
				s[2]=1;
				s[3]=2;
				s[1]=1;
				s[4]=0;
				return;
			}

			///选择第一组启动时间，时
			if(s[0]==51&&s[1]==0&&s[2]==3&&s[3]==0)
			{
				menu211_1(second[0],minite[0],hr[0]);
				s[0]=51;
				s[1]=1;
				s[2]=0;
				s[3]=0;
				delay_ms(1000);
				return;
			}
			///选择第一组启动时间，确定时
			if(s[0]==51&&s[1]==1&&s[2]==0&&s[3]==0)
			{
				menu211_0(second[0],minite[0],hr[0]);
				s[0]=51;
				s[1]=0;
				s[2]=3;
				s[3]=0;
				return;
			}
			///选择第一组启动时间，分
			if(s[0]==51&&s[1]==0&&s[2]==2&&s[3]==1)
			{
				menu211_3(second[0],minite[0],hr[0]);
				s[0]=51;
				s[1]=2;
				s[2]=0;
				s[3]=0;
				delay_ms(1000);
				return;
			}
			///选择第一组启动时间，确定分
			if(s[0]==51&&s[1]==2&&s[2]==0&&s[3]==0)
			{
				menu211_2(second[0],minite[0],hr[0]);
				s[0]=51;
				s[1]=0;
				s[2]=2;
				s[3]=1;
				return;
			}
			///选择第一组启动时间，秒
			if(s[0]==51&&s[1]==0&&s[2]==1&&s[3]==2)
			{
				menu211_5(second[0],minite[0],hr[0]);
				s[0]=51;
				s[1]=3;
				s[2]=0;
				s[3]=0;
				delay_ms(1000);
				return;
			}
			///选择第一组启动时间，确定秒
			if(s[0]==51&&s[1]==3&&s[2]==0&&s[3]==0)
			{
				menu211_4(second[0],minite[0],hr[0]);
				s[0]=51;
				s[1]=0;
				s[2]=1;
				s[3]=2;
				return;
			}
			///选择第一组启动时间，返回
			if(s[0]==51&&s[1]==0&&s[2]==0&&s[3]==3)
			{
				menu21(valid[0]);
				s[0]=5;
				s[1]=1;
				s[2]=3;
				s[3]=0;
				return;
			}
			///选择第一组关闭时间，时
			if(s[0]==54&&s[1]==0&&s[2]==3&&s[3]==0)
			{
				menu211_1(second[1],minite[1],hr[1]);
				s[0]=54;
				s[1]=1;
				s[2]=0;
				s[3]=0;
				delay_ms(1000);
				return;
			}
			///选择第一组关闭时间，确定时
			if(s[0]==54&&s[1]==1&&s[2]==0&&s[3]==0)
			{
				menu211_0(second[1],minite[1],hr[1]);
				s[0]=54;
				s[1]=0;
				s[2]=3;
				s[3]=0;
				return;
			}
			///选择第一组关闭时间，分
			if(s[0]==54&&s[1]==0&&s[2]==2&&s[3]==1)
			{
				menu211_3(second[1],minite[1],hr[1]);
				s[0]=54;
				s[1]=2;
				s[2]=0;
				s[3]=0;
				delay_ms(1000);
				return;
			}
			///选择第一组关闭时间，确定分
			if(s[0]==54&&s[1]==2&&s[2]==0&&s[3]==0)
			{
				menu211_2(second[1],minite[1],hr[1]);
				s[0]=54;
				s[1]=0;
				s[2]=2;
				s[3]=1;
				return;
			}
			///选择第一组关闭时间，秒
			if(s[0]==54&&s[1]==0&&s[2]==1&&s[3]==2)
			{
				menu211_5(second[1],minite[1],hr[1]);
				s[0]=54;
				s[1]=3;
				s[2]=0;
				s[3]=0;
				delay_ms(1000);
				return;
			}
			///选择第一组关闭时间，确定秒
			if(s[0]==54&&s[1]==3&&s[2]==0&&s[3]==0)
			{
				menu211_4(second[1],minite[1],hr[1]);
				s[0]=54;
				s[1]=0;
				s[2]=1;
				s[3]=2;
				return;
			}
			///选择第一组关闭时间，返回
			if(s[0]==54&&s[1]==0&&s[2]==0&&s[3]==3)
			{
				menu21(valid[0]);
				s[0]=5;
				s[1]=1;
				s[2]=3;
				s[3]=0;
				return;
			}
///选择第二组
			if(s[0]==3&&s[2]==2&&s[3]==1)
			{
				menu22(valid[1]);
				s[0]=5;
				s[2]=3;
				s[3]=0;
				s[1]=2;
				return;
			}
			///选择第二组启动时间
			if(s[0]==5&&s[1]==2&&s[2]==3&&s[3]==0)
			{
				menu211(second[2],minite[2],hr[2]);
				s[0]=52;
				s[1]=0;
				s[2]=3;
				s[3]=0;
				return;
			}
			///选择第二组关闭时间
			if(s[0]==5&&s[1]==2&&s[2]==2&&s[3]==1)
			{
				menu212(second[3],minite[3],hr[3]);
				s[0]=55;
				s[1]=0;
				s[2]=3;
				s[3]=0;
				return;
			}
			///选择第二组返回
			if(s[0]==5&&s[1]==2&&s[2]==0&&s[3]==3)
			{
				menu2();
				s[0]=3;
				s[2]=3;
				s[3]=0;
				s[1]=0;
						SYS_UnlockReg();
						 FMC_Open();
					/* Read Data Flash base address */
					u32Addr = FMC_ReadDataFlashBaseAddr();
					printf("  Data Flash Base Address ............... [0x%08x]\n", u32Addr); 
					/*读dataflash地址0*/ 
					u32[0] = FMC_Read(u32Addr);
					u32[1] = FMC_Read(u32Addr+4);
					u32[2] = FMC_Read(u32Addr+8);
					u32[3] = FMC_Read(u32Addr+12);
					u32[4] = FMC_Read(u32Addr+16);
					u32[5] = FMC_Read(u32Addr+20);				
				  ////把第二组的数据写进去
				  u32[1]=u32[1]&0x5ffffff;
					u32[1]=u32[1]|((valid[1]&0x1)<<25);
					u32[2]=u32[2]&0x00ffffff;
				  u32[2]=u32[2]|((second[2]&0xff)<<24);
					u32[3]=u32[3]&0x0;
				  u32[3]=u32[3]|(minite[2]&0xff);
				  u32[3]=u32[3]|((hr[2]&0xff)<<8);
					u32[3]=u32[3]|((second[3]&0xff)<<16);
					u32[3]=u32[3]|((minite[3]&0xff)<<24);
					u32[4]=u32[4]&0xffffff00;
				  u32[4]=u32[4]|(hr[3]&0xff);
							/* 擦除一个page */ 
					 FMC_Erase(u32Addr);
					/*写4 Bytes到dataflash地址0*/ 
					 FMC_Write(u32Addr,u32[0]);
					 FMC_Write(u32Addr+4,u32[1]);
					 FMC_Write(u32Addr+8,u32[2]);
					 FMC_Write(u32Addr+12,u32[3]);
					 FMC_Write(u32Addr+16,u32[4]);
					 FMC_Write(u32Addr+20,u32[5]);
						/* Disable FMC ISP function */
						FMC_Close();
						/* Lock protected registers */
						SYS_LockReg();
        return;
			}	
			///选择第二组有效/无效
			if(s[0]==5&&s[1]==2&&s[2]==1&&s[3]==2)
			{

					menu21_21(valid[1]);
					s[0]=58;
				  s[2]=0;
				  s[3]=0;
				  s[1]=0;
					s[4]=0;				
        return;
			}
			///确定第二组有效/无效
			if(s[0]==58&&s[1]==1) //有效
			{
				menu21_2(valid[1]);
				s[0]=5;
				s[2]=1;
				s[3]=2;
				s[1]=2;
				s[4]=0;
				return;
			}		
			///选择第二组启动时间，时
			if(s[0]==52&&s[1]==0&&s[2]==3&&s[3]==0)
			{
				menu211_1(second[2],minite[2],hr[2]);
				s[0]=52;
				s[1]=1;
				s[2]=0;
				s[3]=0;
				delay_ms(1000);
				return;
			}
			///选择第二组启动时间，确定时
			if(s[0]==52&&s[1]==1&&s[2]==0&&s[3]==0)
			{
				menu211_0(second[2],minite[2],hr[2]);
				s[0]=52;
				s[1]=0;
				s[2]=3;
				s[3]=0;
				return;
			}
			///选择第二组启动时间，分
			if(s[0]==52&&s[1]==0&&s[2]==2&&s[3]==1)
			{
				menu211_3(second[2],minite[2],hr[2]);
				s[0]=52;
				s[1]=2;
				s[2]=0;
				s[3]=0;
				delay_ms(1000);
				return;
			}
			///选择第二组启动时间，确定分
			if(s[0]==52&&s[1]==2&&s[2]==0&&s[3]==0)
			{
				menu211_2(second[2],minite[2],hr[2]);
				s[0]=52;
				s[1]=0;
				s[2]=2;
				s[3]=1;
				return;
			}
			///选择第二组启动时间，秒
			if(s[0]==52&&s[1]==0&&s[2]==1&&s[3]==2)
			{
				menu211_5(second[2],minite[2],hr[2]);
				s[0]=52;
				s[1]=3;
				s[2]=0;
				s[3]=0;
				delay_ms(1000);
				return;
			}
			///选择第二组启动时间，确定秒
			if(s[0]==52&&s[1]==3&&s[2]==0&&s[3]==0)
			{
				menu211_4(second[2],minite[2],hr[2]);
				s[0]=52;
				s[1]=0;
				s[2]=1;
				s[3]=2;
				return;
			}
			///选择第二组启动时间，返回
			if(s[0]==52&&s[1]==0&&s[2]==0&&s[3]==3)
			{
				menu22(valid[1]);
				s[0]=5;
				s[1]=2;
				s[2]=3;
				s[3]=0;
				return;
			}	
			///选择第二组关闭时间，时
			if(s[0]==55&&s[1]==0&&s[2]==3&&s[3]==0)
			{
				menu211_1(second[3],minite[3],hr[3]);
				s[0]=55;
				s[1]=1;
				s[2]=0;
				s[3]=0;
				delay_ms(1000);
				return;
			}
			///选择第二组关闭时间，确定时
			if(s[0]==55&&s[1]==1&&s[2]==0&&s[3]==0)
			{
				menu211_0(second[3],minite[3],hr[3]);
				s[0]=55;
				s[1]=0;
				s[2]=3;
				s[3]=0;
				return;
			}
			///选择第二组关闭时间，分
			if(s[0]==55&&s[1]==0&&s[2]==2&&s[3]==1)
			{
				menu211_3(second[3],minite[3],hr[3]);
				s[0]=55;
				s[1]=2;
				s[2]=0;
				s[3]=0;
				delay_ms(1000);
				return;
			}
			///选择第二组关闭时间，确定分
			if(s[0]==55&&s[1]==2&&s[2]==0&&s[3]==0)
			{
				menu211_2(second[3],minite[3],hr[3]);
				s[0]=55;
				s[1]=0;
				s[2]=2;
				s[3]=1;
				return;
			}
			///选择第二组关闭时间，秒
			if(s[0]==55&&s[1]==0&&s[2]==1&&s[3]==2)
			{
				menu211_5(second[3],minite[3],hr[3]);
				s[0]=55;
				s[1]=3;
				s[2]=0;
				s[3]=0;
				delay_ms(1000);
				return;
			}
			///选择第二组关闭时间，确定秒
			if(s[0]==55&&s[1]==3&&s[2]==0&&s[3]==0)
			{
				menu211_4(second[3],minite[3],hr[3]);
				s[0]=55;
				s[1]=0;
				s[2]=1;
				s[3]=2;
				return;
			}
			///选择第二组关闭时间，返回
			if(s[0]==55&&s[1]==0&&s[2]==0&&s[3]==3)
			{
				menu22(valid[1]);
				s[0]=5;
				s[1]=2;
				s[2]=3;
				s[3]=0;
				return;
			}			
///选择第三组
			if(s[0]==3&&s[2]==1&&s[3]==2)
			{
				menu23(valid[2]);
				s[0]=5;
				s[2]=3;
				s[3]=0;
				s[1]=3;
				return;
			}
			///选择第三组启动时间
			if(s[0]==5&&s[1]==3&&s[2]==3&&s[3]==0)
			{
				menu211(second[4],minite[4],hr[4]);
				s[0]=53;
				s[1]=0;
				s[2]=3;
				s[3]=0;
				return;
			}
			///选择第三组关闭时间
			if(s[0]==5&&s[1]==3&&s[2]==2&&s[3]==1)
			{
				menu212(second[5],minite[5],hr[5]);
				s[0]=56;
				s[1]=0;
				s[2]=3;
				s[3]=0;
				return;
			}
			///选择第三组返回
			if(s[0]==5&&s[1]==3&&s[2]==0&&s[3]==3)
			{
				
				menu2();
				s[0]=3;
				s[2]=3;
				s[3]=0;
				s[1]=0;
						SYS_UnlockReg();
						 FMC_Open();
					/* Read Data Flash base address */
					u32Addr = FMC_ReadDataFlashBaseAddr();
					printf("  Data Flash Base Address ............... [0x%08x]\n", u32Addr); 
					/*读dataflash地址0*/ 
					u32[0] = FMC_Read(u32Addr);
					u32[1] = FMC_Read(u32Addr+4);
					u32[2] = FMC_Read(u32Addr+8);
					u32[3] = FMC_Read(u32Addr+12);
					u32[4] = FMC_Read(u32Addr+16);
					u32[5] = FMC_Read(u32Addr+20);				
				  ////把第三组的数据写进去
				  u32[1]=u32[1]&0x3ffffff;
					u32[1]=u32[1]|((valid[2]&0x1)<<26);
					u32[4]=u32[4]&0x000000ff;
				  u32[4]=u32[4]|((second[4]&0xff)<<8);
					u32[4]=u32[4]|((minite[4]&0xff)<<16);
					u32[4]=u32[4]|((hr[4]&0xff)<<24);
					u32[5]=u32[5]&0x0;
				  u32[5]=u32[5]|(second[5]&0xff);
				  u32[5]=u32[5]|((minite[5]&0xff)<<8);
					u32[5]=u32[5]|((hr[5]&0xff)<<16);

							/* 擦除一个page */ 
					 FMC_Erase(u32Addr);
					/*写4 Bytes到dataflash地址0*/ 
					 FMC_Write(u32Addr,u32[0]);
					 FMC_Write(u32Addr+4,u32[1]);
					 FMC_Write(u32Addr+8,u32[2]);
					 FMC_Write(u32Addr+12,u32[3]);
					 FMC_Write(u32Addr+16,u32[4]);
					 FMC_Write(u32Addr+20,u32[5]);
						/* Disable FMC ISP function */
						FMC_Close();
						/* Lock protected registers */
						SYS_LockReg();
        return;
			}
			///选择第三组有效/无效
			if(s[0]==5&&s[1]==3&&s[2]==1&&s[3]==2)
			{
					menu21_21(valid[2]);
					s[0]=59;
				  s[2]=0;
				  s[3]=0;
				  s[1]=0;
					s[4]=0;				
        return;
			}
			///确定第三组有效/无效
			if(s[0]==59&&s[1]==1) //有效
			{
				menu21_2(valid[2]);
				s[0]=5;
				s[2]=1;
				s[3]=2;
				s[1]=3;
				s[4]=0;
				return;
			}
			///选择第三组启动时间，时
			if(s[0]==53&&s[1]==0&&s[2]==3&&s[3]==0)
			{
				menu211_1(second[4],minite[4],hr[4]);
				s[0]=53;
				s[1]=1;
				s[2]=0;
				s[3]=0;
				delay_ms(1000);
				return;
			}
			///选择第三组启动时间，确定时
			if(s[0]==53&&s[1]==1&&s[2]==0&&s[3]==0)
			{
				menu211_0(second[4],minite[4],hr[4]);
				s[0]=53;
				s[1]=0;
				s[2]=3;
				s[3]=0;
				return;
			}
			///选择第三组启动时间，分
			if(s[0]==53&&s[1]==0&&s[2]==2&&s[3]==1)
			{
				menu211_3(second[4],minite[4],hr[4]);
				s[0]=53;
				s[1]=2;
				s[2]=0;
				s[3]=0;
				delay_ms(1000);
				return;
			}
			///选择第三组启动时间，确定分
			if(s[0]==53&&s[1]==2&&s[2]==0&&s[3]==0)
			{
				menu211_2(second[4],minite[4],hr[4]);
				s[0]=53;
				s[1]=0;
				s[2]=2;
				s[3]=1;
				return;
			}
			///选择第三组启动时间，秒
			if(s[0]==53&&s[1]==0&&s[2]==1&&s[3]==2)
			{
				menu211_5(second[4],minite[4],hr[4]);
				s[0]=53;
				s[1]=3;
				s[2]=0;
				s[3]=0;
				delay_ms(1000);
				return;
			}
			///选择第三组启动时间，确定秒
			if(s[0]==53&&s[1]==3&&s[2]==0&&s[3]==0)
			{
				menu211_4(second[4],minite[4],hr[4]);
				s[0]=53;
				s[1]=0;
				s[2]=1;
				s[3]=2;
				return;
			}
			///选择第三组启动时间，返回
			if(s[0]==53&&s[1]==0&&s[2]==0&&s[3]==3)
			{
				menu23(valid[2]);
				s[0]=5;
				s[1]=3;
				s[2]=3;
				s[3]=0;
				return;
			}
			///选择第三组关闭时间，时
			if(s[0]==56&&s[1]==0&&s[2]==3&&s[3]==0)
			{
				menu211_1(second[5],minite[5],hr[5]);
				s[0]=56;
				s[1]=1;
				s[2]=0;
				s[3]=0;
				delay_ms(1000);
				return;
			}
			///选择第三组关闭时间，确定时
			if(s[0]==56&&s[1]==1&&s[2]==0&&s[3]==0)
			{
				menu211_0(second[5],minite[5],hr[5]);
				s[0]=56;
				s[1]=0;
				s[2]=3;
				s[3]=0;
				return;
			}
			///选择第三组关闭时间，分
			if(s[0]==56&&s[1]==0&&s[2]==2&&s[3]==1)
			{
				menu211_3(second[5],minite[5],hr[5]);
				s[0]=56;
				s[1]=2;
				s[2]=0;
				s[3]=0;
				delay_ms(1000);
				return;
			}
			///选择第三组关闭时间，确定分
			if(s[0]==56&&s[1]==2&&s[2]==0&&s[3]==0)
			{
				menu211_2(second[5],minite[5],hr[5]);
				s[0]=56;
				s[1]=0;
				s[2]=2;
				s[3]=1;
				return;
			}
			///选择第三组关闭时间，秒
			if(s[0]==56&&s[1]==0&&s[2]==1&&s[3]==2)
			{
				menu211_5(second[5],minite[5],hr[5]);
				s[0]=56;
				s[1]=3;
				s[2]=0;
				s[3]=0;
				delay_ms(1000);
				return;
			}
			///选择第三组关闭时间，确定秒
			if(s[0]==56&&s[1]==3&&s[2]==0&&s[3]==0)
			{
				menu211_4(second[5],minite[5],hr[5]);
				s[0]=56;
				s[1]=0;
				s[2]=1;
				s[3]=2;
				return;
			}
			///选择第三组关闭时间，返回
			if(s[0]==56&&s[1]==0&&s[2]==0&&s[3]==3)
			{
				menu23(valid[2]);
				s[0]=5;
				s[1]=3;
				s[2]=3;
				s[3]=0;
				return;
			}	
			///选择返回
			if(s[0]==3&&s[2]==0&&s[3]==3)
			{
			  menu();
			  s[0]=1;
				s[1]=0;
			  s[2]=3;
			  s[3]=0;
				return;				
			}
//////////进入系统设置首页////////////////////////////////////////////////
			if(s[0]==1&&s[2]==1&&s[3]==2)
			{
				menu3();
				s[0]=4;
				s[2]=4;
				s[3]=0;
				return;
			}
			/////选择时间设置
			if(s[0]==4&&s[2]==4&&s[3]==0)
			{
				menu31(sec, min,  hour, day, date, month, year);
				s[0]=6;
				s[2]=3;
				s[3]=0;
				return;
			}
			///选择时间设置，年份
			if(s[0]==6&&s[2]==3&&s[3]==0)
			{
				menu31_1(year);
				s[0]=61;
				s[1]=0;
				delay_ms(1000);
				return;
			}
			////确定年份
			if(s[0]==61)
			{
				menu31_0(sec, min,  hour, day, date, month, year);
				s[0]=6;
				s[2]=3;
				s[3]=0;
				s[1]=0;
				return;
			}
			///选择时间设置，日期，月
			if(s[0]==6&&s[2]==2&&s[3]==1)
			{
				menu31_3(date, month);
				s[0]=62;
				s[1]=0;
				return;
			}
		///确定日期，月
			if(s[0]==62)
			{
				menu31_4(date, month);
				s[0]=63;
				s[1]=0;
				return;
			}
			///确定日期，日
			if(s[0]==63)
			{
				menu31_2(sec, min,  hour, day, date, month, year);
				s[0]=6;
				s[2]=2;
				s[3]=1;
				s[1]=0;
				return;
			}
			///选择时间设置，时间，时
			if(s[0]==6&&s[2]==1&&s[3]==2)
			{
				menu31_6(sec, min,  hour);
				s[0]=64;
				s[1]=0;
				return;
			}
			///确定时间，时
			if(s[0]==64)
			{
				menu31_7(sec, min,  hour);
				s[0]=65;
				s[1]=0;
				return;
			}
			///确定时间，分
			if(s[0]==65)
			{
				menu31_8(sec, min,  hour);
				s[0]=66;
				s[1]=0;
				return;
			}
			///确定时间，秒
			if(s[0]==66)
			{
				menu31_5(sec, min,  hour, day, date, month, year);
				s[0]=6;
				s[1]=0;
				s[2]=1;
				s[3]=2;
				return;
			}
			////时间里面的返回
			if(s[0]==6&&s[2]==0&&s[3]==3)
			{
				menu3();
				Settime(year,month,date,day,hour,min,sec);
				s[0]=4;
				s[2]=4;
				s[3]=0;
				s[1]=0;
				return;
			}			
///////////////////选择风扇
			if(s[0]==4&&s[2]==3&&s[3]==1)
			{
				menu32();
				s[0]=7;
				s[2]=4;
				s[3]=0;
				return;
			}
			////选择高档
			if(s[0]==7&&s[2]==4&&s[3]==0)
			{
				menu3();
				s[0]=4;
				s[2]=4;
				s[3]=0;		
				CS3=0;
				SPI_WriteData2(0x1105);  //11v
				delay_us(1);
				CS3=1;				
				return;
			}	
			////选择中高档
			if(s[0]==7&&s[2]==3&&s[3]==1)
			{
				menu3();
				s[0]=4;
				s[2]=4;
				s[3]=0;	
				CS3=0;
				SPI_WriteData2(0x11b5); //10v
				delay_us(1);
				printf("\n10v\n");
				CS3=1;				
				return;
			}
			////选择中档
			if(s[0]==7&&s[2]==2&&s[3]==2)
			{
				menu3();
				s[0]=4;
				s[2]=4;
				s[3]=0;	
				CS3=0;
				SPI_WriteData2(0x11bd);  //9v
				delay_us(1);
				printf("\n9v\n");
				CS3=1;				
				return;
			}
			////选择中低档
			if(s[0]==7&&s[2]==1&&s[3]==3)
			{
				menu3();
				s[0]=4;
				s[2]=4;
				s[3]=0;
				CS3=0;
				SPI_WriteData2(0x11c6);  //8v
				delay_us(1);
				printf("\n8v\n");
				CS3=1;				
				return;
			}
			////选择低档
			if(s[0]==7&&s[2]==0&&s[3]==4)
			{
				menu3();
				s[0]=4;
				s[2]=4;
				s[3]=0;	
				CS3=0;
				SPI_WriteData2(0x11cf);  //7v
				delay_us(1);
				printf("\n7v\n");
				CS3=1;				
				return;
			}			
			////选择温度校准
			if(s[0]==4&&s[2]==2&&s[3]==2)
			{
				menu33(tempErr,symbol);
				s[0]=8;
				s[1]=2;
				s[4]=0;
				return;
			}
///////////温度校准里面的设置/////////////////////////////////////////////
			///确定符号
			if(s[0]==8&&s[1]==2&&s[4]==0)
			{
				menu33_1(tempErr,symbol);
				s[0]=8;
				s[1]=1;
				s[4]=0;
						
						SYS_UnlockReg();
						 FMC_Open();
					/* Read Data Flash base address */
					u32Addr = FMC_ReadDataFlashBaseAddr();
					/*读dataflash地址0*/ 
					u32[0] = FMC_Read(u32Addr);
					u32[1] = FMC_Read(u32Addr+4);
					u32[2] = FMC_Read(u32Addr+8);
					u32[3] = FMC_Read(u32Addr+12);
					u32[4] = FMC_Read(u32Addr+16);
					u32[5] = FMC_Read(u32Addr+20);				
				  ////把温度校准符号写入
				printf("\nsymbol1:%d",symbol);
          u32[0]=(u32[0]&0x0fffff)|((symbol&0x1)<<20);
							/* 擦除一个page */ 
					 FMC_Erase(u32Addr);
					/*写4 Bytes到dataflash地址0*/ 
					 FMC_Write(u32Addr,u32[0]);
					 FMC_Write(u32Addr+4,u32[1]);
					 FMC_Write(u32Addr+8,u32[2]);
					 FMC_Write(u32Addr+12,u32[3]);
					 FMC_Write(u32Addr+16,u32[4]);
					 FMC_Write(u32Addr+20,u32[5]);
						/* Disable FMC ISP function */
						FMC_Close();
						/* Lock protected registers */
						SYS_LockReg();
						delay_ms(1000);
				return;
			}
			
	///确定校验差，返回系统设置
			if(s[0]==8&&s[1]==1)
			{
				menu3();
				s[0]=4;
				s[2]=4;
				s[3]=0;
				s[4]=0;
				
						 /* Unlock protected registers */
							SYS_UnlockReg();
							/* Enable FMC ISP function */
							 FMC_Open();
						 /* Read Data Flash base address */
						 u32Addr = FMC_ReadDataFlashBaseAddr(); 
					/*读dataflash地址0*/ 
					u32[0] = FMC_Read(u32Addr);
					u32[1] = FMC_Read(u32Addr+4);
					u32[2] = FMC_Read(u32Addr+8);
					u32[3] = FMC_Read(u32Addr+12);
					u32[4] = FMC_Read(u32Addr+16);
					u32[5] = FMC_Read(u32Addr+20);				
				  ////把校验差写进去
				  tempErr1=tempErr*10;
					printf("\ntempErr11:%d\n",tempErr1);
					u32[0]=(u32[0]&0xf00fff)|((tempErr1)<<12);
							/* 擦除一个page */ 
					 FMC_Erase(u32Addr);
					/*写4 Bytes到dataflash地址0*/ 
					 FMC_Write(u32Addr,u32[0]);
					 FMC_Write(u32Addr+4,u32[1]);
					 FMC_Write(u32Addr+8,u32[2]);
					 FMC_Write(u32Addr+12,u32[3]);
					 FMC_Write(u32Addr+16,u32[4]);
					 FMC_Write(u32Addr+20,u32[5]);
							FMC_Close();
							/* Lock protected registers */
							SYS_LockReg();
				
				return;
			}
			////选择温度设置
			if(s[0]==4&&s[2]==1&&s[3]==3)
			{
				menu34(tempset,tempdiff);
				s[0]=9;
				s[2]=2;
				s[3]=0;
				return;
			}	
////////////温度设置里面的操作///////////////////////////////////////
			//进入设定温度
      if(s[0]==9&&s[2]==2&&s[3]==0)
			{
				s[1]=1;
				menu34_01(tempset,tempdiff);
				delay_ms(1000);
				return;
			}
				///确定设置温度
			if(s[0]==9&&s[1]==1)
			{
				s[2]=2;
				s[3]=0;
				s[1]=0;
				menu34_0(tempset,tempdiff);
									/* Unlock protected registers */
						SYS_UnlockReg();
						/* Enable FMC ISP function */
						 FMC_Open();
					/* Read Data Flash base address */
					u32Addr = FMC_ReadDataFlashBaseAddr();
					/*读dataflash地址0*/ 
					u32[0] = FMC_Read(u32Addr);
					u32[1] = FMC_Read(u32Addr+4);
					u32[2] = FMC_Read(u32Addr+8);
					u32[3] = FMC_Read(u32Addr+12);
					u32[4] = FMC_Read(u32Addr+16);
					u32[5] = FMC_Read(u32Addr+20);				
				  ////把第一组的数据写进去
				  tempset1=tempset;
				  u32[0]=(u32[0]&0xffff00)|tempset1;
							/* 擦除一个page */ 
					 FMC_Erase(u32Addr);
					/*写4 Bytes到dataflash地址0*/ 
					 FMC_Write(u32Addr,u32[0]);
					 FMC_Write(u32Addr+4,u32[1]);
					 FMC_Write(u32Addr+8,u32[2]);
					 FMC_Write(u32Addr+12,u32[3]);
					 FMC_Write(u32Addr+16,u32[4]);
					 FMC_Write(u32Addr+20,u32[5]);
						/* Disable FMC ISP function */
						FMC_Close();
						/* Lock protected registers */
						SYS_LockReg();
		 
				return;
			}
	///进入回差设定
			if(s[0]==9&&s[2]==1&&s[3]==1)
			{
				s[1]=2;
				menu34_11(tempset,tempdiff);
				delay_ms(1000);
				return;
			}
			///确定回差设定
			if(s[0]==9&&s[1]==2)
			{
				s[1]=0;
				s[2]=1;
				s[3]=1;
				menu34_1(tempset,tempdiff);
									/* Unlock protected registers */
								SYS_UnlockReg();
								/* Enable FMC ISP function */
								 FMC_Open();
						/* Read Data Flash base address */
							u32Addr = FMC_ReadDataFlashBaseAddr();
					/*读dataflash地址0*/ 
					u32[0] = FMC_Read(u32Addr);
					u32[1] = FMC_Read(u32Addr+4);
					u32[2] = FMC_Read(u32Addr+8);
					u32[3] = FMC_Read(u32Addr+12);
					u32[4] = FMC_Read(u32Addr+16);
					u32[5] = FMC_Read(u32Addr+20);				
				  ////把第一组的数据写进去
				  tempdiff1=tempdiff;
				  u32[0]=(u32[0]&0xfff0ff)|(tempdiff1<<8);

							/* 擦除一个page */ 
					 FMC_Erase(u32Addr);
					/*写4 Bytes到dataflash地址0*/ 
					 FMC_Write(u32Addr,u32[0]);
					 FMC_Write(u32Addr+4,u32[1]);
					 FMC_Write(u32Addr+8,u32[2]);
					 FMC_Write(u32Addr+12,u32[3]);
					 FMC_Write(u32Addr+16,u32[4]);
					 FMC_Write(u32Addr+20,u32[5]);
								/* Disable FMC ISP function */
								FMC_Close();
								/* Lock protected registers */
								SYS_LockReg();
				return;
			}
			///返回系统设置页面
			if(s[0]==9&&s[2]==0&&s[3]==2)
			{
				menu3();
				s[0]=4;
				s[2]=4;
				s[3]=0;				
				return;
			}
			
//////////返回温度显示页面////////////////////////////////////////////////
			if(s[0]==1&&s[2]==0&&s[3]==3)
			{		
        time_now(sec, min, hour, day, date, month, year);				
				Font_Test(tempset,tempErr,symbol);
				checkself();
				s[0]=0;
				s[2]=0;
				s[3]=0;
				return;
			}
//////////返回菜单页面////////////////////////////////////////////////
			if(s[0]==4&&s[2]==0&&s[3]==4)
			{		
			  menu();
			  s[0]=1;
			  s[2]=3;
			  s[3]=0;
				return;
			}
			printf("s2 Interrupt!\n");
		}
/***************************************************************************/
/*******按键上********/
/***************************************************************************/
		if(S2==1)
		{
			if(s[3]>0)
			{
				s[2]++;
				s[3]--;
			}
/////菜单里面的操作
			if(s[0]==1&&s[3]==0&&s[2]==3)  //工作
			{
				menu_0();
			}
			if(s[0]==1&&s[3]==1&&s[2]==2)  //定时
			{
				menu_1();
			}
			if(s[0]==1&&s[3]==2&&s[2]==1)  //系统
			{
				menu_2();
			}
			if(s[0]==1&&s[3]==3&&s[2]==0)   //返回
			{
				menu_3();
			}
///////工作模式里面的操作
			if(s[0]==2&&s[3]==0&&s[2]==2) //自动
			{
				menu1_0();
			}
			if(s[0]==2&&s[3]==1&&s[2]==1) //制热
			{
				menu1_1();
			}
			if(s[0]==2&&s[3]==2&&s[2]==0) //制冷
			{
				menu1_2();
			}
////////////定时设置里面的操作
			if(s[0]==3&&s[2]==3&&s[3]==0) //第一组
			{
				menu2_0();
			}
			if(s[0]==3&&s[2]==2&&s[3]==1) //第二组
			{
				menu2_1();
			}
			if(s[0]==3&&s[2]==1&&s[3]==2) //第三组
			{
				menu2_2();
			}
			if(s[0]==3&&s[2]==0&&s[3]==3) //返回
			{
				menu2_3();
			}
	////////第一组里面的操作
			if(s[0]==5&&s[1]==1&&s[2]==3&&s[3]==0)  ///启动时间
			{
				menu21_0();
			}
			if(s[0]==5&&s[1]==1&&s[2]==2&&s[3]==1)  ///关闭时间
			{
				menu21_1(valid[0]);
			}
			if(s[0]==5&&s[1]==1&&s[2]==1&&s[3]==2)  ///有效 无效
			{
				menu21_2(valid[0]);
			}
			if(s[0]==5&&s[1]==1&&s[2]==0&&s[3]==3)  ///返回
			{
				menu21_3(valid[0]);
			}
		  ////第一组里面启动时间的操作
			if(s[0]==51&&s[1]==0&&s[2]==3&&s[3]==0)
			{
				menu211_0(second[0],minite[0],hr[0]);
			}
			if(s[0]==51&&s[1]==0&&s[2]==2&&s[3]==1)
			{
				menu211_2(second[0],minite[0],hr[0]);
			}
			if(s[0]==51&&s[1]==0&&s[2]==1&&s[3]==2)
			{
				menu211_4(second[0],minite[0],hr[0]);
			}
			if(s[0]==51&&s[1]==0&&s[2]==0&&s[3]==3)
			{
				menu211_6(second[0],minite[0],hr[0]);  //返回
			}
			////第一组启动时间设置，时
			if(s[0]==51&&s[1]==1&&s[2]==0&&s[3]==0)
			{
				if(hr[0]<23)
					 hr[0]++;
				menu211_1(second[0],minite[0],hr[0]);
			}
			////第一组启动时间设置，分
			if(s[0]==51&&s[1]==2&&s[2]==0&&s[3]==0)
			{
				if(minite[0]<59)
					 minite[0]++;
				menu211_3(second[0],minite[0],hr[0]);
			}
		////第一组启动时间设置，秒
			if(s[0]==51&&s[1]==3&&s[2]==0&&s[3]==0)
			{
				if(second[0]<59)
					 second[0]++;
				menu211_5(second[0],minite[0],hr[0]);
			}
		  ////第一组里面关闭时间的操作
			if(s[0]==54&&s[1]==0&&s[2]==3&&s[3]==0)
			{
				menu211_0(second[1],minite[1],hr[1]);
			}
			if(s[0]==54&&s[1]==0&&s[2]==2&&s[3]==1)
			{
				menu211_2(second[1],minite[1],hr[1]);
			}
			if(s[0]==54&&s[1]==0&&s[2]==1&&s[3]==2)
			{
				menu211_4(second[1],minite[1],hr[1]);
			}
			if(s[0]==54&&s[1]==0&&s[2]==0&&s[3]==3)
			{
				menu211_6(second[1],minite[1],hr[1]);
			}
			////第一组关闭时间设置，时
			if(s[0]==54&&s[1]==1&&s[2]==0&&s[3]==0)
			{
				if(hr[1]<24)
					 hr[1]++;
				menu211_1(second[1],minite[1],hr[1]);
			}
			////第一组关闭时间设置，分
			if(s[0]==54&&s[1]==2&&s[2]==0&&s[3]==0)
			{
				if(minite[1]<60)
					 minite[1]++;
				menu211_3(second[1],minite[1],hr[1]);
			}
		////第一组关闭时间设置，秒
			if(s[0]==54&&s[1]==3&&s[2]==0&&s[3]==0)
			{
				if(second[1]<60)
					 second[1]++;
				menu211_5(second[1],minite[1],hr[1]);
			}
			////第一组有效无效的操作
			if(s[0]==57)
			{
				s[1]=1;
				if(valid[0]==0)
				{
					valid[0]=1;
				}
				else{
					valid[0]=0;
				}
				menu21_21(valid[0]);
        delay_ms(100);        
				return;
			}

	////////第二组里面的操作
			if(s[0]==5&&s[1]==2&&s[2]==3&&s[3]==0)  ///启动时间
			{
				menu21_0();
			}
			if(s[0]==5&&s[1]==2&&s[2]==2&&s[3]==1)  ///关闭时间
			{
				menu21_1(valid[1]);
			}
			if(s[0]==5&&s[1]==2&&s[2]==1&&s[3]==2)  ///有效 无效
			{
				menu21_2(valid[1]);
			}
			if(s[0]==5&&s[1]==2&&s[2]==0&&s[3]==3)  ///返回
			{
				menu21_3(valid[1]);
			}
		  ////第二组里面启动时间的操作
			if(s[0]==52&&s[1]==0&&s[2]==3&&s[3]==0)
			{
				menu211_0(second[2],minite[2],hr[2]);
			}
			if(s[0]==52&&s[1]==0&&s[2]==2&&s[3]==1)
			{
				menu211_2(second[2],minite[2],hr[2]);
			}
			if(s[0]==52&&s[1]==0&&s[2]==1&&s[3]==2)
			{
				menu211_4(second[2],minite[2],hr[2]);
			}
			if(s[0]==52&&s[1]==0&&s[2]==0&&s[3]==3)
			{
				menu211_6(second[2],minite[2],hr[2]);
			}
		  ////第二组启动时间设置，时
			if(s[0]==52&&s[1]==1&&s[2]==0&&s[3]==0)
			{
				if(hr[2]<23)
					 hr[2]++;
				menu211_1(second[2],minite[2],hr[2]);
			}
			////第二组启动时间设置，分
			if(s[0]==52&&s[1]==2&&s[2]==0&&s[3]==0)
			{
				if(minite[2]<59)
					 minite[2]++;
				menu211_3(second[2],minite[2],hr[2]);
			}
		////第二组启动时间设置，秒
			if(s[0]==52&&s[1]==3&&s[2]==0&&s[3]==0)
			{
				if(second[2]<59)
					 second[2]++;
				menu211_5(second[2],minite[2],hr[2]);
			}
		  ////第二组里面关闭时间的操作
			if(s[0]==55&&s[1]==0&&s[2]==3&&s[3]==0)
			{
				menu211_0(second[3],minite[3],hr[3]);
			}
			if(s[0]==55&&s[1]==0&&s[2]==2&&s[3]==1)
			{
				menu211_2(second[3],minite[3],hr[3]);
			}
			if(s[0]==55&&s[1]==0&&s[2]==1&&s[3]==2)
			{
				menu211_4(second[3],minite[3],hr[3]);
			}
			if(s[0]==55&&s[1]==0&&s[2]==0&&s[3]==3)
			{
				menu211_6(second[3],minite[3],hr[3]);
			}
		  ////第二组关闭时间设置，时
			if(s[0]==55&&s[1]==1&&s[2]==0&&s[3]==0)
			{
				if(hr[3]<23)
					 hr[3]++;
				menu211_1(second[3],minite[3],hr[3]);
			}
			////第二组关闭时间设置，分
			if(s[0]==55&&s[1]==2&&s[2]==0&&s[3]==0)
			{
				if(minite[3]<59)
					 minite[3]++;
				menu211_3(second[3],minite[3],hr[3]);
			}
		////第二组关闭时间设置，秒
			if(s[0]==55&&s[1]==3&&s[2]==0&&s[3]==0)
			{
				if(second[3]<59)
					 second[3]++;
				menu211_5(second[3],minite[3],hr[3]);
			}			
			////第二组有效无效的操作
			if(s[0]==58)
			{
				s[1]=1;
				if(valid[1]==0)
				{
					valid[1]=1;
				}
				else{
					valid[1]=0;
				}
				menu21_21(valid[1]); 
				delay_ms(1000);
				return;
			}
	////////第三组里面的操作
			if(s[0]==5&&s[1]==3&&s[2]==3&&s[3]==0)  ///启动时间
			{
				menu21_0();
			}
			if(s[0]==5&&s[1]==3&&s[2]==2&&s[3]==1)  ///关闭时间
			{
				menu21_1(valid[2]);
			}
			if(s[0]==5&&s[1]==3&&s[2]==1&&s[3]==2)  ///有效 无效
			{
				menu21_2(valid[2]);
			}
			if(s[0]==5&&s[1]==3&&s[2]==0&&s[3]==3)  ///返回
			{
				menu21_3(valid[2]);
			}
			////第三组里面启动时间的操作
			if(s[0]==53&&s[1]==0&&s[2]==3&&s[3]==0)
			{
				menu211_0(second[4],minite[4],hr[4]);
			}
			if(s[0]==53&&s[1]==0&&s[2]==2&&s[3]==1)
			{
				menu211_2(second[4],minite[4],hr[4]);
			}
			if(s[0]==53&&s[1]==0&&s[2]==1&&s[3]==2)
			{
				menu211_4(second[4],minite[4],hr[4]);
			}
			if(s[0]==53&&s[1]==0&&s[2]==0&&s[3]==3)
			{
				menu211_6(second[4],minite[4],hr[4]);
			}
			////第三组启动时间设置，时
			if(s[0]==53&&s[1]==1&&s[2]==0&&s[3]==0)
			{
				if(hr[4]<23)
					 hr[4]++;
				menu211_1(second[4],minite[4],hr[4]);
			}
			////第三组启动时间设置，分
			if(s[0]==53&&s[1]==2&&s[2]==0&&s[3]==0)
			{
				if(minite[4]<59)
					 minite[4]++;
				menu211_3(second[4],minite[4],hr[4]);
			}
		////第三组启动时间设置，秒
			if(s[0]==53&&s[1]==3&&s[2]==0&&s[3]==0)
			{
				if(second[4]<59)
					 second[4]++;
				menu211_5(second[4],minite[4],hr[4]);
			}
		  ////第三组里面关闭时间的操作
			if(s[0]==56&&s[1]==0&&s[2]==3&&s[3]==0)
			{
				menu211_0(second[5],minite[5],hr[5]);
			}
			if(s[0]==56&&s[1]==0&&s[2]==2&&s[3]==1)
			{
				menu211_2(second[5],minite[5],hr[5]);
			}
			if(s[0]==56&&s[1]==0&&s[2]==1&&s[3]==2)
			{
				menu211_4(second[5],minite[5],hr[5]);
			}
			if(s[0]==56&&s[1]==0&&s[2]==0&&s[3]==3)
			{
				menu211_6(second[5],minite[5],hr[5]);
			}
		  ////第三组关闭时间设置，时
			if(s[0]==56&&s[1]==1&&s[2]==0&&s[3]==0)
			{
				if(hr[5]<24)
					 hr[5]++;
				menu211_1(second[5],minite[5],hr[5]);
			}
			////第三组关闭时间设置，分
			if(s[0]==56&&s[1]==2&&s[2]==0&&s[3]==0)
			{
				if(minite[5]<60)
					 minite[5]++;
				menu211_3(second[5],minite[5],hr[5]);
			}
		////第三组关闭时间设置，秒
			if(s[0]==56&&s[1]==3&&s[2]==0&&s[3]==0)
			{
				if(second[5]<60)
					 second[5]++;
				menu211_5(second[5],minite[5],hr[5]);
			}
			////第三组有效无效的操作
			if(s[0]==59)
			{
				s[1]=1;
				if(valid[2]==0)
				{
					valid[2]=1;
				}
				else{
					valid[2]=0;
				}
				menu21_21(valid[2]);
        delay_ms(1000);        
				return;
			}
////////////系统设置里面的操作
			if(s[0]==4&&s[2]==4&&s[3]==0) //时间设置
			{
				menu3_0();
			}
			if(s[0]==4&&s[2]==3&&s[3]==1) //风扇转速
			{
				menu3_1();
			}
			if(s[0]==4&&s[2]==2&&s[3]==2) //温差
			{
				menu3_2();
			}
			if(s[0]==4&&s[2]==1&&s[3]==3) //温度设置
			{
				menu3_3();
			}
/////////////时间设置里面的操作
			if(s[0]==6&&s[2]==3&&s[3]==0)
			{
				menu31_0(sec, min,  hour, day, date, month, year);
			}
			if(s[0]==6&&s[2]==2&&s[3]==1)
			{
				menu31_2(sec, min,  hour, day, date, month, year);
			}
			if(s[0]==6&&s[2]==1&&s[3]==2)
			{
				menu31_5(sec, min,  hour, day, date, month, year);
			}
			if(s[0]==6&&s[2]==0&&s[3]==3)
			{
				menu31_9(sec, min,  hour, day, date, month, year);
			}
//////////时间设置，年份
      if(s[0]==61)
			{

				if(year<99)
				  year++;
				menu31_1(year);
			}	
//////////时间设置，月
      if(s[0]==62)
			{
				if(month<12)
				  month++;
				menu31_3(date,month);
			}

//////////时间设置，日
      if(s[0]==63)
			{
				if(date<30)
				  date++;
				menu31_4(date,month);
			}
//////////时间设置，时
      if(s[0]==64)
			{
				if(hour<23)
				  hour++;
				menu31_6(sec, min, hour);
			}
//////////时间设置，分
      if(s[0]==65)
			{
				if(min<59)
				  min++;
				menu31_7(sec, min, hour);
			}
//////////时间设置，秒
      if(s[0]==66)
			{
				if(sec<59)
				  sec++;
				menu31_8(sec, min, hour);
			}
///////////////风扇里面的操作	
      if(s[0]==7&&s[2]==4&&s[3]==0)
			{
				menu32_0();
			}
      if(s[0]==7&&s[2]==3&&s[3]==1)
			{
				menu32_1();
			}	
      if(s[0]==7&&s[2]==2&&s[3]==2)
			{
				menu32_2();
			}	
      if(s[0]==7&&s[2]==1&&s[3]==3)
			{
				menu32_3();
			}
      if(s[0]==7&&s[2]==0&&s[3]==4)
			{
				menu32_4();
			}				
///////////////温差里面的操作
			if(s[0]==8&&s[1]==2&&s[4]==0)  //符号设置
			{
				if(symbol==0)
				{
					symbol=1;
				}else
				{
					symbol=0;
				}	
				menu33_0(tempErr,symbol);
			}
			if(s[0]==8&&s[1]==1) //校验差设置
			{
				
					if(tempErr<0.001)
					{
						symbol=0;
						tempErr=tempErr+0.1;
					}
					else
					{
						if(symbol==0&&tempErr<7&&tempErr>0)
							tempErr=tempErr+0.1;
						else
							if(symbol==1&&tempErr<7.1&&tempErr>0)
								tempErr=tempErr-0.1;
					}
					s[4]=0;
					printf("\n temperr:%f\n",tempErr);
					menu33_1(tempErr,symbol);
			}
///////////////温度设置里面的操作
			if(s[0]==9&&s[2]==2&&s[3]==0&&s[1]==0) //温度设定
			{
				menu34_0(tempset,tempdiff);
			}
			if(s[0]==9&&s[2]==1&&s[3]==1&&s[1]==0) //温度回差
			{
				menu34_1(tempset,tempdiff);
			}
			//设温
			if(s[0]==9&&s[1]==1)
			{
				if(tempset<35)
				{
					tempset++;
					menu34_01(tempset,tempdiff);
				}
				s[2]=0;
				s[3]=0;
			}
			///设回差
			if(s[0]==9&&s[1]==2)
			{
				if(tempdiff<(35-tempset))
				{
					tempdiff++;
					menu34_11(tempset,tempdiff);
				}
				s[2]=0;
				s[3]=0;
			}
			
			
			printf("s3 Interrupt!\n");
		}
/****************************************************************************/
/******按键下*******/
/***************************************************************************/
		if(S3==1)
		{
			if(s[2]>0)
			{
				s[3]++;
				s[2]--;
			}
/////////////菜单里面的操作
			if(s[0]==1&&s[3]==1&&s[2]==2)  //定时
			{
				menu_1();
			}
			if(s[0]==1&&s[3]==2&&s[2]==1)  //系统
			{
				menu_2();
			}
			if(s[0]==1&&s[3]==3&&s[2]==0)   //返回
			{
				menu_3();
			}
/////////////工作模式里面的操作
			if(s[0]==2&&s[3]==1&&s[2]==1) //制热
			{
				menu1_1();
			}
			if(s[0]==2&&s[3]==2&&s[2]==0) //制冷
			{
				menu1_2();
			}
////////////定时设置里面的操作
			if(s[0]==3&&s[2]==2&&s[3]==1) //第二组
			{
				menu2_1();
			}
			if(s[0]==3&&s[2]==1&&s[3]==2) //第三组
			{
				menu2_2();
			}
			if(s[0]==3&&s[2]==0&&s[3]==3) //返回
			{
				menu2_3();
			}
	////////第一组里面的操作
			if(s[0]==5&&s[1]==1&&s[2]==3&&s[3]==0)  ///启动时间
			{
				menu21_0();
			}
			if(s[0]==5&&s[1]==1&&s[2]==2&&s[3]==1)  ///关闭时间
			{
				menu21_1(valid[0]);
			}
			if(s[0]==5&&s[1]==1&&s[2]==1&&s[3]==2)  ///有效 无效
			{
				menu21_2(valid[0]);
			}
			if(s[0]==5&&s[1]==1&&s[2]==0&&s[3]==3)  ///返回
			{
				menu21_3(valid[0]);
			}
		  ////第一组里面启动时间的操作
			if(s[0]==51&&s[1]==0&&s[2]==3&&s[3]==0)
			{
				menu211_0(second[0],minite[0],hr[0]);
			}
			if(s[0]==51&&s[1]==0&&s[2]==2&&s[3]==1)
			{
				menu211_2(second[0],minite[0],hr[0]);
			}
			if(s[0]==51&&s[1]==0&&s[2]==1&&s[3]==2)
			{
				menu211_4(second[0],minite[0],hr[0]);
			}
			if(s[0]==51&&s[1]==0&&s[2]==0&&s[3]==3)
			{
				menu211_6(second[0],minite[0],hr[0]);
			}
			////第一组启动时间设置，时
			if(s[0]==51&&s[1]==1&&s[2]==0&&s[3]==0)
			{
				if(hr[0]>0)
					 hr[0]--;
				menu211_1(second[0],minite[0],hr[0]);
			}
			////第一组启动时间设置，分
			if(s[0]==51&&s[1]==2&&s[2]==0&&s[3]==0)
			{
				if(minite[0]>0)
					 minite[0]--;
				menu211_3(second[0],minite[0],hr[0]);
			}
		////第一组启动时间设置，秒
			if(s[0]==51&&s[1]==3&&s[2]==0&&s[3]==0)
			{
				if(second[0]>0)
					 second[0]--;
				menu211_5(second[0],minite[0],hr[0]);
			}
			////第一组里面关闭时间的操作
			if(s[0]==54&&s[1]==0&&s[2]==3&&s[3]==0)
			{
				menu211_0(second[1],minite[1],hr[1]);
			}
			if(s[0]==54&&s[1]==0&&s[2]==2&&s[3]==1)
			{
				menu211_2(second[1],minite[1],hr[1]);
			}
			if(s[0]==54&&s[1]==0&&s[2]==1&&s[3]==2)
			{
				menu211_4(second[1],minite[1],hr[1]);
			}
			if(s[0]==54&&s[1]==0&&s[2]==0&&s[3]==3)
			{
				menu211_6(second[1],minite[1],hr[1]);
			}
			////第一组关闭时间设置，时
			if(s[0]==54&&s[1]==1&&s[2]==0&&s[3]==0)
			{
				if(hr[1]>0)
					 hr[1]--;
				menu211_1(second[1],minite[1],hr[1]);
			}
			////第一组关闭时间设置，分
			if(s[0]==54&&s[1]==2&&s[2]==0&&s[3]==0)
			{
				if(minite[1]>0)
					 minite[1]--;
				menu211_3(second[1],minite[1],hr[1]);
			}
		////第一组关闭时间设置，秒
			if(s[0]==54&&s[1]==3&&s[2]==0&&s[3]==0)
			{
				if(second[1]>0)
					 second[1]--;
				menu211_5(second[1],minite[1],hr[1]);
			}
			////第一组有效无效的操作
			if(s[0]==57)
			{
				s[1]=1;
				if(valid[0]==0)
				{
					valid[0]=1;
				}
				else{
					valid[0]=0;
				}				
				menu21_21(valid[0]);  
        delay_ms(1000);				
				return;
			}
	////////第二组里面的操作
			if(s[0]==5&&s[1]==2&&s[2]==3&&s[3]==0)  ///启动时间
			{
				menu21_0();
			}
			if(s[0]==5&&s[1]==2&&s[2]==2&&s[3]==1)  ///关闭时间
			{
				menu21_1(valid[1]);
			}
			if(s[0]==5&&s[1]==2&&s[2]==1&&s[3]==2)  ///有效 无效
			{
				menu21_2(valid[1]);
			}
			if(s[0]==5&&s[1]==2&&s[2]==0&&s[3]==3)  ///返回
			{
				menu21_3(valid[1]);
			}
		  ////第二组里面启动时间的操作
			if(s[0]==52&&s[1]==0&&s[2]==3&&s[3]==0)
			{
				menu211_0(second[2],minite[2],hr[2]);
			}
			if(s[0]==52&&s[1]==0&&s[2]==2&&s[3]==1)
			{
				menu211_2(second[2],minite[2],hr[2]);
			}
			if(s[0]==52&&s[1]==0&&s[2]==1&&s[3]==2)
			{
				menu211_4(second[2],minite[2],hr[2]);
			}
			if(s[0]==52&&s[1]==0&&s[2]==0&&s[3]==3)
			{
				menu211_6(second[2],minite[2],hr[2]);
			}
			////第二组启动时间设置，时
			if(s[0]==52&&s[1]==1&&s[2]==0&&s[3]==0)
			{
				if(hr[2]>0)
					 hr[2]--;
				menu211_1(second[2],minite[2],hr[2]);
			}
			////第二组启动时间设置，分
			if(s[0]==52&&s[1]==2&&s[2]==0&&s[3]==0)
			{
				if(minite[2]>0)
					 minite[2]--;
				menu211_3(second[2],minite[2],hr[2]);
			}
		////第二组启动时间设置，秒
			if(s[0]==52&&s[1]==3&&s[2]==0&&s[3]==0)
			{
				if(second[2]>0)
					 second[2]--;
				menu211_5(second[2],minite[2],hr[2]);
			}
		  ////第二组里面关闭时间的操作
			if(s[0]==55&&s[1]==0&&s[2]==3&&s[3]==0)
			{
				menu211_0(second[3],minite[3],hr[3]);
			}
			if(s[0]==55&&s[1]==0&&s[2]==2&&s[3]==1)
			{
				menu211_2(second[3],minite[3],hr[3]);
			}
			if(s[0]==55&&s[1]==0&&s[2]==1&&s[3]==2)
			{
				menu211_4(second[3],minite[3],hr[3]);
			}
			if(s[0]==55&&s[1]==0&&s[2]==0&&s[3]==3)
			{
				menu211_6(second[3],minite[3],hr[3]);
			}
			////第二组关闭时间设置，时
			if(s[0]==55&&s[1]==1&&s[2]==0&&s[3]==0)
			{
				if(hr[3]>0)
					 hr[3]--;
				menu211_1(second[3],minite[3],hr[3]);
			}
			////第二组关闭时间设置，分
			if(s[0]==55&&s[1]==2&&s[2]==0&&s[3]==0)
			{
				if(minite[3]>0)
					 minite[3]--;
				menu211_3(second[3],minite[3],hr[3]);
			}
		////第二组关闭时间设置，秒
			if(s[0]==55&&s[1]==3&&s[2]==0&&s[3]==0)
			{
				if(second[3]>0)
					 second[3]--;
				menu211_5(second[3],minite[3],hr[3]);
			}
			////第二组有效无效的操作
			if(s[0]==58)
			{
				s[1]=1;
				if(valid[1]==0)
				{
					valid[1]=1;
				}
				else{
					valid[1]=0;
				}
				menu21_21(valid[1]); 
				delay_ms(1000);
				return;
			}
	////////第三组里面的操作
			if(s[0]==5&&s[1]==3&&s[2]==3&&s[3]==0)  ///启动时间
			{
				menu21_0();
			}
			if(s[0]==5&&s[1]==3&&s[2]==2&&s[3]==1)  ///关闭时间
			{
				menu21_1(valid[2]);
			}
			if(s[0]==5&&s[1]==3&&s[2]==1&&s[3]==2)  ///有效 无效
			{
				menu21_2(valid[2]);
			}
			if(s[0]==5&&s[1]==3&&s[2]==0&&s[3]==3)  ///返回
			{
				menu21_3(valid[2]);
			}
			////第三组里面启动时间的操作
			if(s[0]==53&&s[1]==0&&s[2]==3&&s[3]==0)
			{
				menu211_0(second[4],minite[4],hr[4]);
			}
			if(s[0]==53&&s[1]==0&&s[2]==2&&s[3]==1)
			{
				menu211_2(second[4],minite[4],hr[4]);
			}
			if(s[0]==53&&s[1]==0&&s[2]==1&&s[3]==2)
			{
				menu211_4(second[4],minite[4],hr[4]);
			}
			if(s[0]==53&&s[1]==0&&s[2]==0&&s[3]==3)
			{
				menu211_6(second[4],minite[4],hr[4]);
			}
			////第三组启动时间设置，时
			if(s[0]==53&&s[1]==1&&s[2]==0&&s[3]==0)
			{
				if(hr[4]>0)
					 hr[4]--;
				menu211_1(second[4],minite[4],hr[4]);
			}
			////第三组启动时间设置，分
			if(s[0]==53&&s[1]==2&&s[2]==0&&s[3]==0)
			{
				if(minite[4]>0)
					 minite[4]--;
				menu211_3(second[4],minite[4],hr[4]);
			}
		////第三组启动时间设置，秒
			if(s[0]==53&&s[1]==3&&s[2]==0&&s[3]==0)
			{
				if(second[4]>0)
					 second[4]--;
				menu211_5(second[4],minite[4],hr[4]);
			}
		  ////第三组里面关闭时间的操作
			if(s[0]==56&&s[1]==0&&s[2]==3&&s[3]==0)
			{
				menu211_0(second[5],minite[5],hr[5]);
			}
			if(s[0]==56&&s[1]==0&&s[2]==2&&s[3]==1)
			{
				menu211_2(second[5],minite[5],hr[5]);
			}
			if(s[0]==56&&s[1]==0&&s[2]==1&&s[3]==2)
			{
				menu211_4(second[5],minite[5],hr[5]);
			}
			if(s[0]==56&&s[1]==0&&s[2]==0&&s[3]==3)
			{
				menu211_6(second[5],minite[5],hr[5]);
			}
			
			////第三组关闭时间设置，时
			if(s[0]==56&&s[1]==1&&s[2]==0&&s[3]==0)
			{
				if(hr[5]>0)
					 hr[5]--;
				menu211_1(second[5],minite[5],hr[5]);
			}
			////第三组启动时间设置，分
			if(s[0]==56&&s[1]==2&&s[2]==0&&s[3]==0)
			{
				if(minite[5]>0)
					 minite[5]--;
				menu211_3(second[5],minite[5],hr[5]);
			}
		////第三组启动时间设置，秒
			if(s[0]==56&&s[1]==3&&s[2]==0&&s[3]==0)
			{
				if(second[5]>0)
					 second[5]--;
				menu211_5(second[5],minite[5],hr[5]);
			}
			////第三组有效无效的操作
			if(s[0]==59)
			{
				s[1]=1;
				if(valid[2]==0)
				{
					valid[2]=1;
				}
				else{
					valid[2]=0;
				}
				menu21_21(valid[2]);  
				delay_ms(1000);
				return;
			}
////////////系统设置里面的操作
			if(s[0]==4&&s[2]==3&&s[3]==1) //风扇转速
			{
				menu3_1();
			}
			if(s[0]==4&&s[2]==2&&s[3]==2) //温差
			{
				menu3_2();
			}
			if(s[0]==4&&s[2]==1&&s[3]==3) //温度设置
			{
				menu3_3();
			}
			if(s[0]==4&&s[2]==0&&s[3]==4) //返回
			{
				menu3_4();
			}
/////////////时间设置里面的操作
			if(s[0]==6&&s[2]==3&&s[3]==0)
			{
				menu31_0(sec, min,  hour, day, date, month, year);
			}
			if(s[0]==6&&s[2]==2&&s[3]==1)
			{
				menu31_2(sec, min,  hour, day, date, month, year);
			}
			if(s[0]==6&&s[2]==1&&s[3]==2)
			{
				menu31_5(sec, min,  hour, day, date, month, year);
			}
			if(s[0]==6&&s[2]==0&&s[3]==3)
			{
				menu31_9(sec, min,  hour, day, date, month, year);
			}
//////////时间设置，年份
      if(s[0]==61)
			{
				s[1]=1;
				if(year>0)
				  year--;
				menu31_1(year);
			}
//////////时间设置，月
      if(s[0]==62)
			{
				s[1]=1;
				if(month>1)
				  month--;
				menu31_3(date,month);
			}
//////////时间设置，日
      if(s[0]==63)
			{
				s[1]=1;
				if(date>1)
				  date--;
				menu31_4(date,month);
			}
//////////时间设置，时
      if(s[0]==64)
			{
				s[1]=1;
				if(hour>0)
				  hour--;
				menu31_6(sec, min, hour);
			}
//////////时间设置，分
      if(s[0]==65)
			{
				s[1]=1;
				if(min>0)
				  min--;
				menu31_7(sec, min, hour);
			}
//////////时间设置，秒
      if(s[0]==66)
			{
				s[1]=1;
				if(sec>0)
				  sec--;
				menu31_8(sec, min, hour);
			}	
///////////////风扇里面的操作	
      if(s[0]==7&&s[2]==4&&s[3]==0)
			{
				menu32_0();
			}
      if(s[0]==7&&s[2]==3&&s[3]==1)
			{
				menu32_1();
			}	
      if(s[0]==7&&s[2]==2&&s[3]==2)
			{
				menu32_2();
			}	
      if(s[0]==7&&s[2]==1&&s[3]==3)
			{
				menu32_3();
			}
      if(s[0]==7&&s[2]==0&&s[3]==4)
			{
				menu32_4();
			}			
///////////////温差里面的操作
			if(s[0]==8&&s[1]==2&&s[4]==0)  //符号设置
			{
				if(symbol==0)
				{
					symbol=1;
				}else
				{
					symbol=0;
				}				
				menu33_0(tempErr,symbol);
			}
			if(s[0]==8&&s[1]==1) //校验差设置
			{
				
				if(tempErr<0.001)
				{
					symbol=1;
					tempErr=tempErr+0.1;
				}
				else
				{
					if(symbol==0&&tempErr>0&&tempErr<7.1)
						tempErr=tempErr-0.1;
					else
						if(symbol==1&&tempErr>0&&tempErr<7)
							tempErr=tempErr+0.1;
				}
				s[4]=0;
				printf("\n temperr:%f\n",tempErr);
				menu33_1(tempErr,symbol);
			}
///////////////温度设置里面的操作			
			if(s[0]==9&&s[2]==1&&s[3]==1&&s[1]==0) //温度回差
			{
				menu34_1(tempset,tempdiff);
			}
			if(s[0]==9&&s[2]==0&&s[3]==2&&s[1]==0) //返回
			{
				menu34_2(tempset,tempdiff);
			}
			//设温
			if(s[0]==9&&s[1]==1)
			{
				if(tempset>15)    ////测试，最后要是15
				{
					tempset--;
					menu34_01(tempset,tempdiff);
				}
				s[2]=0;
				s[3]=0;
			}
			///设回差
			if(s[0]==9&&s[1]==2)
			{
				if(tempdiff>2)
				{
					tempdiff--;
					menu34_11(tempset,tempdiff);
				}
				s[2]=0;
				s[3]=0;
			}
			
			printf("s4 Interrupt!\n");
		}

		
/***************************************************************************/
/*****照明*****/
/***************************************************************************/
		if(S5==1)
		{
			if(lampstate==0)   ///开灯
			{
				lamp=1;
				lampstate=~lampstate;
			}
			else    ////关灯
			{
				lamp=0;
				lampstate=~lampstate;  
			}
			printf("s5 Interrupt!\n");
		}
/***************************************************************************/
/*****开关*****/
/***************************************************************************/
		if(S8==1)
		{
			if(s8_state==0&&s[0]==0) 
			{
				s[0]=99;
				stop();
				pump1=0;
				pump2=0;
				hot=0;
				cold=0;
				fan=0;
				s8_state=1;
				
			}
			else if(s8_state==1&&s[0]==99)
			{

		      checkself();  //自检
				  s8_state=0;
				  s[0]=0;
			}
		
			printf("s8 Interrupt!\n");
		}
		
		
	
    /* Clear P3.3 interrupt flag */
    GPIO_CLR_INT_FLAG(P3, BIT3);
//    printf("EINT1 Interrupt!\n");
    
}

/*--------------------------------------------------------------------------------------------------------------*/

/*  EINT1_IRQHandler()  外部中断                                                                                                      */

/*----------------------------------------------------------------------------------------------------------------*/
void EINT0_IRQHandler(void)
{
	
}

/*************************************************************************************************************/
void SYS_Init(void)
{
    /*---------------------------------------------------------------------------------------------------------*/
    /* Init System Clock                                                                                       */
    /*---------------------------------------------------------------------------------------------------------*/
    /* Enable Internal RC 22.1184MHz clock */
    CLK_EnableXtalRC(CLK_PWRCON_OSC22M_EN_Msk);

    /* Waiting for Internal RC clock ready */
    CLK_WaitClockReady(CLK_CLKSTATUS_OSC22M_STB_Msk);

    /* Switch HCLK clock source to Internal RC and HCLK source divide 1 */
    CLK_SetHCLK(CLK_CLKSEL0_HCLK_S_HIRC, CLK_CLKDIV_HCLK(1));

    /* Enable external XTAL 12MHz clock */
    CLK_EnableXtalRC(CLK_PWRCON_XTL12M_EN_Msk);

    /* Waiting for external XTAL clock ready */
    CLK_WaitClockReady(CLK_CLKSTATUS_XTL12M_STB_Msk);

    /* Set core clock as PLL_CLOCK from PLL */
    CLK_SetCoreClock(PLL_CLOCK);

    /* Enable UART module clock */
    CLK_EnableModuleClock(UART0_MODULE);

    /* Select UART module clock source */
    CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UART_S_PLL, CLK_CLKDIV_UART(1));
		
			/* Switch HCLK clock source to HXT and HCLK source divide 1 */
    CLK_SetHCLK(CLK_CLKSEL0_HCLK_S_HXT, CLK_CLKDIV_HCLK(1));
		
		/* Select HCLK as the clock source of SPI1 */
   CLK_SetModuleClock(SPI1_MODULE, CLK_CLKSEL1_SPI1_S_HCLK, MODULE_NoMsk);
		
		/* Enable SPI1 peripheral clock */
    CLK_EnableModuleClock(SPI1_MODULE);

	/* Timer0选择HCLK做时钟源，并且不除频 */ 
	CLK_SetModuleClock(TMR0_MODULE, CLK_CLKSEL1_TMR0_S_HCLK,MODULE_NoMsk); 
	/* 使能Timer0的时钟 */ 
	CLK_EnableModuleClock(TMR0_MODULE); 
    /*---------------------------------------------------------------------------------------------------------*/
    /* Init I/O Multi-function                                                                                 */
    /*---------------------------------------------------------------------------------------------------------*/

    /* Set P3 multi-function pins for UART0 RXD and TXD */
    SYS->P3_MFP &= ~(SYS_MFP_P30_Msk | SYS_MFP_P31_Msk);
    SYS->P3_MFP |= (SYS_MFP_P30_RXD0 | SYS_MFP_P31_TXD0);
		
		/* Configure P as Output mode  */
    GPIO_SetMode(P0, BIT0, GPIO_PMD_OUTPUT);
		GPIO_SetMode(P0, BIT1, GPIO_PMD_OUTPUT);
		
		/* Setup SPI1 multi-function pins */
    SYS->P0_MFP = SYS_MFP_P04_SPISS1 | SYS_MFP_P05_MOSI_1 | SYS_MFP_P06_MISO_1 | SYS_MFP_P07_SPICLK1;
    /* Update System Core Clock */
    /* User can use SystemCoreClockUpdate() to calculate SystemCoreClock and CyclesPerUs automatically. */
    SystemCoreClockUpdate();

}
/*--------------------------------------------------------------------------------------------------------------*/

/*  UART0_Init()                                                                                                        */

/*----------------------------------------------------------------------------------------------------------------*/
void UART0_Init(void)
{
    /*---------------------------------------------------------------------------------------------------------*/
    /* Init UART                                                                                               */
    /*---------------------------------------------------------------------------------------------------------*/
    /* Reset UART0 */
    SYS_ResetModule(UART0_RST);

    /* Configure UART0 and set UART0 Baudrate */
    UART_Open(UART0, 115200);
}
/*--------------------------------------------------------------------------------------------------------------*/

/*  SPI_Init()                                                                                                        */

/*----------------------------------------------------------------------------------------------------------------*/
void SPI_Init(void)
{
	    /*---------------------------------------------------------------------------------------------------------*/
    /* Init SPI                                                                                                */
    /*---------------------------------------------------------------------------------------------------------*/
    /* Configure as a master, clock idle low, 32-bit transaction, drive output on falling clock edge and latch input on rising edge. */
    /* Set IP clock divider. SPI clock rate = 2MHz */
    SPI_Open(SPI1, SPI_MASTER, SPI_MODE_3, 16, 32000);

    /* Enable the automatic hardware slave select function. Select the SS pin and configure as low-active. */
    SPI_EnableAutoSS(SPI1, SPI_SS, SPI_SS_ACTIVE_LOW);

}

/*--------------------------------------------------------------------------------------------------------------*/

/*  GPIO_Init(void)                                                                                                        */

/*----------------------------------------------------------------------------------------------------------------*/
void GPIO_Init(void)
{
	//设置为输入
	GPIO_SetMode(P2, BIT0, GPIO_PMD_INPUT);
	GPIO_SetMode(P2, BIT1, GPIO_PMD_INPUT);
	GPIO_SetMode(P2, BIT2, GPIO_PMD_INPUT);
	GPIO_SetMode(P2, BIT3, GPIO_PMD_INPUT);
	GPIO_SetMode(P2, BIT4, GPIO_PMD_INPUT);
	GPIO_SetMode(P2, BIT5, GPIO_PMD_INPUT);
	GPIO_SetMode(P2, BIT6, GPIO_PMD_INPUT);
	GPIO_SetMode(P2, BIT7, GPIO_PMD_INPUT);
			    /* Configure P as Output mode  */
    GPIO_SetMode(P4, BIT0, GPIO_PMD_OUTPUT);
		GPIO_SetMode(P4, BIT4, GPIO_PMD_OUTPUT);
		GPIO_SetMode(P4, BIT5, GPIO_PMD_OUTPUT);
		    /* Configure P to default Quasi-bidirectional mode */
    GPIO_SetMode(P4, BIT0, GPIO_PMD_QUASI);
		GPIO_SetMode(P4, BIT4, GPIO_PMD_QUASI);
		GPIO_SetMode(P4, BIT5, GPIO_PMD_QUASI);
    /* Debounce function control */
    GPIO_SET_DEBOUNCE_TIME(GPIO_DBCLKSRC_HCLK, GPIO_DBCLKSEL_1024);
    GPIO_ENABLE_DEBOUNCE(P3, BIT2 | BIT3);

    /* Configure P3.3 external interrupt */
    GPIO_EnableEINT1(P3, 3, GPIO_INT_BOTH_EDGE);
    NVIC_EnableIRQ(EINT1_IRQn);

}
/*--------------------------------------------------------------------------------------------------------------*/

/*  Time 0                                                                                                        */

/*----------------------------------------------------------------------------------------------------------------*/
void Timer_Init(void) 
{ 

	/* 初始化Timer0，周期模式，每秒发生一次中断*/ 
	TIMER_Open(TIMER0, TIMER_PERIODIC_MODE, 1000); 
	/* 如果要修改预分频和比较寄存器的值可以用下面两个宏 */ 
	TIMER_SET_CMP_VALUE(TIMER0, 0xffffff);//修改比较寄存器的值 
	TIMER_SET_PRESCALE_VALUE(TIMER0, 0x00);//修改预分频的值 
	/* 使能Timer0中断 */ 
	TIMER_EnableInt(TIMER0); 
	NVIC_EnableIRQ(TMR0_IRQn); 
  TIMER_Start(TIMER0);
	}
/*--------------------------------------------------------------------------------------------------------------*/

/*  //向SPI总线传输一个16位数据                                                                                                       */

/*----------------------------------------------------------------------------------------------------------------*/

void  SPI_WriteData2(int Data)
{
	int i;
	CLK3=0;
	for(i=16;i>0;i--)
	{
		if(Data&0x8000)	
		OUT3=1; //输出数据
		else OUT3=0;
		delay_us(1);
		CLK3=1;
		delay_us(1);
		CLK3=0;
		delay_us(1);
		Data<<=1;
	}
	
	CLK3=0;
}
/*--------------------------------------------------------------------------------------------------------------*/

/*  上电自检                                                                                                        */

/*----------------------------------------------------------------------------------------------------------------*/
	void checkself(void)
	{
		
		
		
		/****************/
		if(P25==0)
		{
			pump1=0;   //关回水泵			
		}
		else
		{
			 //开回水泵
			pump1=1;
		}
		/**********************/
		if(P26==0)
		{
			pump2=0;   //关出水泵
			cold=0;
			hot=0;
			fan=0;
      state_count=0;			
		}
		else
		{
			 //开出水泵
			pump2=1;
		}
		/**************************/
		   temp=temp_dq(tempErr,symbol);
						if(temp<(tempset-tempdiff)&&P26==1)  //加热
							{
								hoting();
								un_state=0;
								cold=0;	
								hot=1;
								fan=1;
								hotstate=1;
								printf("\nhot\n");
								
							}

							if(temp>(tempset+tempdiff)&&P26==1)  //制冷
							{
								colding();
								un_state=0;
								hot=0;
								cold=1;
								fan=1;
								hotstate=0;
								printf("\ncold\n");
								
							}
							if((temp>=tempset-tempdiff)&&temp<=tempset+tempdiff&&P26==1)
							{
								un_state=0;
								cold=0;
								hot=0;
								fan=0;
								normal();
								printf("\nconstant\n");
							}
							if(P26==0)
							{
								cold=0;
								hot=0;
								fan=0;
								un_state=1;
								unnormal();
							}
	}
/*--------------------------------------------------------------------------------------------------------------*/

/*  main                                                                                                        */

/*----------------------------------------------------------------------------------------------------------------*/

int main(void){
	uint32_t u32Data,u32Addr,x,year1;
	unsigned int t1,t2;


    /* Unlock protected registers */
     SYS_UnlockReg();

    /* Init System, peripheral clock and multi-function I/O */
    SYS_Init();
                                                                                                     
    /* Lock protected registers */
    SYS_LockReg();

    /* Init UART0 for printf */
    UART0_Init();
	
	
////读data flash里面的数据		
    /* Unlock protected registers */
    SYS_UnlockReg();
	    /* Enable FMC ISP function */
    FMC_Open();
	/* Read Data Flash base address */
    u32Addr = FMC_ReadDataFlashBaseAddr();
	  printf("  Data Flash Base Address ............... [0x%08x]\n", u32Addr);
	/*读dataflash地址0*/ 
	  u32Data = FMC_Read(u32Addr); 
	  printf("\n    data: 0x%x    \r\n", u32Data);
	  if (u32Data != 0xffffffff) 
	   {
	     	tempset1=u32Data&0xff; 
			  tempset=tempset1;
			  tempdiff1=(u32Data&0xf00)>>8;
			  tempdiff=tempdiff1;
			  tempErr1=(u32Data&0xff000)>>12;
			  printf("\ntempErr:%d",tempErr1);
			  tempErr=tempErr1/10+(tempErr1%10)*0.1;			  
			  symbol=(u32Data&0x100000)>>20;
	   }
			else
			{
				tempset1=tempset;
				tempdiff1=tempdiff;
				tempErr1=tempErr*10;
				u32Data=tempset1&0xff;
				u32Data=u32Data|((tempdiff1&0xf)<<8);
				u32Data=u32Data|((tempErr1&0xff)<<12);
				u32Data=u32Data|((symbol&0x1)<<20);
				FMC_Write(u32Addr,u32Data);
			}
	/*读dataflash地址4*/ 
	  u32Data = FMC_Read(u32Addr+4); 
	  printf("\n    data: 0x%x    \r\n", u32Data);
    if(u32Data != 0xffffffff)
		{
			second[0]=u32Data&0xff;
			minite[0]=(u32Data&0xff00)>>8;
			hr[0]=(u32Data&0xff0000)>>16;
			valid[0]=(u32Data&0x1000000)>>24;
			valid[1]=(u32Data&0x2000000)>>25;
			valid[2]=(u32Data&0x4000000)>>26;
		}
		else
		{
			u32Data=second[0]&0xff;
			u32Data=u32Data|((minite[0]&0xff)<<8);
			u32Data=u32Data|((hr[0]&0xff)<<16);
			u32Data=u32Data|((valid[0]&0x1)<<24);
			u32Data=u32Data|((valid[1]&0x1)<<25);
			u32Data=u32Data|((valid[2]&0x1)<<26);
			FMC_Write(u32Addr+4,u32Data);
		}
		 	
	/*读dataflash地址8*/ 
	  u32Data = FMC_Read(u32Addr+8); 
	  printf("\n    data: 0x%x    \r\n", u32Data);
    if(u32Data != 0xffffffff)
		{
			second[1]=u32Data&0xff;
			minite[1]=(u32Data&0xff00)>>8;
			hr[1]=(u32Data&0xff0000)>>16;
			second[2]=(u32Data&0xff000000)>>24;
		}
		else
		{
			u32Data=second[1]&0xff;
			u32Data=u32Data|((minite[1]&0xff)<<8);
			u32Data=u32Data|((hr[1]&0xff)<<16);
      u32Data=u32Data|((second[2]&0xff)<<24);
			FMC_Write(u32Addr+8,u32Data);
		}
	/*读dataflash地址12*/ 
	  u32Data = FMC_Read(u32Addr+12); 
	  printf("\n    data: 0x%x    \r\n", u32Data);
    if(u32Data != 0xffffffff)
		{
			minite[2]=u32Data&0xff;
			hr[2]=(u32Data&0xff00)>>8;
			second[3]=(u32Data&0xff0000)>>16;
			minite[3]=(u32Data&0xff000000)>>24;
		}
		else
		{
			u32Data=minite[2]&0xff;
			u32Data=u32Data|((hr[2]&0xff)<<8);
			u32Data=u32Data|((second[3]&0xff)<<16);
      u32Data=u32Data|((minite[3]&0xff)<<24);
			FMC_Write(u32Addr+12,u32Data);
		}
	/*读dataflash地址16*/ 
	  u32Data = FMC_Read(u32Addr+16); 
    if(u32Data != 0xffffffff)
		{
			hr[3]=u32Data&0xff;
			second[4]=(u32Data&0xff00)>>8;
			minite[4]=(u32Data&0xff0000)>>16;
			hr[4]=(u32Data&0xff000000)>>24;
		}
		else
		{
			u32Data=hr[3]&0xff;
			u32Data=u32Data|((second[4]&0xff)<<8);
			u32Data=u32Data|((minite[4]&0xff)<<16);
      u32Data=u32Data|((hr[4]&0xff)<<24);
			FMC_Write(u32Addr+16,u32Data);
		}
		/*读dataflash地址20*/ 
	  u32Data = FMC_Read(u32Addr+20); 
    if(u32Data != 0xffffffff)
		{
			second[5]=u32Data&0xff;
			minite[5]=(u32Data&0xff00)>>8;
			hr[5]=(u32Data&0xff0000)>>16;
			
		}
		else
		{
			u32Data=second[5]&0xff;
			u32Data=u32Data|((minite[5]&0xff)<<8);
			u32Data=u32Data|((hr[5]&0xff)<<16);
			FMC_Write(u32Addr+20,u32Data);
		}			
    /* Disable FMC ISP function */
    FMC_Close();
    /* Lock protected registers */
    SYS_LockReg();

		/* Init SPI */
    SPI_Init();
    
	
	  GPIO_Init();
	
		printf("\n\nCPU @ %d Hz\n", SystemCoreClock);
		LCD_Init(); //初始化lcd
		ds18b20_init();
    InitDs1390();
		relay_init();	
		welcome();
		delay_ms(1000);
///读时间		
		t1=readtime();
		t2=readtime2();
		year1=(t2&0xff0000)>>16;

    if(year1<0x12)
			{
				Settime(year,month,date,day, hour, min, sec) ;
			}	
    else{
					sec=t1&0xff;
					min=(t1&0xff00)>>8;
					hour=(t1&0xff0000)>>16;
			    date=t2&0xff;
					month=(t2&0xff00)>>8;
					year=(t2&0xff0000)>>16;
		}			
		time_now(sec, min, hour, day, date, month, year);
		Font_Test(tempset,tempErr,symbol);
		checkself();  //自检
					
		/*init time0*/
	  Timer_Init();
  
//NVIC_SetPriority(TMR0_IRQn, 1);	
//NVIC_SetPriority(EINT1_IRQn, 0);	

	while(1)
		{

			delay_ms(1000);
			printf("\n\n\n");
		}

}





