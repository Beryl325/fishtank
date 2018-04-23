/* Includes ------------------------------------------------------------------*/
#include <GUI.h>
#include <stdio.h>
#include <M051Series.h>
#include <Lcd_Driver.h>
#include <delay.h>
#include <demo.h>
#include <DS18B20.h>

/******************************************************************************/
///欢迎界面
/******************************************************************************/
void welcome(void)
{
	
	Lcd_Clear(GREEN1);
	
	Gui_DrawFont_C(18,50,BLACK,GREEN1,90);
	Gui_DrawFont_C(34,50,BLACK,GREEN1,91);
	Gui_DrawFont_C(50,50,BLACK,GREEN1,92);
	Gui_DrawFont_C(66,50,BLACK,GREEN1,93);
	Gui_DrawFont_C(82,50,BLACK,GREEN1,94);
	Gui_DrawFont_C(98,50,BLACK,GREEN1,95);
	
	Gui_DrawFont_C(10,80,BLACK,GREEN1,96);
	Gui_DrawFont_C(26,80,BLACK,GREEN1,97);
	Gui_DrawFont_C(42,80,BLACK,GREEN1,98);
	Gui_DrawFont_C(58,80,BLACK,GREEN1,99);
	Gui_DrawFont_C(74,80,BLACK,GREEN1,100);
	Gui_DrawFont_C(90,80,BLACK,GREEN1,101);
	Gui_DrawFont_C(106,80,BLACK,GREEN1,102);
	
	Gui_DrawFont_S(34,110,BLACK,GREEN1,13);
	Gui_DrawFont_S(50,110,BLACK,GREEN1,2);
	Gui_DrawFont_S(58,110,BLACK,GREEN1,10);
	Gui_DrawFont_S(66,110,BLACK,GREEN1,2);
	Gui_DrawFont_S(74,110,BLACK,GREEN1,10);
	Gui_DrawFont_S(82,110,BLACK,GREEN1,5);

}
/******************************************************************************/
///时间界面
/******************************************************************************/
void time_now(unsigned char sec,unsigned char min,unsigned char hour,unsigned char day,unsigned char date,unsigned char month,unsigned char year)
{
	
	unsigned char x[6];
	Lcd_Clear(GREEN1);
	Gui_DrawFont_S(20,20,BLACK,GREEN1,2);
	Gui_DrawFont_S(28,20,BLACK,GREEN1,0);
		//年份
	x[0]=year/10;
	x[1]=year%10;
	Gui_DrawFont_S(36,20,BLACK,GREEN1,x[0]);
	Gui_DrawFont_S(44,20,BLACK,GREEN1,x[1]);
	Gui_DrawFont_S(52,20,BLACK,GREEN1,11);
		//日期
	x[0]=month/10;
	x[1]=month%10;
	Gui_DrawFont_S(60,20,BLACK,GREEN1,x[0]);
	Gui_DrawFont_S(68,20,BLACK,GREEN1,x[1]);
	Gui_DrawFont_S(76,20,BLACK,GREEN1,11);
	x[2]=date/10;
	x[3]=date%10;
	Gui_DrawFont_S(84,20,BLACK,GREEN1,x[2]);
	Gui_DrawFont_S(92,20,BLACK,GREEN1,x[3]);
		//时间
	x[0]=hour/10;
	x[1]=hour%10;
	x[2]=min/10;
	x[3]=min%10;
	x[4]=sec/10;
	x[5]=sec%10;
	Gui_DrawFont_S(30,50,BLACK,GREEN1,x[0]);
	Gui_DrawFont_S(38,50,BLACK,GREEN1,x[1]);
	Gui_DrawFont_S(46,50,BLACK,GREEN1,12);
	Gui_DrawFont_S(54,50,BLACK,GREEN1,x[2]);
	Gui_DrawFont_S(62,50,BLACK,GREEN1,x[3]);
	Gui_DrawFont_S(70,50,BLACK,GREEN1,12);
	Gui_DrawFont_S(78,50,BLACK,GREEN1,x[4]);
	Gui_DrawFont_S(86,50,BLACK,GREEN1,x[5]);

}
///时间实时
/******************************************************************************/
void time_now1(unsigned char sec,unsigned char min,unsigned char hour,unsigned char day,unsigned char date,unsigned char month,unsigned char year)
{
	
	unsigned char x[6];
	Gui_DrawFont_S(20,20,BLACK,GREEN1,2);
	Gui_DrawFont_S(28,20,BLACK,GREEN1,0);
		//年份
	x[0]=year/10;
	x[1]=year%10;
	Gui_DrawFont_S(36,20,BLACK,GREEN1,x[0]);
	Gui_DrawFont_S(44,20,BLACK,GREEN1,x[1]);
	Gui_DrawFont_S(52,20,BLACK,GREEN1,11);
		//日期
	x[0]=month/10;
	x[1]=month%10;
	Gui_DrawFont_S(60,20,BLACK,GREEN1,x[0]);
	Gui_DrawFont_S(68,20,BLACK,GREEN1,x[1]);
	Gui_DrawFont_S(76,20,BLACK,GREEN1,11);	
	x[2]=date/10;
	x[3]=date%10;
	Gui_DrawFont_S(84,20,BLACK,GREEN1,x[2]);
	Gui_DrawFont_S(92,20,BLACK,GREEN1,x[3]);
		//时间
	x[0]=hour/10;
	x[1]=hour%10;
	x[2]=min/10;
	x[3]=min%10;
	x[4]=sec/10;
	x[5]=sec%10;
	Gui_DrawFont_S(30,50,BLACK,GREEN1,x[0]);
	Gui_DrawFont_S(38,50,BLACK,GREEN1,x[1]);
	Gui_DrawFont_S(46,50,BLACK,GREEN1,12);
	Gui_DrawFont_S(54,50,BLACK,GREEN1,x[2]);
	Gui_DrawFont_S(62,50,BLACK,GREEN1,x[3]);
	Gui_DrawFont_S(70,50,BLACK,GREEN1,12);
	Gui_DrawFont_S(78,50,BLACK,GREEN1,x[4]);
	Gui_DrawFont_S(86,50,BLACK,GREEN1,x[5]);

}
  
/******************************************************************************/
///温度界面
/******************************************************************************/	
float Font_Test(float tempset,float temperr,unsigned char symbol)
{
	
	int temp,i,k,result1;
	float result,re;
	char x[3],set[3];
	result1=tempset*10;
	for(i=0;i<3;i++)
	{
		set[i]=result1/100;
		k=result1%100;
		result1=k*10;
	}
	
	temp=read_temp_ds18b20();
	result=(temp&0x07ff);
		
	result=(temp&0x07ff)*0.0625;
	if(symbol==0)
		re=result+temperr;
	else
		re=result-temperr;
	
//	printf("\nresult:%f\n",result);

	result=result*10+0.5;
//	printf("\nresult:%f\n",result);
	if(symbol==0)
		result=result+temperr*10;
	else
		result=result-temperr*10;
//	printf("\nresult2:%f\n",result);
	result1=result;
//		printf("\nresult1:%d\n",result1);
	for(i=0;i<3;i++)
	{
		x[i]=result1/100;
		k=result1%100;
		result1=k*10;
	}

//当前	
	Gui_DrawFont_C(10,80,BLACK,GREEN1,0);
	Gui_DrawFont_C(26,80,BLACK,GREEN1,1);
	Gui_DrawFont_C(42,80,BLACK,GREEN1,11);
	//显示当前温度
	Gui_DrawFont_S(58,80,BLUE,GREEN1,x[0]);
	Gui_DrawFont_S(66,80,BLUE,GREEN1,x[1]);
	Gui_DrawFont_S(74,80,BLUE,GREEN1,10);
	Gui_DrawFont_S(82,80,BLUE,GREEN1,x[2]);	
	Gui_DrawFont_C(96,80,BLACK,GREEN1,10);
//设定
	Gui_DrawFont_C(10,110,BLACK,GREEN1,2);
	Gui_DrawFont_C(26,110,BLACK,GREEN1,3);
	Gui_DrawFont_C(42,110,BLACK,GREEN1,11);
	//设定温度
	Gui_DrawFont_S(58,110,BLUE,GREEN1,set[0]);
	Gui_DrawFont_S(66,110,BLUE,GREEN1,set[1]);
	Gui_DrawFont_S(74,110,BLUE,GREEN1,10);
	Gui_DrawFont_S(82,110,BLUE,GREEN1,set[2]);
	Gui_DrawFont_C(96,110,BLACK,GREEN1,10);
	//状态
	Gui_DrawFont_C(10,140,BLACK,GREEN1,4);
	Gui_DrawFont_C(26,140,BLACK,GREEN1,5);
	Gui_DrawFont_C(42,140,BLACK,GREEN1,11);
	
	return re;
}
/****************************************************************************************/
///显示当前状态，加热 过滤
/******************************************************************************************/
void hoting(void)
{
		Gui_DrawFont_C(50,140,RED,GREEN1,62);
	  Gui_DrawFont_C(66,140,RED,GREEN1,9);
	  Gui_DrawFont_C(90,140,BLACK,GREEN1,6);
	  Gui_DrawFont_C(106,140,BLACK,GREEN1,7);
}
/****************************************************************************************/
///显示当前状态，制冷  过滤
/******************************************************************************************/
void colding(void)
{
	Gui_DrawFont_C(50,140,BLUE,GREEN1,8);
	Gui_DrawFont_C(66,140,BLUE,GREEN1,57);
	Gui_DrawFont_C(90,140,BLACK,GREEN1,6);
	Gui_DrawFont_C(106,140,BLACK,GREEN1,7);
}
/****************************************************************************************/
///显示当前状态，恒温 过滤
/******************************************************************************************/
void normal(void)
{
	Gui_DrawFont_C(50,140,BLACK,GREEN1,63);
	Gui_DrawFont_C(66,140,BLACK,GREEN1,44);
	Gui_DrawFont_C(90,140,BLACK,GREEN1,6);
	Gui_DrawFont_C(106,140,BLACK,GREEN1,7);
}
/****************************************************************************************/
///显示当前状态，进水故障，请手动清洗回水口滤网或回水泵
/******************************************************************************************/
void unnormal(void)
{
	Gui_DrawFont_C(50,140,RED,GREEN1,76);
	Gui_DrawFont_C(66,140,RED,GREEN1,67);
	Gui_DrawFont_C(90,140,RED,GREEN1,77);
	Gui_DrawFont_C(106,140,RED,GREEN1,78);
	
/*	Lcd_Clear(GREEN1);
	Gui_DrawFont_C(30,50,RED,GREEN1,76);
	Gui_DrawFont_C(46,50,RED,GREEN1,67);
	Gui_DrawFont_C(62,50,RED,GREEN1,77);
	Gui_DrawFont_C(78,50,RED,GREEN1,78);
	
	Gui_DrawFont_C(10,80,RED,GREEN1,86);
	Gui_DrawFont_C(26,80,RED,GREEN1,79);
	Gui_DrawFont_C(42,80,RED,GREEN1,32);
	Gui_DrawFont_C(58,80,RED,GREEN1,80);
	Gui_DrawFont_C(74,80,RED,GREEN1,81);
	Gui_DrawFont_C(90,80,RED,GREEN1,46);
	Gui_DrawFont_C(106,80,RED,GREEN1,67);
	
	Gui_DrawFont_C(10,110,RED,GREEN1,82);
	Gui_DrawFont_C(26,110,RED,GREEN1,7);
	Gui_DrawFont_C(42,110,RED,GREEN1,83);
	Gui_DrawFont_C(58,110,RED,GREEN1,84);
	Gui_DrawFont_C(74,110,RED,GREEN1,46);
	Gui_DrawFont_C(90,110,RED,GREEN1,67);
	Gui_DrawFont_C(106,110,RED,GREEN1,85);
*/
}
/****************************************************************************************/
///显示当前状态，停止 换水
/******************************************************************************************/
void stop(void)
{
	Gui_DrawFont_C(50,140,BLACK,GREEN1,68);
	Gui_DrawFont_C(66,140,BLACK,GREEN1,87);
	Gui_DrawFont_C(90,140,BLACK,GREEN1,88);
	Gui_DrawFont_C(106,140,BLACK,GREEN1,89);
}
/****************************************************************************************/
///显示当前温度
/******************************************************************************************/
float temp_dq(float temperr,unsigned char symbol)
{
		int temp,i,k,result1;
	  float result,re;
	  char x[3];
		temp=read_temp_ds18b20();      //读ds18b20
		result=(temp&0x07ff)*0.0625;
//		 printf("\nresult:%f\n",result);
	if(symbol==0)
	{re=result+temperr;}
	else
	{re=result-temperr;}
	  result=result*10+0.5;
		if(symbol==0)
			result=result+temperr*10;
		else
			result=result-temperr*10;
	  result1=result;	
//		printf("\nresult1:%d\n",result1);
	for(i=0;i<3;i++)
	{
		x[i]=result1/100;
		k=result1%100;
		result1=k*10;
//		printf("\nx:%d\n",x[i]);
	}
	//显示当前温度
	Gui_DrawFont_S(58,80,BLUE,GREEN1,x[0]);
	Gui_DrawFont_S(66,80,BLUE,GREEN1,x[1]);
	Gui_DrawFont_S(74,80,BLUE,GREEN1,10);
	Gui_DrawFont_S(82,80,BLUE,GREEN1,x[2]);	
	return re;
}

/****************************************************************************************/
///菜单首页
/******************************************************************************************/
void menu(void)
{
  	Lcd_Clear(GREEN1);
  //菜单
	Gui_DrawFont_C(10,20,BLACK,GREEN1,12);
	Gui_DrawFont_C(26,20,BLACK,GREEN1,13);
	Gui_DrawFont_C(42,20,BLACK,GREEN1,11);
	
	//工作模式
	Gui_DrawFont_C(10,50,BLACK,GREEN,14);
	Gui_DrawFont_C(26,50,BLACK,GREEN,15);
	Gui_DrawFont_C(42,50,BLACK,GREEN,16);
	Gui_DrawFont_C(58,50,BLACK,GREEN,17);
	//定时设置
	Gui_DrawFont_C(10,80,BLACK,GREEN1,18);
	Gui_DrawFont_C(26,80,BLACK,GREEN1,19);
	Gui_DrawFont_C(42,80,BLACK,GREEN1,2);
	Gui_DrawFont_C(58,80,BLACK,GREEN1,50);
	//系统设置
	Gui_DrawFont_C(10,110,BLACK,GREEN1,20);
	Gui_DrawFont_C(26,110,BLACK,GREEN1,21);
	Gui_DrawFont_C(42,110,BLACK,GREEN1,2);
	Gui_DrawFont_C(58,110,BLACK,GREEN1,50);
	//返回
	Gui_DrawFont_C(10,140,BLACK,GREEN1,22);
	Gui_DrawFont_C(26,140,BLACK,GREEN1,23);

}
/****************************************************************************************/
///菜单首页,工作
/******************************************************************************************/
void menu_0(void)
{
	
	//工作模式
	Gui_DrawFont_C(10,50,BLACK,GREEN,14);
	Gui_DrawFont_C(26,50,BLACK,GREEN,15);
	Gui_DrawFont_C(42,50,BLACK,GREEN,16);
	Gui_DrawFont_C(58,50,BLACK,GREEN,17);
	//定时设置
	Gui_DrawFont_C(10,80,BLACK,GREEN1,18);
	Gui_DrawFont_C(26,80,BLACK,GREEN1,19);
	Gui_DrawFont_C(42,80,BLACK,GREEN1,2);
	Gui_DrawFont_C(58,80,BLACK,GREEN1,50);



}
/****************************************************************************************/
///菜单首页,定时
/******************************************************************************************/
void menu_1(void)
{
	
	//工作模式
	Gui_DrawFont_C(10,50,BLACK,GREEN1,14);
	Gui_DrawFont_C(26,50,BLACK,GREEN1,15);
	Gui_DrawFont_C(42,50,BLACK,GREEN1,16);
	Gui_DrawFont_C(58,50,BLACK,GREEN1,17);
	//定时设置
	Gui_DrawFont_C(10,80,BLACK,GREEN,18);
	Gui_DrawFont_C(26,80,BLACK,GREEN,19);
	Gui_DrawFont_C(42,80,BLACK,GREEN,2);
	Gui_DrawFont_C(58,80,BLACK,GREEN,50);
	//系统设置
	Gui_DrawFont_C(10,110,BLACK,GREEN1,20);
	Gui_DrawFont_C(26,110,BLACK,GREEN1,21);
	Gui_DrawFont_C(42,110,BLACK,GREEN1,2);
	Gui_DrawFont_C(58,110,BLACK,GREEN1,50);


}
/****************************************************************************************/
///菜单首页,系统
/******************************************************************************************/
void menu_2(void)
{
	

	//定时设置
	Gui_DrawFont_C(10,80,BLACK,GREEN1,18);
	Gui_DrawFont_C(26,80,BLACK,GREEN1,19);
	Gui_DrawFont_C(42,80,BLACK,GREEN1,2);
	Gui_DrawFont_C(58,80,BLACK,GREEN1,50);
	//系统设置
	Gui_DrawFont_C(10,110,BLACK,GREEN,20);
	Gui_DrawFont_C(26,110,BLACK,GREEN,21);
	Gui_DrawFont_C(42,110,BLACK,GREEN,2);
	Gui_DrawFont_C(58,110,BLACK,GREEN,50);

	//返回
	Gui_DrawFont_C(10,140,BLACK,GREEN1,22);
	Gui_DrawFont_C(26,140,BLACK,GREEN1,23);

}
/****************************************************************************************/
///菜单首页,返回
/******************************************************************************************/
void menu_3(void)
{

	//系统设置
	Gui_DrawFont_C(10,110,BLACK,GREEN1,20);
	Gui_DrawFont_C(26,110,BLACK,GREEN1,21);
	Gui_DrawFont_C(42,110,BLACK,GREEN1,2);
	Gui_DrawFont_C(58,110,BLACK,GREEN1,50);

	//返回
	Gui_DrawFont_C(10,140,BLACK,GREEN,22);
	Gui_DrawFont_C(26,140,BLACK,GREEN,23);

}
/****************************************************************************************/
///工作模式页
/******************************************************************************************/
void menu1(void)
{
  	Lcd_Clear(GREEN1);
  //工作模式
	Gui_DrawFont_C(10,20,BLACK,GREEN1,14);
	Gui_DrawFont_C(26,20,BLACK,GREEN1,15);
	Gui_DrawFont_C(42,20,BLACK,GREEN1,16);
	Gui_DrawFont_C(58,20,BLACK,GREEN1,17);
	Gui_DrawFont_C(74,20,BLACK,GREEN1,11);
	
	//自动
	Gui_DrawFont_C(10,50,BLACK,GREEN,24);
	Gui_DrawFont_C(26,50,BLACK,GREEN,25);

	//制热
	Gui_DrawFont_C(10,80,BLACK,GREEN1,8);
	Gui_DrawFont_C(26,80,BLACK,GREEN1,9);
	
	//制冷
	Gui_DrawFont_C(10,110,BLACK,GREEN1,8);
	Gui_DrawFont_C(26,110,BLACK,GREEN1,51);

}
/****************************************************************************************/
///工作模式页,自动
/******************************************************************************************/
void menu1_0(void)
{
	
	//自动
	Gui_DrawFont_C(10,50,BLACK,GREEN,24);
	Gui_DrawFont_C(26,50,BLACK,GREEN,25);

	//制热
	Gui_DrawFont_C(10,80,BLACK,GREEN1,8);
	Gui_DrawFont_C(26,80,BLACK,GREEN1,9);
	


}
/****************************************************************************************/
///工作模式页,制热
/******************************************************************************************/
void menu1_1(void)
{

	//自动
	Gui_DrawFont_C(10,50,BLACK,GREEN1,24);
	Gui_DrawFont_C(26,50,BLACK,GREEN1,25);

	//制热
	Gui_DrawFont_C(10,80,BLACK,GREEN,8);
	Gui_DrawFont_C(26,80,BLACK,GREEN,9);
	
	//制冷
	Gui_DrawFont_C(10,110,BLACK,GREEN1,8);
	Gui_DrawFont_C(26,110,BLACK,GREEN1,51);

}
/****************************************************************************************/
///工作模式页,制冷
/******************************************************************************************/
void menu1_2(void)
{


	//制热
	Gui_DrawFont_C(10,80,BLACK,GREEN1,8);
	Gui_DrawFont_C(26,80,BLACK,GREEN1,9);
	
	//制冷
	Gui_DrawFont_C(10,110,BLACK,GREEN,8);
	Gui_DrawFont_C(26,110,BLACK,GREEN,51);

}

/****************************************************************************************/
///时间设置首页
/******************************************************************************************/
void menu2(void)
{
  	Lcd_Clear(GREEN1);
  //时间设置
	Gui_DrawFont_C(10,10,BLACK,GREEN1,35);
	Gui_DrawFont_C(26,10,BLACK,GREEN1,36);
	Gui_DrawFont_C(42,10,BLACK,GREEN1,2);
	Gui_DrawFont_C(58,10,BLACK,GREEN1,50);
	Gui_DrawFont_C(74,10,BLACK,GREEN1,11);
	
	//第一组
	Gui_DrawFont_C(10,40,BLACK,GREEN,26);
	Gui_DrawFont_C(26,40,BLACK,GREEN,27);
	Gui_DrawFont_C(42,40,BLACK,GREEN,30);

	//第二组
	Gui_DrawFont_C(10,70,BLACK,GREEN1,26);
	Gui_DrawFont_C(26,70,BLACK,GREEN1,28);
	Gui_DrawFont_C(42,70,BLACK,GREEN1,30);
	
	//第三组
	Gui_DrawFont_C(10,100,BLACK,GREEN1,26);
	Gui_DrawFont_C(26,100,BLACK,GREEN1,29);
	Gui_DrawFont_C(42,100,BLACK,GREEN1,30);
	
	//返回
	Gui_DrawFont_C(10,130,BLACK,GREEN1,22);
	Gui_DrawFont_C(26,130,BLACK,GREEN1,23);
}
/****************************************************************************************/
///时间设置,第一组
/******************************************************************************************/
void menu2_0(void)
{
	//第一组
	Gui_DrawFont_C(10,40,BLACK,GREEN,26);
	Gui_DrawFont_C(26,40,BLACK,GREEN,27);
	Gui_DrawFont_C(42,40,BLACK,GREEN,30);

	//第二组
	Gui_DrawFont_C(10,70,BLACK,GREEN1,26);
	Gui_DrawFont_C(26,70,BLACK,GREEN1,28);
	Gui_DrawFont_C(42,70,BLACK,GREEN1,30);
	

}
/****************************************************************************************/
///时间设置,第二组
/******************************************************************************************/
void menu2_1(void)
{
	//第一组
	Gui_DrawFont_C(10,40,BLACK,GREEN1,26);
	Gui_DrawFont_C(26,40,BLACK,GREEN1,27);
	Gui_DrawFont_C(42,40,BLACK,GREEN1,30);

	//第二组
	Gui_DrawFont_C(10,70,BLACK,GREEN,26);
	Gui_DrawFont_C(26,70,BLACK,GREEN,28);
	Gui_DrawFont_C(42,70,BLACK,GREEN,30);
	
	//第三组
	Gui_DrawFont_C(10,100,BLACK,GREEN1,26);
	Gui_DrawFont_C(26,100,BLACK,GREEN1,29);
	Gui_DrawFont_C(42,100,BLACK,GREEN1,30);
	

}
/****************************************************************************************/
///时间设置,第三组
/******************************************************************************************/
void menu2_2(void)
{

	//第二组
	Gui_DrawFont_C(10,70,BLACK,GREEN1,26);
	Gui_DrawFont_C(26,70,BLACK,GREEN1,28);
	Gui_DrawFont_C(42,70,BLACK,GREEN1,30);
	
	//第三组
	Gui_DrawFont_C(10,100,BLACK,GREEN,26);
	Gui_DrawFont_C(26,100,BLACK,GREEN,29);
	Gui_DrawFont_C(42,100,BLACK,GREEN,30);
	
	//返回
	Gui_DrawFont_C(10,130,BLACK,GREEN1,22);
	Gui_DrawFont_C(26,130,BLACK,GREEN1,23);
}
/****************************************************************************************/
///时间设置,返回
/******************************************************************************************/
void menu2_3(void)
{
	
	//第三组
	Gui_DrawFont_C(10,100,BLACK,GREEN1,26);
	Gui_DrawFont_C(26,100,BLACK,GREEN1,29);
	Gui_DrawFont_C(42,100,BLACK,GREEN1,30);
	
	//返回
	Gui_DrawFont_C(10,130,BLACK,GREEN,22);
	Gui_DrawFont_C(26,130,BLACK,GREEN,23);
}

/****************************************************************************************/
///第一组设置首页
/******************************************************************************************/
void menu21(unsigned char valid)
{
  	Lcd_Clear(GREEN1);
  //第一组
	Gui_DrawFont_C(10,20,BLACK,GREEN1,26);
	Gui_DrawFont_C(26,20,BLACK,GREEN1,27);
	Gui_DrawFont_C(42,20,BLACK,GREEN1,30);
	Gui_DrawFont_C(58,20,BLACK,GREEN1,11);
	
	//启动时间
	Gui_DrawFont_C(10,50,BLACK,GREEN,31);
	Gui_DrawFont_C(26,50,BLACK,GREEN,32);
	Gui_DrawFont_C(42,50,BLACK,GREEN,35);
	Gui_DrawFont_C(58,50,BLACK,GREEN,36);

	//关闭时间
	Gui_DrawFont_C(10,80,BLACK,GREEN1,33);
	Gui_DrawFont_C(26,80,BLACK,GREEN1,34);
	Gui_DrawFont_C(42,80,BLACK,GREEN1,35);
	Gui_DrawFont_C(58,80,BLACK,GREEN1,36);	
	
	//无效
	if(valid==0)
	{
	   Gui_DrawFont_C(10,110,BLACK,GREEN1,38);
	   Gui_DrawFont_C(26,110,BLACK,GREEN1,39);
	}
	else{
	   Gui_DrawFont_C(10,110,BLACK,GREEN1,37);//有效
	   Gui_DrawFont_C(26,110,BLACK,GREEN1,39);	
	}

	//返回
	Gui_DrawFont_C(10,140,BLACK,GREEN1,22);
	Gui_DrawFont_C(26,140,BLACK,GREEN1,23);
}
/****************************************************************************************/
///第一组设置首页,启动时间
/******************************************************************************************/
void menu21_0()
{	
	//启动时间
	Gui_DrawFont_C(10,50,BLACK,GREEN,31);
	Gui_DrawFont_C(26,50,BLACK,GREEN,32);
	Gui_DrawFont_C(42,50,BLACK,GREEN,35);
	Gui_DrawFont_C(58,50,BLACK,GREEN,36);

	//关闭时间
	Gui_DrawFont_C(10,80,BLACK,GREEN1,33);
	Gui_DrawFont_C(26,80,BLACK,GREEN1,34);
	Gui_DrawFont_C(42,80,BLACK,GREEN1,35);
	Gui_DrawFont_C(58,80,BLACK,GREEN1,36);	
	

}
/****************************************************************************************/
///第一组设置首页,关闭时间
/******************************************************************************************/
void menu21_1(unsigned char valid)
{	
	//启动时间
	Gui_DrawFont_C(10,50,BLACK,GREEN1,31);
	Gui_DrawFont_C(26,50,BLACK,GREEN1,32);
	Gui_DrawFont_C(42,50,BLACK,GREEN1,35);
	Gui_DrawFont_C(58,50,BLACK,GREEN1,36);

	//关闭时间
	Gui_DrawFont_C(10,80,BLACK,GREEN,33);
	Gui_DrawFont_C(26,80,BLACK,GREEN,34);
	Gui_DrawFont_C(42,80,BLACK,GREEN,35);
	Gui_DrawFont_C(58,80,BLACK,GREEN,36);	
	
	//无效
	if(valid==0)
	{
	   Gui_DrawFont_C(10,110,BLACK,GREEN1,38);
	   Gui_DrawFont_C(26,110,BLACK,GREEN1,39);
	}
	else{
	   Gui_DrawFont_C(10,110,BLACK,GREEN1,37);//有效
	   Gui_DrawFont_C(26,110,BLACK,GREEN1,39);	
	}
	

}
/****************************************************************************************/
///第一组设置首页,//有效//无效
/******************************************************************************************/
void menu21_2(unsigned char valid)
{	

	//关闭时间
	Gui_DrawFont_C(10,80,BLACK,GREEN1,33);
	Gui_DrawFont_C(26,80,BLACK,GREEN1,34);
	Gui_DrawFont_C(42,80,BLACK,GREEN1,35);
	Gui_DrawFont_C(58,80,BLACK,GREEN1,36);	
	
	//无效
	if(valid==0)
	{
	   Gui_DrawFont_C(10,110,BLACK,GREEN,38);
	   Gui_DrawFont_C(26,110,BLACK,GREEN,39);
	}
	else{
	   Gui_DrawFont_C(10,110,BLACK,GREEN,37);//有效
	   Gui_DrawFont_C(26,110,BLACK,GREEN,39);	
	}
	
	//返回
	Gui_DrawFont_C(10,140,BLACK,GREEN1,22);
	Gui_DrawFont_C(26,140,BLACK,GREEN1,23);
}
/****************************************************************************************/
///第一组设置首页,//有效
/******************************************************************************************/
void menu21_21(unsigned char valid)
{	
	//无效
	if(valid==0)
	{
	   Gui_DrawFont_C(10,110,BLACK,GRAY0,38);
	   Gui_DrawFont_C(26,110,BLACK,GRAY0,39);
	}
	else{
	   Gui_DrawFont_C(10,110,BLACK,GRAY0,37);//有效
	   Gui_DrawFont_C(26,110,BLACK,GRAY0,39);	
	}	


}
/****************************************************************************************/
///第一组设置首页,//无效
/******************************************************************************************/
void menu21_22(void)
{	
	
	
	//有效//无效
	Gui_DrawFont_C(10,110,BLACK,GRAY0,38);
	Gui_DrawFont_C(26,110,BLACK,GRAY0,39);
	
	//返回
	Gui_DrawFont_C(10,140,BLACK,GREEN1,22);
	Gui_DrawFont_C(26,140,BLACK,GREEN1,23);
}
/****************************************************************************************/
///第一组设置首页,//返回
/******************************************************************************************/
void menu21_3(unsigned char valid)
{	
	
	//无效
	if(valid==0)
	{
	   Gui_DrawFont_C(10,110,BLACK,GREEN1,38);
	   Gui_DrawFont_C(26,110,BLACK,GREEN1,39);
	}
	else{
	   Gui_DrawFont_C(10,110,BLACK,GREEN1,37);//有效
	   Gui_DrawFont_C(26,110,BLACK,GREEN1,39);	
	}
	
	//返回
	Gui_DrawFont_C(10,140,BLACK,GREEN,22);
	Gui_DrawFont_C(26,140,BLACK,GREEN,23);
}
/****************************************************************************************/
///启动时间首页
/******************************************************************************************/
void menu211(unsigned char sec,unsigned char min,unsigned char hour)
{
	unsigned char x[2];
  	Lcd_Clear(GREEN1);
   
	//启动时间
	Gui_DrawFont_C(10,20,BLACK,GREEN1,31);
	Gui_DrawFont_C(26,20,BLACK,GREEN1,32);
	Gui_DrawFont_C(42,20,BLACK,GREEN1,35);
	Gui_DrawFont_C(58,20,BLACK,GREEN1,36);

	//时
	x[0]=hour/10;
	x[1]=hour%10;
	Gui_DrawFont_C(10,50,BLACK,GREEN,19);
	Gui_DrawFont_C(26,50,BLACK,GREEN,11);
	Gui_DrawFont_S(42,50,BLACK,GREEN1,x[0]);
	Gui_DrawFont_S(50,50,BLACK,GREEN1,x[1]);	
	
	//分
	x[0]=min/10;
	x[1]=min%10;
	Gui_DrawFont_C(10,80,BLACK,GREEN1,64);
	Gui_DrawFont_C(26,80,BLACK,GREEN1,11);
	Gui_DrawFont_S(42,80,BLACK,GREEN1,x[0]);
	Gui_DrawFont_S(50,80,BLACK,GREEN1,x[1]);
		//秒
	x[0]=sec/10;
	x[1]=sec%10;
	Gui_DrawFont_C(10,110,BLACK,GREEN1,65);
	Gui_DrawFont_C(26,110,BLACK,GREEN1,11);
	Gui_DrawFont_S(42,110,BLACK,GREEN1,x[0]);
	Gui_DrawFont_S(50,110,BLACK,GREEN1,x[1]);
	//返回
	Gui_DrawFont_C(10,140,BLACK,GREEN1,22);
	Gui_DrawFont_C(26,140,BLACK,GREEN1,23);
}
/****************************************************************************************/
///关闭时间首页
/******************************************************************************************/
void menu212(unsigned char sec,unsigned char min,unsigned char hour)
{
		unsigned char x[2];
  	Lcd_Clear(GREEN1);

	//关闭时间
	Gui_DrawFont_C(10,20,BLACK,GREEN1,33);
	Gui_DrawFont_C(26,20,BLACK,GREEN1,34);
	Gui_DrawFont_C(42,20,BLACK,GREEN1,35);
	Gui_DrawFont_C(58,20,BLACK,GREEN1,36);
	//时
	x[0]=hour/10;
	x[1]=hour%10;
	Gui_DrawFont_C(10,50,BLACK,GREEN,19);
	Gui_DrawFont_C(26,50,BLACK,GREEN,11);
	Gui_DrawFont_S(42,50,BLACK,GREEN1,x[0]);
	Gui_DrawFont_S(50,50,BLACK,GREEN1,x[1]);	
	
	//分
	x[0]=min/10;
	x[1]=min%10;
	Gui_DrawFont_C(10,80,BLACK,GREEN1,64);
	Gui_DrawFont_C(26,80,BLACK,GREEN1,11);
	Gui_DrawFont_S(42,80,BLACK,GREEN1,x[0]);
	Gui_DrawFont_S(50,80,BLACK,GREEN1,x[1]);
		//秒
	x[0]=sec/10;
	x[1]=sec%10;
	Gui_DrawFont_C(10,110,BLACK,GREEN1,65);
	Gui_DrawFont_C(26,110,BLACK,GREEN1,11);
	Gui_DrawFont_S(42,110,BLACK,GREEN1,x[0]);
	Gui_DrawFont_S(50,110,BLACK,GREEN1,x[1]);
	//返回
	Gui_DrawFont_C(10,140,BLACK,GREEN1,22);
	Gui_DrawFont_C(26,140,BLACK,GREEN1,23);
}
/****************************************************************************************/
///启动时间,时1
/******************************************************************************************/
void menu211_0(unsigned char sec,unsigned char min,unsigned char hour)
{
	unsigned char x[2];
	//时
	x[0]=hour/10;
	x[1]=hour%10;
	Gui_DrawFont_C(10,50,BLACK,GREEN,19);
	Gui_DrawFont_C(26,50,BLACK,GREEN,11);
	Gui_DrawFont_S(42,50,BLACK,GREEN1,x[0]);
	Gui_DrawFont_S(50,50,BLACK,GREEN1,x[1]);	
	
	//分
	x[0]=min/10;
	x[1]=min%10;
	Gui_DrawFont_C(10,80,BLACK,GREEN1,64);
	Gui_DrawFont_C(26,80,BLACK,GREEN1,11);
	Gui_DrawFont_S(42,80,BLACK,GREEN1,x[0]);
	Gui_DrawFont_S(50,80,BLACK,GREEN1,x[1]);
		//秒
	x[0]=sec/10;
	x[1]=sec%10;
	Gui_DrawFont_C(10,110,BLACK,GREEN1,65);
	Gui_DrawFont_C(26,110,BLACK,GREEN1,11);
	Gui_DrawFont_S(42,110,BLACK,GREEN1,x[0]);
	Gui_DrawFont_S(50,110,BLACK,GREEN1,x[1]);
	//返回
	Gui_DrawFont_C(10,140,BLACK,GREEN1,22);
	Gui_DrawFont_C(26,140,BLACK,GREEN1,23);	
}
/****************************************************************************************/
///启动时间,时2
/******************************************************************************************/
void menu211_1(unsigned char sec,unsigned char min,unsigned char hour)
{

	unsigned char x[2];
	//时
	x[0]=hour/10;
	x[1]=hour%10;
	Gui_DrawFont_C(10,50,BLACK,GREEN1,19);
	Gui_DrawFont_C(26,50,BLACK,GREEN1,11);
	Gui_DrawFont_S(42,50,BLACK,GREEN,x[0]);
	Gui_DrawFont_S(50,50,BLACK,GREEN,x[1]);	
		
}
/****************************************************************************************/
///启动时间,分1
/******************************************************************************************/
void menu211_2(unsigned char sec,unsigned char min,unsigned char hour)
{
	unsigned char x[2];
	//时
	x[0]=hour/10;
	x[1]=hour%10;
	Gui_DrawFont_C(10,50,BLACK,GREEN1,19);
	Gui_DrawFont_C(26,50,BLACK,GREEN1,11);
	Gui_DrawFont_S(42,50,BLACK,GREEN1,x[0]);
	Gui_DrawFont_S(50,50,BLACK,GREEN1,x[1]);	
	
	//分
	x[0]=min/10;
	x[1]=min%10;
	Gui_DrawFont_C(10,80,BLACK,GREEN,64);
	Gui_DrawFont_C(26,80,BLACK,GREEN,11);
	Gui_DrawFont_S(42,80,BLACK,GREEN1,x[0]);
	Gui_DrawFont_S(50,80,BLACK,GREEN1,x[1]);
		//秒
	x[0]=sec/10;
	x[1]=sec%10;
	Gui_DrawFont_C(10,110,BLACK,GREEN1,65);
	Gui_DrawFont_C(26,110,BLACK,GREEN1,11);
	Gui_DrawFont_S(42,110,BLACK,GREEN1,x[0]);
	Gui_DrawFont_S(50,110,BLACK,GREEN1,x[1]);
	//返回
	Gui_DrawFont_C(10,140,BLACK,GREEN1,22);
	Gui_DrawFont_C(26,140,BLACK,GREEN1,23);	
}
/****************************************************************************************/
///启动时间,分2
/******************************************************************************************/
void menu211_3(unsigned char sec,unsigned char min,unsigned char hour)
{
	unsigned char x[2];
	
	
	//分
	x[0]=min/10;
	x[1]=min%10;
	Gui_DrawFont_C(10,80,BLACK,GREEN1,64);
	Gui_DrawFont_C(26,80,BLACK,GREEN1,11);
	Gui_DrawFont_S(42,80,BLACK,GREEN,x[0]);
	Gui_DrawFont_S(50,80,BLACK,GREEN,x[1]);
	
}
/****************************************************************************************/
///启动时间,秒1
/******************************************************************************************/
void menu211_4(unsigned char sec,unsigned char min,unsigned char hour)
{
	unsigned char x[2];
	//时
	x[0]=hour/10;
	x[1]=hour%10;
	Gui_DrawFont_C(10,50,BLACK,GREEN1,19);
	Gui_DrawFont_C(26,50,BLACK,GREEN1,11);
	Gui_DrawFont_S(42,50,BLACK,GREEN1,x[0]);
	Gui_DrawFont_S(50,50,BLACK,GREEN1,x[1]);	
	
	//分
	x[0]=min/10;
	x[1]=min%10;
	Gui_DrawFont_C(10,80,BLACK,GREEN1,64);
	Gui_DrawFont_C(26,80,BLACK,GREEN1,11);
	Gui_DrawFont_S(42,80,BLACK,GREEN1,x[0]);
	Gui_DrawFont_S(50,80,BLACK,GREEN1,x[1]);
		//秒
	x[0]=sec/10;
	x[1]=sec%10;
	Gui_DrawFont_C(10,110,BLACK,GREEN,65);
	Gui_DrawFont_C(26,110,BLACK,GREEN,11);
	Gui_DrawFont_S(42,110,BLACK,GREEN1,x[0]);
	Gui_DrawFont_S(50,110,BLACK,GREEN1,x[1]);
	//返回
	Gui_DrawFont_C(10,140,BLACK,GREEN1,22);
	Gui_DrawFont_C(26,140,BLACK,GREEN1,23);	
}
/****************************************************************************************/
///启动时间,秒2
/******************************************************************************************/
void menu211_5(unsigned char sec,unsigned char min,unsigned char hour)
{
	unsigned char x[2];

		//秒
	x[0]=sec/10;
	x[1]=sec%10;
	Gui_DrawFont_C(10,110,BLACK,GREEN1,65);
	Gui_DrawFont_C(26,110,BLACK,GREEN1,11);
	Gui_DrawFont_S(42,110,BLACK,GREEN,x[0]);
	Gui_DrawFont_S(50,110,BLACK,GREEN,x[1]);
	
}
/****************************************************************************************/
///启动时间,返回
/******************************************************************************************/
void menu211_6(unsigned char sec,unsigned char min,unsigned char hour)
{
	unsigned char x[2];
	//时
	x[0]=hour/10;
	x[1]=hour%10;
	Gui_DrawFont_C(10,50,BLACK,GREEN1,19);
	Gui_DrawFont_C(26,50,BLACK,GREEN1,11);
	Gui_DrawFont_S(42,50,BLACK,GREEN1,x[0]);
	Gui_DrawFont_S(50,50,BLACK,GREEN1,x[1]);	
	
	//分
	x[0]=min/10;
	x[1]=min%10;
	Gui_DrawFont_C(10,80,BLACK,GREEN1,64);
	Gui_DrawFont_C(26,80,BLACK,GREEN1,11);
	Gui_DrawFont_S(42,80,BLACK,GREEN1,x[0]);
	Gui_DrawFont_S(50,80,BLACK,GREEN1,x[1]);
		//秒
	x[0]=sec/10;
	x[1]=sec%10;
	Gui_DrawFont_C(10,110,BLACK,GREEN1,65);
	Gui_DrawFont_C(26,110,BLACK,GREEN1,11);
	Gui_DrawFont_S(42,110,BLACK,GREEN1,x[0]);
	Gui_DrawFont_S(50,110,BLACK,GREEN1,x[1]);
	//返回
	Gui_DrawFont_C(10,140,BLACK,GREEN,22);
	Gui_DrawFont_C(26,140,BLACK,GREEN,23);	
}
/****************************************************************************************/
///第二组设置首页
/******************************************************************************************/
void menu22(unsigned char valid)     ///第二组
{
	 Lcd_Clear(GREEN1);
  //第二组
	Gui_DrawFont_C(10,20,BLACK,GREEN1,26);
	Gui_DrawFont_C(26,20,BLACK,GREEN1,28);
	Gui_DrawFont_C(42,20,BLACK,GREEN1,30);
	Gui_DrawFont_C(58,20,BLACK,GREEN1,11);
	
	//启动时间
	Gui_DrawFont_C(10,50,BLACK,GREEN,31);
	Gui_DrawFont_C(26,50,BLACK,GREEN,32);
	Gui_DrawFont_C(42,50,BLACK,GREEN,35);
	Gui_DrawFont_C(58,50,BLACK,GREEN,36);

	//关闭时间
	Gui_DrawFont_C(10,80,BLACK,GREEN1,33);
	Gui_DrawFont_C(26,80,BLACK,GREEN1,34);
	Gui_DrawFont_C(42,80,BLACK,GREEN1,35);
	Gui_DrawFont_C(58,80,BLACK,GREEN1,36);	
	
	//无效
	if(valid==0)
	{
	   Gui_DrawFont_C(10,110,BLACK,GREEN1,38);
	   Gui_DrawFont_C(26,110,BLACK,GREEN1,39);
	}
	else{
	   Gui_DrawFont_C(10,110,BLACK,GREEN1,37);//有效
	   Gui_DrawFont_C(26,110,BLACK,GREEN1,39);	
	}
	
	//返回
	Gui_DrawFont_C(10,140,BLACK,GREEN1,22);
	Gui_DrawFont_C(26,140,BLACK,GREEN1,23);
}

/****************************************************************************************/
///第三组设置首页
/******************************************************************************************/
void menu23(unsigned char valid)     ///第三组
{
	Lcd_Clear(GREEN1);
  //第三组
	Gui_DrawFont_C(10,20,BLACK,GREEN1,26);
	Gui_DrawFont_C(26,20,BLACK,GREEN1,29);
	Gui_DrawFont_C(42,20,BLACK,GREEN1,30);
	Gui_DrawFont_C(58,20,BLACK,GREEN1,11);
	
	//启动时间
	Gui_DrawFont_C(10,50,BLACK,GREEN,31);
	Gui_DrawFont_C(26,50,BLACK,GREEN,32);
	Gui_DrawFont_C(42,50,BLACK,GREEN,35);
	Gui_DrawFont_C(58,50,BLACK,GREEN,36);

	//关闭时间
	Gui_DrawFont_C(10,80,BLACK,GREEN1,33);
	Gui_DrawFont_C(26,80,BLACK,GREEN1,34);
	Gui_DrawFont_C(42,80,BLACK,GREEN1,35);
	Gui_DrawFont_C(58,80,BLACK,GREEN1,36);	
	
	//无效
	if(valid==0)
	{
	   Gui_DrawFont_C(10,110,BLACK,GREEN1,38);
	   Gui_DrawFont_C(26,110,BLACK,GREEN1,39);
	}
	else{
	   Gui_DrawFont_C(10,110,BLACK,GREEN1,37);//有效
	   Gui_DrawFont_C(26,110,BLACK,GREEN1,39);	
	}
	
	//返回
	Gui_DrawFont_C(10,140,BLACK,GREEN1,22);
	Gui_DrawFont_C(26,140,BLACK,GREEN1,23);
}
/****************************************************************************************/
///系统设置首页
/******************************************************************************************/
void menu3(void)
{
  	Lcd_Clear(GREEN1);
  //系统设置
	Gui_DrawFont_C(10,10,BLACK,GREEN1,20);
	Gui_DrawFont_C(26,10,BLACK,GREEN1,22);
	Gui_DrawFont_C(42,10,BLACK,GREEN1,2);
	Gui_DrawFont_C(58,10,BLACK,GREEN1,50);
	Gui_DrawFont_C(74,10,BLACK,GREEN1,11);
	
	//时间设置
	Gui_DrawFont_C(10,35,BLACK,GREEN,35);
	Gui_DrawFont_C(26,35,BLACK,GREEN,36);
	Gui_DrawFont_C(42,35,BLACK,GREEN,2);
	Gui_DrawFont_C(58,35,BLACK,GREEN,50);

	//风扇转速
	Gui_DrawFont_C(10,60,BLACK,GREEN1,40);
	Gui_DrawFont_C(26,60,BLACK,GREEN1,41);
	Gui_DrawFont_C(42,60,BLACK,GREEN1,42);
	Gui_DrawFont_C(58,60,BLACK,GREEN1,43);
	
	//温差校准
	Gui_DrawFont_C(10,85,BLACK,GREEN1,44);
	Gui_DrawFont_C(26,85,BLACK,GREEN1,47);
	Gui_DrawFont_C(42,85,BLACK,GREEN1,48);
	Gui_DrawFont_C(58,85,BLACK,GREEN1,49);
	
	//温度设置
	Gui_DrawFont_C(10,110,BLACK,GREEN1,44);
	Gui_DrawFont_C(26,110,BLACK,GREEN1,45);
	Gui_DrawFont_C(42,110,BLACK,GREEN1,2);
	Gui_DrawFont_C(58,110,BLACK,GREEN1,50);
	
		//返回
	Gui_DrawFont_C(10,135,BLACK,GREEN1,22);
	Gui_DrawFont_C(26,135,BLACK,GREEN1,23);

}
/****************************************************************************************/
///系统设置,时间
/******************************************************************************************/
void menu3_0(void)
{
	
	//时间设置
	Gui_DrawFont_C(10,35,BLACK,GREEN,35);
	Gui_DrawFont_C(26,35,BLACK,GREEN,36);
	Gui_DrawFont_C(42,35,BLACK,GREEN,2);
	Gui_DrawFont_C(58,35,BLACK,GREEN,50);

	//风扇转速
	Gui_DrawFont_C(10,60,BLACK,GREEN1,40);
	Gui_DrawFont_C(26,60,BLACK,GREEN1,41);
	Gui_DrawFont_C(42,60,BLACK,GREEN1,42);
	Gui_DrawFont_C(58,60,BLACK,GREEN1,43);
	

}
/****************************************************************************************/
///系统设置，风扇
/******************************************************************************************/
void menu3_1(void)
{

	//时间设置
	Gui_DrawFont_C(10,35,BLACK,GREEN1,35);
	Gui_DrawFont_C(26,35,BLACK,GREEN1,36);
	Gui_DrawFont_C(42,35,BLACK,GREEN1,2);
	Gui_DrawFont_C(58,35,BLACK,GREEN1,50);

	//风扇转速
	Gui_DrawFont_C(10,60,BLACK,GREEN,40);
	Gui_DrawFont_C(26,60,BLACK,GREEN,41);
	Gui_DrawFont_C(42,60,BLACK,GREEN,42);
	Gui_DrawFont_C(58,60,BLACK,GREEN,43);
	
	//温差校准
	Gui_DrawFont_C(10,85,BLACK,GREEN1,44);
	Gui_DrawFont_C(26,85,BLACK,GREEN1,47);
	Gui_DrawFont_C(42,85,BLACK,GREEN1,48);
	Gui_DrawFont_C(58,85,BLACK,GREEN1,49);

}
/****************************************************************************************/
///系统设置,温差
/******************************************************************************************/
void menu3_2(void)
{


	//风扇转速
	Gui_DrawFont_C(10,60,BLACK,GREEN1,40);
	Gui_DrawFont_C(26,60,BLACK,GREEN1,41);
	Gui_DrawFont_C(42,60,BLACK,GREEN1,42);
	Gui_DrawFont_C(58,60,BLACK,GREEN1,43);
	
	//温差校准
	Gui_DrawFont_C(10,85,BLACK,GREEN,44);
	Gui_DrawFont_C(26,85,BLACK,GREEN,47);
	Gui_DrawFont_C(42,85,BLACK,GREEN,48);
	Gui_DrawFont_C(58,85,BLACK,GREEN,49);
	
	//温度设置
	Gui_DrawFont_C(10,110,BLACK,GREEN1,44);
	Gui_DrawFont_C(26,110,BLACK,GREEN1,45);
	Gui_DrawFont_C(42,110,BLACK,GREEN1,2);
	Gui_DrawFont_C(58,110,BLACK,GREEN1,50);


}
/****************************************************************************************/
///系统设置,回差
/******************************************************************************************/
void menu3_3(void)
{	
	//温差校准
	Gui_DrawFont_C(10,85,BLACK,GREEN1,44);
	Gui_DrawFont_C(26,85,BLACK,GREEN1,47);
	Gui_DrawFont_C(42,85,BLACK,GREEN1,48);
	Gui_DrawFont_C(58,85,BLACK,GREEN1,49);
	
	//温度回差
	Gui_DrawFont_C(10,110,BLACK,GREEN,44);
	Gui_DrawFont_C(26,110,BLACK,GREEN,45);
	Gui_DrawFont_C(42,110,BLACK,GREEN,2);
	Gui_DrawFont_C(58,110,BLACK,GREEN,50);
	
		//返回
	Gui_DrawFont_C(10,135,BLACK,GREEN1,22);
	Gui_DrawFont_C(26,135,BLACK,GREEN1,23);

}
/****************************************************************************************/
///系统设置，返回
/******************************************************************************************/
void menu3_4(void)
{	
	//温度设置
	Gui_DrawFont_C(10,110,BLACK,GREEN1,44);
	Gui_DrawFont_C(26,110,BLACK,GREEN1,45);
	Gui_DrawFont_C(42,110,BLACK,GREEN1,2);
	Gui_DrawFont_C(58,110,BLACK,GREEN1,50);
	
		//返回
	Gui_DrawFont_C(10,135,BLACK,GREEN,22);
	Gui_DrawFont_C(26,135,BLACK,GREEN,23);

}

/****************************************************************************************/
///系统设置->时间设置首页
/******************************************************************************************/
void menu31(unsigned char sec,unsigned char min,unsigned char hour,unsigned char day,unsigned char date,unsigned char month,unsigned char year)
{
  unsigned char x[6];
	Lcd_Clear(GREEN1);
		//时间设置

	Gui_DrawFont_C(10,20,BLACK,GREEN1,35);
	Gui_DrawFont_C(26,20,BLACK,GREEN1,36);
	Gui_DrawFont_C(42,20,BLACK,GREEN1,2);
	Gui_DrawFont_C(58,20,BLACK,GREEN1,50);
	
	//年份
	x[0]=year/10;
	x[1]=year%10;
	Gui_DrawFont_C(10,50,BLACK,GREEN,52);	
	Gui_DrawFont_C(26,50,BLACK,GREEN,55);
	Gui_DrawFont_C(42,50,BLACK,GREEN,11);
	Gui_DrawFont_S(58,50,BLACK,GREEN1,2);
	Gui_DrawFont_S(66,50,BLACK,GREEN1,0);
	Gui_DrawFont_S(74,50,BLACK,GREEN1,x[0]);
	Gui_DrawFont_S(82,50,BLACK,GREEN1,x[1]);
	
	//日期
	x[0]=month/10;
	x[1]=month%10;
	x[2]=date/10;
	x[3]=date%10;
	Gui_DrawFont_C(10,80,BLACK,GREEN1,54);	
	Gui_DrawFont_C(26,80,BLACK,GREEN1,56);
	Gui_DrawFont_C(42,80,BLACK,GREEN1,11);
	Gui_DrawFont_S(58,80,BLACK,GREEN1,x[0]);
	Gui_DrawFont_S(66,80,BLACK,GREEN1,x[1]);
	Gui_DrawFont_C(74,80,BLACK,GREEN1,53);
	Gui_DrawFont_S(90,80,BLACK,GREEN1,x[2]);
	Gui_DrawFont_S(98,80,BLACK,GREEN1,x[3]);
	Gui_DrawFont_C(106,80,BLACK,GREEN1,54);
	
	//时间
	x[0]=hour/10;
	x[1]=hour%10;
	x[2]=min/10;
	x[3]=min%10;
	x[4]=sec/10;
	x[5]=sec%10;	
	Gui_DrawFont_C(10,110,BLACK,GREEN1,35);	
	Gui_DrawFont_C(26,110,BLACK,GREEN1,36);
	Gui_DrawFont_C(42,110,BLACK,GREEN1,11);
	Gui_DrawFont_S(58,110,BLACK,GREEN1,x[0]);
	Gui_DrawFont_S(66,110,BLACK,GREEN1,x[1]);
	Gui_DrawFont_C(74,110,BLACK,GREEN1,11);
	Gui_DrawFont_S(82,110,BLACK,GREEN1,x[2]);
	Gui_DrawFont_S(90,110,BLACK,GREEN1,x[3]);
	Gui_DrawFont_C(98,110,BLACK,GREEN1,11);
	Gui_DrawFont_S(106,110,BLACK,GREEN1,x[4]);
	Gui_DrawFont_S(114,110,BLACK,GREEN1,x[5]);

			//返回
	Gui_DrawFont_C(10,140,BLACK,GREEN1,22);
	Gui_DrawFont_C(26,140,BLACK,GREEN1,23);
}
/****************************************************************************************/
///系统设置->时间设置,年份1
/******************************************************************************************/
void menu31_0(unsigned char sec,unsigned char min,unsigned char hour,unsigned char day,unsigned char date,unsigned char month,unsigned char year)
{
  unsigned char x[6];
	
	//年份
	x[0]=year/10;
	x[1]=year%10;
	Gui_DrawFont_C(10,50,BLACK,GREEN,52);	
	Gui_DrawFont_C(26,50,BLACK,GREEN,55);
	Gui_DrawFont_C(42,50,BLACK,GREEN,11);
	Gui_DrawFont_S(58,50,BLACK,GREEN1,2);
	Gui_DrawFont_S(66,50,BLACK,GREEN1,0);
	Gui_DrawFont_S(74,50,BLACK,GREEN1,x[0]);
	Gui_DrawFont_S(82,50,BLACK,GREEN1,x[1]);
	
	//日期
	x[0]=month/10;
	x[1]=month%10;
	x[2]=date/10;
	x[3]=date%10;
	Gui_DrawFont_C(10,80,BLACK,GREEN1,54);	
	Gui_DrawFont_C(26,80,BLACK,GREEN1,56);
	Gui_DrawFont_C(42,80,BLACK,GREEN1,11);
	Gui_DrawFont_S(58,80,BLACK,GREEN1,x[0]);
	Gui_DrawFont_S(66,80,BLACK,GREEN1,x[1]);
	Gui_DrawFont_C(74,80,BLACK,GREEN1,53);
	Gui_DrawFont_S(90,80,BLACK,GREEN1,x[2]);
	Gui_DrawFont_S(98,80,BLACK,GREEN1,x[3]);
	Gui_DrawFont_C(106,80,BLACK,GREEN1,54);
	
	//时间
	x[0]=hour/10;
	x[1]=hour%10;
	x[2]=min/10;
	x[3]=min%10;
	x[4]=sec/10;
	x[5]=sec%10;	

}
/****************************************************************************************/
///系统设置->时间设置,年份2
/******************************************************************************************/
void menu31_1(unsigned char year)
{
  unsigned char x[6];
	
	//年份
	x[0]=year/10;
	x[1]=year%10;
	Gui_DrawFont_C(10,50,BLACK,GREEN1,52);	
	Gui_DrawFont_C(26,50,BLACK,GREEN1,55);
	Gui_DrawFont_C(42,50,BLACK,GREEN1,11);
	Gui_DrawFont_S(58,50,BLACK,GREEN1,2);
	Gui_DrawFont_S(66,50,BLACK,GREEN1,0);
	Gui_DrawFont_S(74,50,BLACK,GREEN,x[0]);
	Gui_DrawFont_S(82,50,BLACK,GREEN,x[1]);

}
/****************************************************************************************/
///系统设置->时间设置,日期1
/******************************************************************************************/
void menu31_2(unsigned char sec,unsigned char min,unsigned char hour,unsigned char day,unsigned char date,unsigned char month,unsigned char year)
{
  unsigned char x[6];
	
	//年份
	x[0]=year/10;
	x[1]=year%10;
	Gui_DrawFont_C(10,50,BLACK,GREEN1,52);	
	Gui_DrawFont_C(26,50,BLACK,GREEN1,55);
	Gui_DrawFont_C(42,50,BLACK,GREEN1,11);
	Gui_DrawFont_S(58,50,BLACK,GREEN1,2);
	Gui_DrawFont_S(66,50,BLACK,GREEN1,0);
	Gui_DrawFont_S(74,50,BLACK,GREEN1,x[0]);
	Gui_DrawFont_S(82,50,BLACK,GREEN1,x[1]);
	
	//日期
	x[0]=month/10;
	x[1]=month%10;
	x[2]=date/10;
	x[3]=date%10;
	Gui_DrawFont_C(10,80,BLACK,GREEN,54);	
	Gui_DrawFont_C(26,80,BLACK,GREEN,56);
	Gui_DrawFont_C(42,80,BLACK,GREEN,11);
	Gui_DrawFont_S(58,80,BLACK,GREEN1,x[0]);
	Gui_DrawFont_S(66,80,BLACK,GREEN1,x[1]);
	Gui_DrawFont_C(74,80,BLACK,GREEN1,53);
	Gui_DrawFont_S(90,80,BLACK,GREEN1,x[2]);
	Gui_DrawFont_S(98,80,BLACK,GREEN1,x[3]);
	Gui_DrawFont_C(106,80,BLACK,GREEN1,54);
	
	//时间
	x[0]=hour/10;
	x[1]=hour%10;
	x[2]=min/10;
	x[3]=min%10;
	x[4]=sec/10;
	x[5]=sec%10;	
	Gui_DrawFont_C(10,110,BLACK,GREEN1,35);	
	Gui_DrawFont_C(26,110,BLACK,GREEN1,36);
	Gui_DrawFont_C(42,110,BLACK,GREEN1,11);
	Gui_DrawFont_S(58,110,BLACK,GREEN1,x[0]);
	Gui_DrawFont_S(66,110,BLACK,GREEN1,x[1]);
	Gui_DrawFont_C(74,110,BLACK,GREEN1,11);
	Gui_DrawFont_S(82,110,BLACK,GREEN1,x[2]);
	Gui_DrawFont_S(90,110,BLACK,GREEN1,x[3]);
	Gui_DrawFont_C(98,110,BLACK,GREEN1,11);
	Gui_DrawFont_S(106,110,BLACK,GREEN1,x[4]);
	Gui_DrawFont_S(114,110,BLACK,GREEN1,x[5]);


}
/****************************************************************************************/
///系统设置->时间设置,日期，月
/******************************************************************************************/
void menu31_3(unsigned char date,unsigned char month)
{
  unsigned char x[6];
	
	//日期
	x[0]=month/10;
	x[1]=month%10;
	x[2]=date/10;
	x[3]=date%10;
	Gui_DrawFont_C(10,80,BLACK,GREEN1,54);	
	Gui_DrawFont_C(26,80,BLACK,GREEN1,56);
	Gui_DrawFont_C(42,80,BLACK,GREEN1,11);
	Gui_DrawFont_S(58,80,BLACK,GREEN,x[0]);
	Gui_DrawFont_S(66,80,BLACK,GREEN,x[1]);
	Gui_DrawFont_C(74,80,BLACK,GREEN1,53);
	Gui_DrawFont_S(90,80,BLACK,GREEN1,x[2]);
	Gui_DrawFont_S(98,80,BLACK,GREEN1,x[3]);
	Gui_DrawFont_C(106,80,BLACK,GREEN1,54);

}
/****************************************************************************************/
///系统设置->时间设置,日期，日
/******************************************************************************************/
void menu31_4(unsigned char date,unsigned char month)
{
  unsigned char x[6];
	
	//日期
	x[0]=month/10;
	x[1]=month%10;
	x[2]=date/10;
	x[3]=date%10;
	Gui_DrawFont_C(10,80,BLACK,GREEN1,54);	
	Gui_DrawFont_C(26,80,BLACK,GREEN1,56);
	Gui_DrawFont_C(42,80,BLACK,GREEN1,11);
	Gui_DrawFont_S(58,80,BLACK,GREEN1,x[0]);
	Gui_DrawFont_S(66,80,BLACK,GREEN1,x[1]);
	Gui_DrawFont_C(74,80,BLACK,GREEN1,53);
	Gui_DrawFont_S(90,80,BLACK,GREEN,x[2]);
	Gui_DrawFont_S(98,80,BLACK,GREEN,x[3]);
	Gui_DrawFont_C(106,80,BLACK,GREEN1,54);

}
/****************************************************************************************/
///系统设置->时间设置,时间1
/******************************************************************************************/
void menu31_5(unsigned char sec,unsigned char min,unsigned char hour,unsigned char day,unsigned char date,unsigned char month,unsigned char year)
{
  unsigned char x[6];
	
	//年份
	x[0]=year/10;
	x[1]=year%10;

	
	//日期
	x[0]=month/10;
	x[1]=month%10;
	x[2]=date/10;
	x[3]=date%10;
	Gui_DrawFont_C(10,80,BLACK,GREEN1,54);	
	Gui_DrawFont_C(26,80,BLACK,GREEN1,56);
	Gui_DrawFont_C(42,80,BLACK,GREEN1,11);
	Gui_DrawFont_S(58,80,BLACK,GREEN1,x[0]);
	Gui_DrawFont_S(66,80,BLACK,GREEN1,x[1]);
	Gui_DrawFont_C(74,80,BLACK,GREEN1,53);
	Gui_DrawFont_S(90,80,BLACK,GREEN1,x[2]);
	Gui_DrawFont_S(98,80,BLACK,GREEN1,x[3]);
	Gui_DrawFont_C(106,80,BLACK,GREEN1,54);
	
	//时间
	x[0]=hour/10;
	x[1]=hour%10;
	x[2]=min/10;
	x[3]=min%10;
	x[4]=sec/10;
	x[5]=sec%10;	
	Gui_DrawFont_C(10,110,BLACK,GREEN,35);	
	Gui_DrawFont_C(26,110,BLACK,GREEN,36);
	Gui_DrawFont_C(42,110,BLACK,GREEN,11);
	Gui_DrawFont_S(58,110,BLACK,GREEN1,x[0]);
	Gui_DrawFont_S(66,110,BLACK,GREEN1,x[1]);
	Gui_DrawFont_C(74,110,BLACK,GREEN1,11);
	Gui_DrawFont_S(82,110,BLACK,GREEN1,x[2]);
	Gui_DrawFont_S(90,110,BLACK,GREEN1,x[3]);
	Gui_DrawFont_C(98,110,BLACK,GREEN1,11);
	Gui_DrawFont_S(106,110,BLACK,GREEN1,x[4]);
	Gui_DrawFont_S(114,110,BLACK,GREEN1,x[5]);

			//返回
	Gui_DrawFont_C(10,140,BLACK,GREEN1,22);
	Gui_DrawFont_C(26,140,BLACK,GREEN1,23);
}
/****************************************************************************************/
///系统设置->时间设置,时
/******************************************************************************************/
void menu31_6(unsigned char sec,unsigned char min,unsigned char hour)
{
  unsigned char x[6];
		
	//时间
	x[0]=hour/10;
	x[1]=hour%10;
	x[2]=min/10;
	x[3]=min%10;
	x[4]=sec/10;
	x[5]=sec%10;	
	Gui_DrawFont_C(10,110,BLACK,GREEN1,35);	
	Gui_DrawFont_C(26,110,BLACK,GREEN1,36);
	Gui_DrawFont_C(42,110,BLACK,GREEN1,11);
	Gui_DrawFont_S(58,110,BLACK,GREEN,x[0]);
	Gui_DrawFont_S(66,110,BLACK,GREEN,x[1]);
	Gui_DrawFont_C(74,110,BLACK,GREEN1,11);
	Gui_DrawFont_S(82,110,BLACK,GREEN1,x[2]);
	Gui_DrawFont_S(90,110,BLACK,GREEN1,x[3]);
	Gui_DrawFont_C(98,110,BLACK,GREEN1,11);
	Gui_DrawFont_S(106,110,BLACK,GREEN1,x[4]);
	Gui_DrawFont_S(114,110,BLACK,GREEN1,x[5]);


}
/****************************************************************************************/
///系统设置->时间设置,分
/******************************************************************************************/
void menu31_7(unsigned char sec,unsigned char min,unsigned char hour)
{
  unsigned char x[6];
		
	//时间
	x[0]=hour/10;
	x[1]=hour%10;
	x[2]=min/10;
	x[3]=min%10;
	x[4]=sec/10;
	x[5]=sec%10;	
	Gui_DrawFont_C(10,110,BLACK,GREEN1,35);	
	Gui_DrawFont_C(26,110,BLACK,GREEN1,36);
	Gui_DrawFont_C(42,110,BLACK,GREEN1,11);
	Gui_DrawFont_S(58,110,BLACK,GREEN1,x[0]);
	Gui_DrawFont_S(66,110,BLACK,GREEN1,x[1]);
	Gui_DrawFont_C(74,110,BLACK,GREEN1,11);
	Gui_DrawFont_S(82,110,BLACK,GREEN,x[2]);
	Gui_DrawFont_S(90,110,BLACK,GREEN,x[3]);
	Gui_DrawFont_C(98,110,BLACK,GREEN1,11);
	Gui_DrawFont_S(106,110,BLACK,GREEN1,x[4]);
	Gui_DrawFont_S(114,110,BLACK,GREEN1,x[5]);
}
/****************************************************************************************/
///系统设置->时间设置,秒
/******************************************************************************************/
void menu31_8(unsigned char sec,unsigned char min,unsigned char hour)
{
  unsigned char x[6];
		
	//时间
	x[0]=hour/10;
	x[1]=hour%10;
	x[2]=min/10;
	x[3]=min%10;
	x[4]=sec/10;
	x[5]=sec%10;	
	Gui_DrawFont_C(10,110,BLACK,GREEN1,35);	
	Gui_DrawFont_C(26,110,BLACK,GREEN1,36);
	Gui_DrawFont_C(42,110,BLACK,GREEN1,11);
	Gui_DrawFont_S(58,110,BLACK,GREEN1,x[0]);
	Gui_DrawFont_S(66,110,BLACK,GREEN1,x[1]);
	Gui_DrawFont_C(74,110,BLACK,GREEN1,11);
	Gui_DrawFont_S(82,110,BLACK,GREEN1,x[2]);
	Gui_DrawFont_S(90,110,BLACK,GREEN1,x[3]);
	Gui_DrawFont_C(98,110,BLACK,GREEN1,11);
	Gui_DrawFont_S(106,110,BLACK,GREEN,x[4]);
	Gui_DrawFont_S(114,110,BLACK,GREEN,x[5]);
}
/****************************************************************************************/
///系统设置->时间设置,返回
/******************************************************************************************/
void menu31_9(unsigned char sec,unsigned char min,unsigned char hour,unsigned char day,unsigned char date,unsigned char month,unsigned char year)
{
  unsigned char x[6];
	
	//年份
	x[0]=year/10;
	x[1]=year%10;

	
	//日期
	x[0]=month/10;
	x[1]=month%10;
	x[2]=date/10;
	x[3]=date%10;

	
	//时间
	x[0]=hour/10;
	x[1]=hour%10;
	x[2]=min/10;
	x[3]=min%10;
	x[4]=sec/10;
	x[5]=sec%10;	
	Gui_DrawFont_C(10,110,BLACK,GREEN1,35);	
	Gui_DrawFont_C(26,110,BLACK,GREEN1,36);
	Gui_DrawFont_C(42,110,BLACK,GREEN1,11);
	Gui_DrawFont_S(58,110,BLACK,GREEN1,x[0]);
	Gui_DrawFont_S(66,110,BLACK,GREEN1,x[1]);
	Gui_DrawFont_C(74,110,BLACK,GREEN1,11);
	Gui_DrawFont_S(82,110,BLACK,GREEN1,x[2]);
	Gui_DrawFont_S(90,110,BLACK,GREEN1,x[3]);
	Gui_DrawFont_C(98,110,BLACK,GREEN1,11);
	Gui_DrawFont_S(106,110,BLACK,GREEN1,x[4]);
	Gui_DrawFont_S(114,110,BLACK,GREEN1,x[5]);

			//返回
	Gui_DrawFont_C(10,140,BLACK,GREEN,22);
	Gui_DrawFont_C(26,140,BLACK,GREEN,23);
}
/****************************************************************************************/
///系统设置->风扇转速首页
/******************************************************************************************/
void menu32(void)
{
	Lcd_Clear(GREEN1);
   	//风扇转速
	Gui_DrawFont_C(10,15,BLACK,GREEN1,40);
	Gui_DrawFont_C(26,15,BLACK,GREEN1,41);
	Gui_DrawFont_C(42,15,BLACK,GREEN1,42);
	Gui_DrawFont_C(58,15,BLACK,GREEN1,43);
	   	//高档
	Gui_DrawFont_C(10,35,BLACK,GREEN,73);
	Gui_DrawFont_C(42,35,BLACK,GREEN,72);

	   	//中高档
	Gui_DrawFont_C(10,55,BLACK,GREEN1,74);
	Gui_DrawFont_C(26,55,BLACK,GREEN1,73);
	Gui_DrawFont_C(42,55,BLACK,GREEN1,72);

	   	//中档
	Gui_DrawFont_C(10,75,BLACK,GREEN1,74);
	Gui_DrawFont_C(42,75,BLACK,GREEN1,72);

		   	//中低档
	Gui_DrawFont_C(10,95,BLACK,GREEN1,74);
	Gui_DrawFont_C(26,95,BLACK,GREEN1,75);
	Gui_DrawFont_C(42,95,BLACK,GREEN1,72);

	   	//低档
	Gui_DrawFont_C(10,115,BLACK,GREEN1,75);
	Gui_DrawFont_C(42,115,BLACK,GREEN1,72);
}
/****************************************************************************************/
///系统设置->风扇转速,高档
/******************************************************************************************/
void menu32_0(void)
{
	   	//高档
	Gui_DrawFont_C(10,35,BLACK,GREEN,73);
	Gui_DrawFont_C(42,35,BLACK,GREEN,72);

	   	//中高档
	Gui_DrawFont_C(10,55,BLACK,GREEN1,74);
	Gui_DrawFont_C(26,55,BLACK,GREEN1,73);
	Gui_DrawFont_C(42,55,BLACK,GREEN1,72);

}
/****************************************************************************************/
///系统设置->风扇转速,中高档
/******************************************************************************************/
void menu32_1(void)
{
	   	//高档
	Gui_DrawFont_C(10,35,BLACK,GREEN1,73);
	Gui_DrawFont_C(42,35,BLACK,GREEN1,72);

	   	//中高档
	Gui_DrawFont_C(10,55,BLACK,GREEN,74);
	Gui_DrawFont_C(26,55,BLACK,GREEN,73);
	Gui_DrawFont_C(42,55,BLACK,GREEN,72);

	   	//中档
	Gui_DrawFont_C(10,75,BLACK,GREEN1,74);
	Gui_DrawFont_C(42,75,BLACK,GREEN1,72);
}
/****************************************************************************************/
///系统设置->风扇转速,中档
/******************************************************************************************/
void menu32_2(void)
{
	   	//中高档
	Gui_DrawFont_C(10,55,BLACK,GREEN1,74);
	Gui_DrawFont_C(26,55,BLACK,GREEN1,73);
	Gui_DrawFont_C(42,55,BLACK,GREEN1,72);

	   	//中档
	Gui_DrawFont_C(10,75,BLACK,GREEN,74);
	Gui_DrawFont_C(42,75,BLACK,GREEN,72);

		   	//中低档
	Gui_DrawFont_C(10,95,BLACK,GREEN1,74);
	Gui_DrawFont_C(26,95,BLACK,GREEN1,75);
	Gui_DrawFont_C(42,95,BLACK,GREEN1,72);

}
/****************************************************************************************/
///系统设置->风扇转速，中低档
/******************************************************************************************/
void menu32_3(void)
{
	   	//中档
	Gui_DrawFont_C(10,75,BLACK,GREEN1,74);
	Gui_DrawFont_C(42,75,BLACK,GREEN1,72);

		   	//中低档
	Gui_DrawFont_C(10,95,BLACK,GREEN,74);
	Gui_DrawFont_C(26,95,BLACK,GREEN,75);
	Gui_DrawFont_C(42,95,BLACK,GREEN,72);

	   	//低档
	Gui_DrawFont_C(10,115,BLACK,GREEN1,75);

	Gui_DrawFont_C(42,115,BLACK,GREEN1,72);
}
/****************************************************************************************/
///系统设置->风扇转速，低档
/******************************************************************************************/
void menu32_4(void)
{
		   	//中低档
	Gui_DrawFont_C(10,95,BLACK,GREEN1,74);
	Gui_DrawFont_C(26,95,BLACK,GREEN1,75);
	Gui_DrawFont_C(42,95,BLACK,GREEN1,72);

	   	//低档
	Gui_DrawFont_C(10,115,BLACK,GREEN,75);

	Gui_DrawFont_C(42,115,BLACK,GREEN,72);
}
/****************************************************************************************/
///系统设置->温差校准首页
/******************************************************************************************/
void menu33(float temperr,unsigned char sym)
{
	int temperr1,x[2];
	temperr1=temperr*10;
	x[0]=temperr1/10;
	x[1]=temperr1%10;
		Lcd_Clear(GREEN1);
	/////温差校准
	Gui_DrawFont_C(10,20,BLACK,GREEN1,44);
	Gui_DrawFont_C(26,20,BLACK,GREEN1,47);
	Gui_DrawFont_C(42,20,BLACK,GREEN1,48);
	Gui_DrawFont_C(58,20,BLACK,GREEN1,49);
	Gui_DrawFont_C(74,20,BLACK,GREEN1,11);
	////
	if(sym==0)
		Gui_DrawFont_S(14,60,BLUE,GREEN,14);
	else
		Gui_DrawFont_S(14,60,BLUE,GREEN,11);
	Gui_DrawFont_S(30,60,BLUE,GREEN1,x[0]);
	Gui_DrawFont_S(38,60,BLUE,GREEN1,10);
	Gui_DrawFont_S(46,60,BLUE,GREEN1,x[1]);
		//温度范围为-7~7
	Gui_DrawFont_S(5,110,RED,GREEN1,15);
	Gui_DrawFont_C(13,110,RED,GREEN1,44);
	Gui_DrawFont_C(29,110,RED,GREEN1,45);
	Gui_DrawFont_C(45,110,RED,GREEN1,58);
	Gui_DrawFont_C(61,110,RED,GREEN1,59);	
	Gui_DrawFont_S(77,110,RED,GREEN1,11);
	Gui_DrawFont_S(85,110,RED,GREEN1,7);
	Gui_DrawFont_S(93,110,RED,GREEN1,17);
	Gui_DrawFont_S(101,110,RED,GREEN1,7);
	Gui_DrawFont_S(109,110,RED,GREEN1,16);
}
/****************************************************************************************/
///系统设置->温差校准首页,符号
/******************************************************************************************/
void menu33_0(float temperr,unsigned char sym)
{
	int temperr1,x[2];
	temperr1=temperr*10;
	x[0]=temperr1/10;
	x[1]=temperr1%10;
	if(sym==0)
		Gui_DrawFont_S(14,60,BLUE,GREEN,14);
	else
		Gui_DrawFont_S(14,60,BLUE,GREEN,11);
		Gui_DrawFont_S(30,60,BLUE,GREEN1,x[0]);
	Gui_DrawFont_S(38,60,BLUE,GREEN1,10);
	Gui_DrawFont_S(46,60,BLUE,GREEN1,x[1]);
}
/****************************************************************************************/
///系统设置->温差校准首页,cha
/******************************************************************************************/
void menu33_1(float temperr,unsigned char sym)
{
	int temperr1,x[2];
	temperr1=temperr*10;
	x[0]=temperr1/10;
	x[1]=temperr1%10;

	if(sym==0)
		Gui_DrawFont_S(14,60,BLUE,GREEN1,14);
	else
		Gui_DrawFont_S(14,60,BLUE,GREEN1,11);
		Gui_DrawFont_S(30,60,BLUE,GREEN,x[0]);
	Gui_DrawFont_S(38,60,BLUE,GREEN,10);
	Gui_DrawFont_S(46,60,BLUE,GREEN,x[1]);
}

/****************************************************************************************/
///系统设置->温度设置首页
/******************************************************************************************/
void menu34(float tempset1,float tempdiff1)
{
	int x[2],y,z;
	z=tempset1;
	x[0]=z/10;
	x[1]=z%10;
	y=tempdiff1;
	Lcd_Clear(GREEN1);
	//温度设置：
	Gui_DrawFont_C(10,20,BLACK,GREEN1,44);
	Gui_DrawFont_C(26,20,BLACK,GREEN1,45);
	Gui_DrawFont_C(42,20,BLACK,GREEN1,2);
	Gui_DrawFont_C(58,20,BLACK,GREEN1,50);
	Gui_DrawFont_C(74,20,BLACK,GREEN1,11);
	//设定温度：
	Gui_DrawFont_C(10,50,BLACK,GREEN,2);
	Gui_DrawFont_C(26,50,BLACK,GREEN,3);
	Gui_DrawFont_C(42,50,BLACK,GREEN,44);
	Gui_DrawFont_C(58,50,BLACK,GREEN,45);
	Gui_DrawFont_C(74,50,BLACK,GREEN,11);
	Gui_DrawFont_S(90,50,BLUE,GREEN1,x[0]);
	Gui_DrawFont_S(98,50,BLUE,GREEN1,x[1]);
	Gui_DrawFont_C(106,50,BLACK,GREEN1,10);
	//温度回差
	Gui_DrawFont_C(10,80,BLACK,GREEN1,44);
	Gui_DrawFont_C(26,80,BLACK,GREEN1,45);
	Gui_DrawFont_C(42,80,BLACK,GREEN1,46);
	Gui_DrawFont_C(58,80,BLACK,GREEN1,47);
	Gui_DrawFont_C(74,80,BLACK,GREEN1,11);
	Gui_DrawFont_S(90,80,BLUE,GREEN1,y);
	Gui_DrawFont_C(106,80,BLACK,GREEN1,10);
	//返回
	Gui_DrawFont_C(10,110,BLACK,GREEN1,22);
	Gui_DrawFont_C(26,110,BLACK,GREEN1,23);
	//温度范围为15~25

}
/****************************************************************************************/
///系统设置->温度设置->设定温度
/******************************************************************************************/
void menu34_0(float tempset1,float tempdiff1)
{
	int x[2],y,z;
	z=tempset1;
	x[0]=z/10;
	x[1]=z%10;
	y=tempdiff1;
	//设定温度：
	Gui_DrawFont_C(10,50,BLACK,GREEN,2);
	Gui_DrawFont_C(26,50,BLACK,GREEN,3);
	Gui_DrawFont_C(42,50,BLACK,GREEN,44);
	Gui_DrawFont_C(58,50,BLACK,GREEN,45);
	Gui_DrawFont_C(74,50,BLACK,GREEN,11);
	Gui_DrawFont_S(90,50,BLUE,GREEN1,x[0]);
	Gui_DrawFont_S(98,50,BLUE,GREEN1,x[1]);
	Gui_DrawFont_C(106,50,BLACK,GREEN1,10);
	//温度回差
	Gui_DrawFont_C(10,80,BLACK,GREEN1,44);
	Gui_DrawFont_C(26,80,BLACK,GREEN1,45);
	Gui_DrawFont_C(42,80,BLACK,GREEN1,46);
	Gui_DrawFont_C(58,80,BLACK,GREEN1,47);
	Gui_DrawFont_C(74,80,BLACK,GREEN1,11);
	Gui_DrawFont_S(90,80,BLUE,GREEN1,y);
	Gui_DrawFont_C(106,80,BLACK,GREEN1,10);


}
/****************************************************************************************/
///系统设置->温度设置->温度回差
/******************************************************************************************/
void menu34_1(float tempset1,float tempdiff1)
{
	int x[2],y,z;
	z=tempset1;
	x[0]=z/10;
	x[1]=z%10;
	y=tempdiff1;
	//设定温度：
	Gui_DrawFont_C(10,50,BLACK,GREEN1,2);
	Gui_DrawFont_C(26,50,BLACK,GREEN1,3);
	Gui_DrawFont_C(42,50,BLACK,GREEN1,44);
	Gui_DrawFont_C(58,50,BLACK,GREEN1,45);
	Gui_DrawFont_C(74,50,BLACK,GREEN1,11);
	Gui_DrawFont_S(90,50,BLUE,GREEN1,x[0]);
	Gui_DrawFont_S(98,50,BLUE,GREEN1,x[1]);
	Gui_DrawFont_C(106,50,BLACK,GREEN1,10);
	//温度回差
	Gui_DrawFont_C(10,80,BLACK,GREEN,44);
	Gui_DrawFont_C(26,80,BLACK,GREEN,45);
	Gui_DrawFont_C(42,80,BLACK,GREEN,46);
	Gui_DrawFont_C(58,80,BLACK,GREEN,47);
	Gui_DrawFont_C(74,80,BLACK,GREEN,11);
	Gui_DrawFont_S(90,80,BLUE,GREEN1,y);
	Gui_DrawFont_C(106,80,BLACK,GREEN1,10);
	//返回
	Gui_DrawFont_C(10,110,BLACK,GREEN1,22);
	Gui_DrawFont_C(26,110,BLACK,GREEN1,23);

}
/****************************************************************************************/
///系统设置->温度设置->返回
/******************************************************************************************/
void menu34_2(float tempset1,float tempdiff1)
{
	int x[2],y,z;
	z=tempset1;
	x[0]=z/10;
	x[1]=z%10;
	y=tempdiff1;

	//温度回差
	Gui_DrawFont_C(10,80,BLACK,GREEN1,44);
	Gui_DrawFont_C(26,80,BLACK,GREEN1,45);
	Gui_DrawFont_C(42,80,BLACK,GREEN1,46);
	Gui_DrawFont_C(58,80,BLACK,GREEN1,47);
	Gui_DrawFont_C(74,80,BLACK,GREEN1,11);
	Gui_DrawFont_S(90,80,BLUE,GREEN1,y);
	Gui_DrawFont_C(106,80,BLACK,GREEN1,10);
	//返回
	Gui_DrawFont_C(10,110,BLACK,GREEN,22);
	Gui_DrawFont_C(26,110,BLACK,GREEN,23);

}
/****************************************************************************************/
///系统设置->温度设置->设定温度->温度
/******************************************************************************************/
void menu34_01(float tempset1,float tempdiff1)
{
	int x[2],y,z;
	z=tempset1;
	x[0]=z/10;
	x[1]=z%10;
	y=tempdiff1;
	//设定温度：
	Gui_DrawFont_C(10,50,BLACK,GREEN1,2);
	Gui_DrawFont_C(26,50,BLACK,GREEN1,3);
	Gui_DrawFont_C(42,50,BLACK,GREEN1,44);
	Gui_DrawFont_C(58,50,BLACK,GREEN1,45);
	Gui_DrawFont_C(74,50,BLACK,GREEN1,11);
	Gui_DrawFont_S(90,50,BLUE,GREEN,x[0]);
	Gui_DrawFont_S(98,50,BLUE,GREEN,x[1]);
	Gui_DrawFont_C(106,50,BLACK,GREEN1,10);


}
/****************************************************************************************/
///系统设置->温度设置->设定温度->回差
/******************************************************************************************/
void menu34_11(float tempset1,float tempdiff1)
{
	int x[2],y,z;
	z=tempset1;
	x[0]=z/10;
	x[1]=z%10;
	y=tempdiff1;

	//温度回差
	Gui_DrawFont_C(10,80,BLACK,GREEN1,44);
	Gui_DrawFont_C(26,80,BLACK,GREEN1,45);
	Gui_DrawFont_C(42,80,BLACK,GREEN1,46);
	Gui_DrawFont_C(58,80,BLACK,GREEN1,47);
	Gui_DrawFont_C(74,80,BLACK,GREEN1,11);
	Gui_DrawFont_S(90,80,BLUE,GREEN,y);
	Gui_DrawFont_C(106,80,BLACK,GREEN1,10);

}
