/* Includes ------------------------------------------------------------------*/
#include <GUI.h>
#include <stdio.h>
#include <M051Series.h>
#include <Lcd_Driver.h>
#include <delay.h>
#include <demo.h>
#include <DS18B20.h>

/******************************************************************************/
///��ӭ����
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
///ʱ�����
/******************************************************************************/
void time_now(unsigned char sec,unsigned char min,unsigned char hour,unsigned char day,unsigned char date,unsigned char month,unsigned char year)
{
	
	unsigned char x[6];
	Lcd_Clear(GREEN1);
	Gui_DrawFont_S(20,20,BLACK,GREEN1,2);
	Gui_DrawFont_S(28,20,BLACK,GREEN1,0);
		//���
	x[0]=year/10;
	x[1]=year%10;
	Gui_DrawFont_S(36,20,BLACK,GREEN1,x[0]);
	Gui_DrawFont_S(44,20,BLACK,GREEN1,x[1]);
	Gui_DrawFont_S(52,20,BLACK,GREEN1,11);
		//����
	x[0]=month/10;
	x[1]=month%10;
	Gui_DrawFont_S(60,20,BLACK,GREEN1,x[0]);
	Gui_DrawFont_S(68,20,BLACK,GREEN1,x[1]);
	Gui_DrawFont_S(76,20,BLACK,GREEN1,11);
	x[2]=date/10;
	x[3]=date%10;
	Gui_DrawFont_S(84,20,BLACK,GREEN1,x[2]);
	Gui_DrawFont_S(92,20,BLACK,GREEN1,x[3]);
		//ʱ��
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
///ʱ��ʵʱ
/******************************************************************************/
void time_now1(unsigned char sec,unsigned char min,unsigned char hour,unsigned char day,unsigned char date,unsigned char month,unsigned char year)
{
	
	unsigned char x[6];
	Gui_DrawFont_S(20,20,BLACK,GREEN1,2);
	Gui_DrawFont_S(28,20,BLACK,GREEN1,0);
		//���
	x[0]=year/10;
	x[1]=year%10;
	Gui_DrawFont_S(36,20,BLACK,GREEN1,x[0]);
	Gui_DrawFont_S(44,20,BLACK,GREEN1,x[1]);
	Gui_DrawFont_S(52,20,BLACK,GREEN1,11);
		//����
	x[0]=month/10;
	x[1]=month%10;
	Gui_DrawFont_S(60,20,BLACK,GREEN1,x[0]);
	Gui_DrawFont_S(68,20,BLACK,GREEN1,x[1]);
	Gui_DrawFont_S(76,20,BLACK,GREEN1,11);	
	x[2]=date/10;
	x[3]=date%10;
	Gui_DrawFont_S(84,20,BLACK,GREEN1,x[2]);
	Gui_DrawFont_S(92,20,BLACK,GREEN1,x[3]);
		//ʱ��
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
///�¶Ƚ���
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

//��ǰ	
	Gui_DrawFont_C(10,80,BLACK,GREEN1,0);
	Gui_DrawFont_C(26,80,BLACK,GREEN1,1);
	Gui_DrawFont_C(42,80,BLACK,GREEN1,11);
	//��ʾ��ǰ�¶�
	Gui_DrawFont_S(58,80,BLUE,GREEN1,x[0]);
	Gui_DrawFont_S(66,80,BLUE,GREEN1,x[1]);
	Gui_DrawFont_S(74,80,BLUE,GREEN1,10);
	Gui_DrawFont_S(82,80,BLUE,GREEN1,x[2]);	
	Gui_DrawFont_C(96,80,BLACK,GREEN1,10);
//�趨
	Gui_DrawFont_C(10,110,BLACK,GREEN1,2);
	Gui_DrawFont_C(26,110,BLACK,GREEN1,3);
	Gui_DrawFont_C(42,110,BLACK,GREEN1,11);
	//�趨�¶�
	Gui_DrawFont_S(58,110,BLUE,GREEN1,set[0]);
	Gui_DrawFont_S(66,110,BLUE,GREEN1,set[1]);
	Gui_DrawFont_S(74,110,BLUE,GREEN1,10);
	Gui_DrawFont_S(82,110,BLUE,GREEN1,set[2]);
	Gui_DrawFont_C(96,110,BLACK,GREEN1,10);
	//״̬
	Gui_DrawFont_C(10,140,BLACK,GREEN1,4);
	Gui_DrawFont_C(26,140,BLACK,GREEN1,5);
	Gui_DrawFont_C(42,140,BLACK,GREEN1,11);
	
	return re;
}
/****************************************************************************************/
///��ʾ��ǰ״̬������ ����
/******************************************************************************************/
void hoting(void)
{
		Gui_DrawFont_C(50,140,RED,GREEN1,62);
	  Gui_DrawFont_C(66,140,RED,GREEN1,9);
	  Gui_DrawFont_C(90,140,BLACK,GREEN1,6);
	  Gui_DrawFont_C(106,140,BLACK,GREEN1,7);
}
/****************************************************************************************/
///��ʾ��ǰ״̬������  ����
/******************************************************************************************/
void colding(void)
{
	Gui_DrawFont_C(50,140,BLUE,GREEN1,8);
	Gui_DrawFont_C(66,140,BLUE,GREEN1,57);
	Gui_DrawFont_C(90,140,BLACK,GREEN1,6);
	Gui_DrawFont_C(106,140,BLACK,GREEN1,7);
}
/****************************************************************************************/
///��ʾ��ǰ״̬������ ����
/******************************************************************************************/
void normal(void)
{
	Gui_DrawFont_C(50,140,BLACK,GREEN1,63);
	Gui_DrawFont_C(66,140,BLACK,GREEN1,44);
	Gui_DrawFont_C(90,140,BLACK,GREEN1,6);
	Gui_DrawFont_C(106,140,BLACK,GREEN1,7);
}
/****************************************************************************************/
///��ʾ��ǰ״̬����ˮ���ϣ����ֶ���ϴ��ˮ���������ˮ��
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
///��ʾ��ǰ״̬��ֹͣ ��ˮ
/******************************************************************************************/
void stop(void)
{
	Gui_DrawFont_C(50,140,BLACK,GREEN1,68);
	Gui_DrawFont_C(66,140,BLACK,GREEN1,87);
	Gui_DrawFont_C(90,140,BLACK,GREEN1,88);
	Gui_DrawFont_C(106,140,BLACK,GREEN1,89);
}
/****************************************************************************************/
///��ʾ��ǰ�¶�
/******************************************************************************************/
float temp_dq(float temperr,unsigned char symbol)
{
		int temp,i,k,result1;
	  float result,re;
	  char x[3];
		temp=read_temp_ds18b20();      //��ds18b20
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
	//��ʾ��ǰ�¶�
	Gui_DrawFont_S(58,80,BLUE,GREEN1,x[0]);
	Gui_DrawFont_S(66,80,BLUE,GREEN1,x[1]);
	Gui_DrawFont_S(74,80,BLUE,GREEN1,10);
	Gui_DrawFont_S(82,80,BLUE,GREEN1,x[2]);	
	return re;
}

/****************************************************************************************/
///�˵���ҳ
/******************************************************************************************/
void menu(void)
{
  	Lcd_Clear(GREEN1);
  //�˵�
	Gui_DrawFont_C(10,20,BLACK,GREEN1,12);
	Gui_DrawFont_C(26,20,BLACK,GREEN1,13);
	Gui_DrawFont_C(42,20,BLACK,GREEN1,11);
	
	//����ģʽ
	Gui_DrawFont_C(10,50,BLACK,GREEN,14);
	Gui_DrawFont_C(26,50,BLACK,GREEN,15);
	Gui_DrawFont_C(42,50,BLACK,GREEN,16);
	Gui_DrawFont_C(58,50,BLACK,GREEN,17);
	//��ʱ����
	Gui_DrawFont_C(10,80,BLACK,GREEN1,18);
	Gui_DrawFont_C(26,80,BLACK,GREEN1,19);
	Gui_DrawFont_C(42,80,BLACK,GREEN1,2);
	Gui_DrawFont_C(58,80,BLACK,GREEN1,50);
	//ϵͳ����
	Gui_DrawFont_C(10,110,BLACK,GREEN1,20);
	Gui_DrawFont_C(26,110,BLACK,GREEN1,21);
	Gui_DrawFont_C(42,110,BLACK,GREEN1,2);
	Gui_DrawFont_C(58,110,BLACK,GREEN1,50);
	//����
	Gui_DrawFont_C(10,140,BLACK,GREEN1,22);
	Gui_DrawFont_C(26,140,BLACK,GREEN1,23);

}
/****************************************************************************************/
///�˵���ҳ,����
/******************************************************************************************/
void menu_0(void)
{
	
	//����ģʽ
	Gui_DrawFont_C(10,50,BLACK,GREEN,14);
	Gui_DrawFont_C(26,50,BLACK,GREEN,15);
	Gui_DrawFont_C(42,50,BLACK,GREEN,16);
	Gui_DrawFont_C(58,50,BLACK,GREEN,17);
	//��ʱ����
	Gui_DrawFont_C(10,80,BLACK,GREEN1,18);
	Gui_DrawFont_C(26,80,BLACK,GREEN1,19);
	Gui_DrawFont_C(42,80,BLACK,GREEN1,2);
	Gui_DrawFont_C(58,80,BLACK,GREEN1,50);



}
/****************************************************************************************/
///�˵���ҳ,��ʱ
/******************************************************************************************/
void menu_1(void)
{
	
	//����ģʽ
	Gui_DrawFont_C(10,50,BLACK,GREEN1,14);
	Gui_DrawFont_C(26,50,BLACK,GREEN1,15);
	Gui_DrawFont_C(42,50,BLACK,GREEN1,16);
	Gui_DrawFont_C(58,50,BLACK,GREEN1,17);
	//��ʱ����
	Gui_DrawFont_C(10,80,BLACK,GREEN,18);
	Gui_DrawFont_C(26,80,BLACK,GREEN,19);
	Gui_DrawFont_C(42,80,BLACK,GREEN,2);
	Gui_DrawFont_C(58,80,BLACK,GREEN,50);
	//ϵͳ����
	Gui_DrawFont_C(10,110,BLACK,GREEN1,20);
	Gui_DrawFont_C(26,110,BLACK,GREEN1,21);
	Gui_DrawFont_C(42,110,BLACK,GREEN1,2);
	Gui_DrawFont_C(58,110,BLACK,GREEN1,50);


}
/****************************************************************************************/
///�˵���ҳ,ϵͳ
/******************************************************************************************/
void menu_2(void)
{
	

	//��ʱ����
	Gui_DrawFont_C(10,80,BLACK,GREEN1,18);
	Gui_DrawFont_C(26,80,BLACK,GREEN1,19);
	Gui_DrawFont_C(42,80,BLACK,GREEN1,2);
	Gui_DrawFont_C(58,80,BLACK,GREEN1,50);
	//ϵͳ����
	Gui_DrawFont_C(10,110,BLACK,GREEN,20);
	Gui_DrawFont_C(26,110,BLACK,GREEN,21);
	Gui_DrawFont_C(42,110,BLACK,GREEN,2);
	Gui_DrawFont_C(58,110,BLACK,GREEN,50);

	//����
	Gui_DrawFont_C(10,140,BLACK,GREEN1,22);
	Gui_DrawFont_C(26,140,BLACK,GREEN1,23);

}
/****************************************************************************************/
///�˵���ҳ,����
/******************************************************************************************/
void menu_3(void)
{

	//ϵͳ����
	Gui_DrawFont_C(10,110,BLACK,GREEN1,20);
	Gui_DrawFont_C(26,110,BLACK,GREEN1,21);
	Gui_DrawFont_C(42,110,BLACK,GREEN1,2);
	Gui_DrawFont_C(58,110,BLACK,GREEN1,50);

	//����
	Gui_DrawFont_C(10,140,BLACK,GREEN,22);
	Gui_DrawFont_C(26,140,BLACK,GREEN,23);

}
/****************************************************************************************/
///����ģʽҳ
/******************************************************************************************/
void menu1(void)
{
  	Lcd_Clear(GREEN1);
  //����ģʽ
	Gui_DrawFont_C(10,20,BLACK,GREEN1,14);
	Gui_DrawFont_C(26,20,BLACK,GREEN1,15);
	Gui_DrawFont_C(42,20,BLACK,GREEN1,16);
	Gui_DrawFont_C(58,20,BLACK,GREEN1,17);
	Gui_DrawFont_C(74,20,BLACK,GREEN1,11);
	
	//�Զ�
	Gui_DrawFont_C(10,50,BLACK,GREEN,24);
	Gui_DrawFont_C(26,50,BLACK,GREEN,25);

	//����
	Gui_DrawFont_C(10,80,BLACK,GREEN1,8);
	Gui_DrawFont_C(26,80,BLACK,GREEN1,9);
	
	//����
	Gui_DrawFont_C(10,110,BLACK,GREEN1,8);
	Gui_DrawFont_C(26,110,BLACK,GREEN1,51);

}
/****************************************************************************************/
///����ģʽҳ,�Զ�
/******************************************************************************************/
void menu1_0(void)
{
	
	//�Զ�
	Gui_DrawFont_C(10,50,BLACK,GREEN,24);
	Gui_DrawFont_C(26,50,BLACK,GREEN,25);

	//����
	Gui_DrawFont_C(10,80,BLACK,GREEN1,8);
	Gui_DrawFont_C(26,80,BLACK,GREEN1,9);
	


}
/****************************************************************************************/
///����ģʽҳ,����
/******************************************************************************************/
void menu1_1(void)
{

	//�Զ�
	Gui_DrawFont_C(10,50,BLACK,GREEN1,24);
	Gui_DrawFont_C(26,50,BLACK,GREEN1,25);

	//����
	Gui_DrawFont_C(10,80,BLACK,GREEN,8);
	Gui_DrawFont_C(26,80,BLACK,GREEN,9);
	
	//����
	Gui_DrawFont_C(10,110,BLACK,GREEN1,8);
	Gui_DrawFont_C(26,110,BLACK,GREEN1,51);

}
/****************************************************************************************/
///����ģʽҳ,����
/******************************************************************************************/
void menu1_2(void)
{


	//����
	Gui_DrawFont_C(10,80,BLACK,GREEN1,8);
	Gui_DrawFont_C(26,80,BLACK,GREEN1,9);
	
	//����
	Gui_DrawFont_C(10,110,BLACK,GREEN,8);
	Gui_DrawFont_C(26,110,BLACK,GREEN,51);

}

/****************************************************************************************/
///ʱ��������ҳ
/******************************************************************************************/
void menu2(void)
{
  	Lcd_Clear(GREEN1);
  //ʱ������
	Gui_DrawFont_C(10,10,BLACK,GREEN1,35);
	Gui_DrawFont_C(26,10,BLACK,GREEN1,36);
	Gui_DrawFont_C(42,10,BLACK,GREEN1,2);
	Gui_DrawFont_C(58,10,BLACK,GREEN1,50);
	Gui_DrawFont_C(74,10,BLACK,GREEN1,11);
	
	//��һ��
	Gui_DrawFont_C(10,40,BLACK,GREEN,26);
	Gui_DrawFont_C(26,40,BLACK,GREEN,27);
	Gui_DrawFont_C(42,40,BLACK,GREEN,30);

	//�ڶ���
	Gui_DrawFont_C(10,70,BLACK,GREEN1,26);
	Gui_DrawFont_C(26,70,BLACK,GREEN1,28);
	Gui_DrawFont_C(42,70,BLACK,GREEN1,30);
	
	//������
	Gui_DrawFont_C(10,100,BLACK,GREEN1,26);
	Gui_DrawFont_C(26,100,BLACK,GREEN1,29);
	Gui_DrawFont_C(42,100,BLACK,GREEN1,30);
	
	//����
	Gui_DrawFont_C(10,130,BLACK,GREEN1,22);
	Gui_DrawFont_C(26,130,BLACK,GREEN1,23);
}
/****************************************************************************************/
///ʱ������,��һ��
/******************************************************************************************/
void menu2_0(void)
{
	//��һ��
	Gui_DrawFont_C(10,40,BLACK,GREEN,26);
	Gui_DrawFont_C(26,40,BLACK,GREEN,27);
	Gui_DrawFont_C(42,40,BLACK,GREEN,30);

	//�ڶ���
	Gui_DrawFont_C(10,70,BLACK,GREEN1,26);
	Gui_DrawFont_C(26,70,BLACK,GREEN1,28);
	Gui_DrawFont_C(42,70,BLACK,GREEN1,30);
	

}
/****************************************************************************************/
///ʱ������,�ڶ���
/******************************************************************************************/
void menu2_1(void)
{
	//��һ��
	Gui_DrawFont_C(10,40,BLACK,GREEN1,26);
	Gui_DrawFont_C(26,40,BLACK,GREEN1,27);
	Gui_DrawFont_C(42,40,BLACK,GREEN1,30);

	//�ڶ���
	Gui_DrawFont_C(10,70,BLACK,GREEN,26);
	Gui_DrawFont_C(26,70,BLACK,GREEN,28);
	Gui_DrawFont_C(42,70,BLACK,GREEN,30);
	
	//������
	Gui_DrawFont_C(10,100,BLACK,GREEN1,26);
	Gui_DrawFont_C(26,100,BLACK,GREEN1,29);
	Gui_DrawFont_C(42,100,BLACK,GREEN1,30);
	

}
/****************************************************************************************/
///ʱ������,������
/******************************************************************************************/
void menu2_2(void)
{

	//�ڶ���
	Gui_DrawFont_C(10,70,BLACK,GREEN1,26);
	Gui_DrawFont_C(26,70,BLACK,GREEN1,28);
	Gui_DrawFont_C(42,70,BLACK,GREEN1,30);
	
	//������
	Gui_DrawFont_C(10,100,BLACK,GREEN,26);
	Gui_DrawFont_C(26,100,BLACK,GREEN,29);
	Gui_DrawFont_C(42,100,BLACK,GREEN,30);
	
	//����
	Gui_DrawFont_C(10,130,BLACK,GREEN1,22);
	Gui_DrawFont_C(26,130,BLACK,GREEN1,23);
}
/****************************************************************************************/
///ʱ������,����
/******************************************************************************************/
void menu2_3(void)
{
	
	//������
	Gui_DrawFont_C(10,100,BLACK,GREEN1,26);
	Gui_DrawFont_C(26,100,BLACK,GREEN1,29);
	Gui_DrawFont_C(42,100,BLACK,GREEN1,30);
	
	//����
	Gui_DrawFont_C(10,130,BLACK,GREEN,22);
	Gui_DrawFont_C(26,130,BLACK,GREEN,23);
}

/****************************************************************************************/
///��һ��������ҳ
/******************************************************************************************/
void menu21(unsigned char valid)
{
  	Lcd_Clear(GREEN1);
  //��һ��
	Gui_DrawFont_C(10,20,BLACK,GREEN1,26);
	Gui_DrawFont_C(26,20,BLACK,GREEN1,27);
	Gui_DrawFont_C(42,20,BLACK,GREEN1,30);
	Gui_DrawFont_C(58,20,BLACK,GREEN1,11);
	
	//����ʱ��
	Gui_DrawFont_C(10,50,BLACK,GREEN,31);
	Gui_DrawFont_C(26,50,BLACK,GREEN,32);
	Gui_DrawFont_C(42,50,BLACK,GREEN,35);
	Gui_DrawFont_C(58,50,BLACK,GREEN,36);

	//�ر�ʱ��
	Gui_DrawFont_C(10,80,BLACK,GREEN1,33);
	Gui_DrawFont_C(26,80,BLACK,GREEN1,34);
	Gui_DrawFont_C(42,80,BLACK,GREEN1,35);
	Gui_DrawFont_C(58,80,BLACK,GREEN1,36);	
	
	//��Ч
	if(valid==0)
	{
	   Gui_DrawFont_C(10,110,BLACK,GREEN1,38);
	   Gui_DrawFont_C(26,110,BLACK,GREEN1,39);
	}
	else{
	   Gui_DrawFont_C(10,110,BLACK,GREEN1,37);//��Ч
	   Gui_DrawFont_C(26,110,BLACK,GREEN1,39);	
	}

	//����
	Gui_DrawFont_C(10,140,BLACK,GREEN1,22);
	Gui_DrawFont_C(26,140,BLACK,GREEN1,23);
}
/****************************************************************************************/
///��һ��������ҳ,����ʱ��
/******************************************************************************************/
void menu21_0()
{	
	//����ʱ��
	Gui_DrawFont_C(10,50,BLACK,GREEN,31);
	Gui_DrawFont_C(26,50,BLACK,GREEN,32);
	Gui_DrawFont_C(42,50,BLACK,GREEN,35);
	Gui_DrawFont_C(58,50,BLACK,GREEN,36);

	//�ر�ʱ��
	Gui_DrawFont_C(10,80,BLACK,GREEN1,33);
	Gui_DrawFont_C(26,80,BLACK,GREEN1,34);
	Gui_DrawFont_C(42,80,BLACK,GREEN1,35);
	Gui_DrawFont_C(58,80,BLACK,GREEN1,36);	
	

}
/****************************************************************************************/
///��һ��������ҳ,�ر�ʱ��
/******************************************************************************************/
void menu21_1(unsigned char valid)
{	
	//����ʱ��
	Gui_DrawFont_C(10,50,BLACK,GREEN1,31);
	Gui_DrawFont_C(26,50,BLACK,GREEN1,32);
	Gui_DrawFont_C(42,50,BLACK,GREEN1,35);
	Gui_DrawFont_C(58,50,BLACK,GREEN1,36);

	//�ر�ʱ��
	Gui_DrawFont_C(10,80,BLACK,GREEN,33);
	Gui_DrawFont_C(26,80,BLACK,GREEN,34);
	Gui_DrawFont_C(42,80,BLACK,GREEN,35);
	Gui_DrawFont_C(58,80,BLACK,GREEN,36);	
	
	//��Ч
	if(valid==0)
	{
	   Gui_DrawFont_C(10,110,BLACK,GREEN1,38);
	   Gui_DrawFont_C(26,110,BLACK,GREEN1,39);
	}
	else{
	   Gui_DrawFont_C(10,110,BLACK,GREEN1,37);//��Ч
	   Gui_DrawFont_C(26,110,BLACK,GREEN1,39);	
	}
	

}
/****************************************************************************************/
///��һ��������ҳ,//��Ч//��Ч
/******************************************************************************************/
void menu21_2(unsigned char valid)
{	

	//�ر�ʱ��
	Gui_DrawFont_C(10,80,BLACK,GREEN1,33);
	Gui_DrawFont_C(26,80,BLACK,GREEN1,34);
	Gui_DrawFont_C(42,80,BLACK,GREEN1,35);
	Gui_DrawFont_C(58,80,BLACK,GREEN1,36);	
	
	//��Ч
	if(valid==0)
	{
	   Gui_DrawFont_C(10,110,BLACK,GREEN,38);
	   Gui_DrawFont_C(26,110,BLACK,GREEN,39);
	}
	else{
	   Gui_DrawFont_C(10,110,BLACK,GREEN,37);//��Ч
	   Gui_DrawFont_C(26,110,BLACK,GREEN,39);	
	}
	
	//����
	Gui_DrawFont_C(10,140,BLACK,GREEN1,22);
	Gui_DrawFont_C(26,140,BLACK,GREEN1,23);
}
/****************************************************************************************/
///��һ��������ҳ,//��Ч
/******************************************************************************************/
void menu21_21(unsigned char valid)
{	
	//��Ч
	if(valid==0)
	{
	   Gui_DrawFont_C(10,110,BLACK,GRAY0,38);
	   Gui_DrawFont_C(26,110,BLACK,GRAY0,39);
	}
	else{
	   Gui_DrawFont_C(10,110,BLACK,GRAY0,37);//��Ч
	   Gui_DrawFont_C(26,110,BLACK,GRAY0,39);	
	}	


}
/****************************************************************************************/
///��һ��������ҳ,//��Ч
/******************************************************************************************/
void menu21_22(void)
{	
	
	
	//��Ч//��Ч
	Gui_DrawFont_C(10,110,BLACK,GRAY0,38);
	Gui_DrawFont_C(26,110,BLACK,GRAY0,39);
	
	//����
	Gui_DrawFont_C(10,140,BLACK,GREEN1,22);
	Gui_DrawFont_C(26,140,BLACK,GREEN1,23);
}
/****************************************************************************************/
///��һ��������ҳ,//����
/******************************************************************************************/
void menu21_3(unsigned char valid)
{	
	
	//��Ч
	if(valid==0)
	{
	   Gui_DrawFont_C(10,110,BLACK,GREEN1,38);
	   Gui_DrawFont_C(26,110,BLACK,GREEN1,39);
	}
	else{
	   Gui_DrawFont_C(10,110,BLACK,GREEN1,37);//��Ч
	   Gui_DrawFont_C(26,110,BLACK,GREEN1,39);	
	}
	
	//����
	Gui_DrawFont_C(10,140,BLACK,GREEN,22);
	Gui_DrawFont_C(26,140,BLACK,GREEN,23);
}
/****************************************************************************************/
///����ʱ����ҳ
/******************************************************************************************/
void menu211(unsigned char sec,unsigned char min,unsigned char hour)
{
	unsigned char x[2];
  	Lcd_Clear(GREEN1);
   
	//����ʱ��
	Gui_DrawFont_C(10,20,BLACK,GREEN1,31);
	Gui_DrawFont_C(26,20,BLACK,GREEN1,32);
	Gui_DrawFont_C(42,20,BLACK,GREEN1,35);
	Gui_DrawFont_C(58,20,BLACK,GREEN1,36);

	//ʱ
	x[0]=hour/10;
	x[1]=hour%10;
	Gui_DrawFont_C(10,50,BLACK,GREEN,19);
	Gui_DrawFont_C(26,50,BLACK,GREEN,11);
	Gui_DrawFont_S(42,50,BLACK,GREEN1,x[0]);
	Gui_DrawFont_S(50,50,BLACK,GREEN1,x[1]);	
	
	//��
	x[0]=min/10;
	x[1]=min%10;
	Gui_DrawFont_C(10,80,BLACK,GREEN1,64);
	Gui_DrawFont_C(26,80,BLACK,GREEN1,11);
	Gui_DrawFont_S(42,80,BLACK,GREEN1,x[0]);
	Gui_DrawFont_S(50,80,BLACK,GREEN1,x[1]);
		//��
	x[0]=sec/10;
	x[1]=sec%10;
	Gui_DrawFont_C(10,110,BLACK,GREEN1,65);
	Gui_DrawFont_C(26,110,BLACK,GREEN1,11);
	Gui_DrawFont_S(42,110,BLACK,GREEN1,x[0]);
	Gui_DrawFont_S(50,110,BLACK,GREEN1,x[1]);
	//����
	Gui_DrawFont_C(10,140,BLACK,GREEN1,22);
	Gui_DrawFont_C(26,140,BLACK,GREEN1,23);
}
/****************************************************************************************/
///�ر�ʱ����ҳ
/******************************************************************************************/
void menu212(unsigned char sec,unsigned char min,unsigned char hour)
{
		unsigned char x[2];
  	Lcd_Clear(GREEN1);

	//�ر�ʱ��
	Gui_DrawFont_C(10,20,BLACK,GREEN1,33);
	Gui_DrawFont_C(26,20,BLACK,GREEN1,34);
	Gui_DrawFont_C(42,20,BLACK,GREEN1,35);
	Gui_DrawFont_C(58,20,BLACK,GREEN1,36);
	//ʱ
	x[0]=hour/10;
	x[1]=hour%10;
	Gui_DrawFont_C(10,50,BLACK,GREEN,19);
	Gui_DrawFont_C(26,50,BLACK,GREEN,11);
	Gui_DrawFont_S(42,50,BLACK,GREEN1,x[0]);
	Gui_DrawFont_S(50,50,BLACK,GREEN1,x[1]);	
	
	//��
	x[0]=min/10;
	x[1]=min%10;
	Gui_DrawFont_C(10,80,BLACK,GREEN1,64);
	Gui_DrawFont_C(26,80,BLACK,GREEN1,11);
	Gui_DrawFont_S(42,80,BLACK,GREEN1,x[0]);
	Gui_DrawFont_S(50,80,BLACK,GREEN1,x[1]);
		//��
	x[0]=sec/10;
	x[1]=sec%10;
	Gui_DrawFont_C(10,110,BLACK,GREEN1,65);
	Gui_DrawFont_C(26,110,BLACK,GREEN1,11);
	Gui_DrawFont_S(42,110,BLACK,GREEN1,x[0]);
	Gui_DrawFont_S(50,110,BLACK,GREEN1,x[1]);
	//����
	Gui_DrawFont_C(10,140,BLACK,GREEN1,22);
	Gui_DrawFont_C(26,140,BLACK,GREEN1,23);
}
/****************************************************************************************/
///����ʱ��,ʱ1
/******************************************************************************************/
void menu211_0(unsigned char sec,unsigned char min,unsigned char hour)
{
	unsigned char x[2];
	//ʱ
	x[0]=hour/10;
	x[1]=hour%10;
	Gui_DrawFont_C(10,50,BLACK,GREEN,19);
	Gui_DrawFont_C(26,50,BLACK,GREEN,11);
	Gui_DrawFont_S(42,50,BLACK,GREEN1,x[0]);
	Gui_DrawFont_S(50,50,BLACK,GREEN1,x[1]);	
	
	//��
	x[0]=min/10;
	x[1]=min%10;
	Gui_DrawFont_C(10,80,BLACK,GREEN1,64);
	Gui_DrawFont_C(26,80,BLACK,GREEN1,11);
	Gui_DrawFont_S(42,80,BLACK,GREEN1,x[0]);
	Gui_DrawFont_S(50,80,BLACK,GREEN1,x[1]);
		//��
	x[0]=sec/10;
	x[1]=sec%10;
	Gui_DrawFont_C(10,110,BLACK,GREEN1,65);
	Gui_DrawFont_C(26,110,BLACK,GREEN1,11);
	Gui_DrawFont_S(42,110,BLACK,GREEN1,x[0]);
	Gui_DrawFont_S(50,110,BLACK,GREEN1,x[1]);
	//����
	Gui_DrawFont_C(10,140,BLACK,GREEN1,22);
	Gui_DrawFont_C(26,140,BLACK,GREEN1,23);	
}
/****************************************************************************************/
///����ʱ��,ʱ2
/******************************************************************************************/
void menu211_1(unsigned char sec,unsigned char min,unsigned char hour)
{

	unsigned char x[2];
	//ʱ
	x[0]=hour/10;
	x[1]=hour%10;
	Gui_DrawFont_C(10,50,BLACK,GREEN1,19);
	Gui_DrawFont_C(26,50,BLACK,GREEN1,11);
	Gui_DrawFont_S(42,50,BLACK,GREEN,x[0]);
	Gui_DrawFont_S(50,50,BLACK,GREEN,x[1]);	
		
}
/****************************************************************************************/
///����ʱ��,��1
/******************************************************************************************/
void menu211_2(unsigned char sec,unsigned char min,unsigned char hour)
{
	unsigned char x[2];
	//ʱ
	x[0]=hour/10;
	x[1]=hour%10;
	Gui_DrawFont_C(10,50,BLACK,GREEN1,19);
	Gui_DrawFont_C(26,50,BLACK,GREEN1,11);
	Gui_DrawFont_S(42,50,BLACK,GREEN1,x[0]);
	Gui_DrawFont_S(50,50,BLACK,GREEN1,x[1]);	
	
	//��
	x[0]=min/10;
	x[1]=min%10;
	Gui_DrawFont_C(10,80,BLACK,GREEN,64);
	Gui_DrawFont_C(26,80,BLACK,GREEN,11);
	Gui_DrawFont_S(42,80,BLACK,GREEN1,x[0]);
	Gui_DrawFont_S(50,80,BLACK,GREEN1,x[1]);
		//��
	x[0]=sec/10;
	x[1]=sec%10;
	Gui_DrawFont_C(10,110,BLACK,GREEN1,65);
	Gui_DrawFont_C(26,110,BLACK,GREEN1,11);
	Gui_DrawFont_S(42,110,BLACK,GREEN1,x[0]);
	Gui_DrawFont_S(50,110,BLACK,GREEN1,x[1]);
	//����
	Gui_DrawFont_C(10,140,BLACK,GREEN1,22);
	Gui_DrawFont_C(26,140,BLACK,GREEN1,23);	
}
/****************************************************************************************/
///����ʱ��,��2
/******************************************************************************************/
void menu211_3(unsigned char sec,unsigned char min,unsigned char hour)
{
	unsigned char x[2];
	
	
	//��
	x[0]=min/10;
	x[1]=min%10;
	Gui_DrawFont_C(10,80,BLACK,GREEN1,64);
	Gui_DrawFont_C(26,80,BLACK,GREEN1,11);
	Gui_DrawFont_S(42,80,BLACK,GREEN,x[0]);
	Gui_DrawFont_S(50,80,BLACK,GREEN,x[1]);
	
}
/****************************************************************************************/
///����ʱ��,��1
/******************************************************************************************/
void menu211_4(unsigned char sec,unsigned char min,unsigned char hour)
{
	unsigned char x[2];
	//ʱ
	x[0]=hour/10;
	x[1]=hour%10;
	Gui_DrawFont_C(10,50,BLACK,GREEN1,19);
	Gui_DrawFont_C(26,50,BLACK,GREEN1,11);
	Gui_DrawFont_S(42,50,BLACK,GREEN1,x[0]);
	Gui_DrawFont_S(50,50,BLACK,GREEN1,x[1]);	
	
	//��
	x[0]=min/10;
	x[1]=min%10;
	Gui_DrawFont_C(10,80,BLACK,GREEN1,64);
	Gui_DrawFont_C(26,80,BLACK,GREEN1,11);
	Gui_DrawFont_S(42,80,BLACK,GREEN1,x[0]);
	Gui_DrawFont_S(50,80,BLACK,GREEN1,x[1]);
		//��
	x[0]=sec/10;
	x[1]=sec%10;
	Gui_DrawFont_C(10,110,BLACK,GREEN,65);
	Gui_DrawFont_C(26,110,BLACK,GREEN,11);
	Gui_DrawFont_S(42,110,BLACK,GREEN1,x[0]);
	Gui_DrawFont_S(50,110,BLACK,GREEN1,x[1]);
	//����
	Gui_DrawFont_C(10,140,BLACK,GREEN1,22);
	Gui_DrawFont_C(26,140,BLACK,GREEN1,23);	
}
/****************************************************************************************/
///����ʱ��,��2
/******************************************************************************************/
void menu211_5(unsigned char sec,unsigned char min,unsigned char hour)
{
	unsigned char x[2];

		//��
	x[0]=sec/10;
	x[1]=sec%10;
	Gui_DrawFont_C(10,110,BLACK,GREEN1,65);
	Gui_DrawFont_C(26,110,BLACK,GREEN1,11);
	Gui_DrawFont_S(42,110,BLACK,GREEN,x[0]);
	Gui_DrawFont_S(50,110,BLACK,GREEN,x[1]);
	
}
/****************************************************************************************/
///����ʱ��,����
/******************************************************************************************/
void menu211_6(unsigned char sec,unsigned char min,unsigned char hour)
{
	unsigned char x[2];
	//ʱ
	x[0]=hour/10;
	x[1]=hour%10;
	Gui_DrawFont_C(10,50,BLACK,GREEN1,19);
	Gui_DrawFont_C(26,50,BLACK,GREEN1,11);
	Gui_DrawFont_S(42,50,BLACK,GREEN1,x[0]);
	Gui_DrawFont_S(50,50,BLACK,GREEN1,x[1]);	
	
	//��
	x[0]=min/10;
	x[1]=min%10;
	Gui_DrawFont_C(10,80,BLACK,GREEN1,64);
	Gui_DrawFont_C(26,80,BLACK,GREEN1,11);
	Gui_DrawFont_S(42,80,BLACK,GREEN1,x[0]);
	Gui_DrawFont_S(50,80,BLACK,GREEN1,x[1]);
		//��
	x[0]=sec/10;
	x[1]=sec%10;
	Gui_DrawFont_C(10,110,BLACK,GREEN1,65);
	Gui_DrawFont_C(26,110,BLACK,GREEN1,11);
	Gui_DrawFont_S(42,110,BLACK,GREEN1,x[0]);
	Gui_DrawFont_S(50,110,BLACK,GREEN1,x[1]);
	//����
	Gui_DrawFont_C(10,140,BLACK,GREEN,22);
	Gui_DrawFont_C(26,140,BLACK,GREEN,23);	
}
/****************************************************************************************/
///�ڶ���������ҳ
/******************************************************************************************/
void menu22(unsigned char valid)     ///�ڶ���
{
	 Lcd_Clear(GREEN1);
  //�ڶ���
	Gui_DrawFont_C(10,20,BLACK,GREEN1,26);
	Gui_DrawFont_C(26,20,BLACK,GREEN1,28);
	Gui_DrawFont_C(42,20,BLACK,GREEN1,30);
	Gui_DrawFont_C(58,20,BLACK,GREEN1,11);
	
	//����ʱ��
	Gui_DrawFont_C(10,50,BLACK,GREEN,31);
	Gui_DrawFont_C(26,50,BLACK,GREEN,32);
	Gui_DrawFont_C(42,50,BLACK,GREEN,35);
	Gui_DrawFont_C(58,50,BLACK,GREEN,36);

	//�ر�ʱ��
	Gui_DrawFont_C(10,80,BLACK,GREEN1,33);
	Gui_DrawFont_C(26,80,BLACK,GREEN1,34);
	Gui_DrawFont_C(42,80,BLACK,GREEN1,35);
	Gui_DrawFont_C(58,80,BLACK,GREEN1,36);	
	
	//��Ч
	if(valid==0)
	{
	   Gui_DrawFont_C(10,110,BLACK,GREEN1,38);
	   Gui_DrawFont_C(26,110,BLACK,GREEN1,39);
	}
	else{
	   Gui_DrawFont_C(10,110,BLACK,GREEN1,37);//��Ч
	   Gui_DrawFont_C(26,110,BLACK,GREEN1,39);	
	}
	
	//����
	Gui_DrawFont_C(10,140,BLACK,GREEN1,22);
	Gui_DrawFont_C(26,140,BLACK,GREEN1,23);
}

/****************************************************************************************/
///������������ҳ
/******************************************************************************************/
void menu23(unsigned char valid)     ///������
{
	Lcd_Clear(GREEN1);
  //������
	Gui_DrawFont_C(10,20,BLACK,GREEN1,26);
	Gui_DrawFont_C(26,20,BLACK,GREEN1,29);
	Gui_DrawFont_C(42,20,BLACK,GREEN1,30);
	Gui_DrawFont_C(58,20,BLACK,GREEN1,11);
	
	//����ʱ��
	Gui_DrawFont_C(10,50,BLACK,GREEN,31);
	Gui_DrawFont_C(26,50,BLACK,GREEN,32);
	Gui_DrawFont_C(42,50,BLACK,GREEN,35);
	Gui_DrawFont_C(58,50,BLACK,GREEN,36);

	//�ر�ʱ��
	Gui_DrawFont_C(10,80,BLACK,GREEN1,33);
	Gui_DrawFont_C(26,80,BLACK,GREEN1,34);
	Gui_DrawFont_C(42,80,BLACK,GREEN1,35);
	Gui_DrawFont_C(58,80,BLACK,GREEN1,36);	
	
	//��Ч
	if(valid==0)
	{
	   Gui_DrawFont_C(10,110,BLACK,GREEN1,38);
	   Gui_DrawFont_C(26,110,BLACK,GREEN1,39);
	}
	else{
	   Gui_DrawFont_C(10,110,BLACK,GREEN1,37);//��Ч
	   Gui_DrawFont_C(26,110,BLACK,GREEN1,39);	
	}
	
	//����
	Gui_DrawFont_C(10,140,BLACK,GREEN1,22);
	Gui_DrawFont_C(26,140,BLACK,GREEN1,23);
}
/****************************************************************************************/
///ϵͳ������ҳ
/******************************************************************************************/
void menu3(void)
{
  	Lcd_Clear(GREEN1);
  //ϵͳ����
	Gui_DrawFont_C(10,10,BLACK,GREEN1,20);
	Gui_DrawFont_C(26,10,BLACK,GREEN1,22);
	Gui_DrawFont_C(42,10,BLACK,GREEN1,2);
	Gui_DrawFont_C(58,10,BLACK,GREEN1,50);
	Gui_DrawFont_C(74,10,BLACK,GREEN1,11);
	
	//ʱ������
	Gui_DrawFont_C(10,35,BLACK,GREEN,35);
	Gui_DrawFont_C(26,35,BLACK,GREEN,36);
	Gui_DrawFont_C(42,35,BLACK,GREEN,2);
	Gui_DrawFont_C(58,35,BLACK,GREEN,50);

	//����ת��
	Gui_DrawFont_C(10,60,BLACK,GREEN1,40);
	Gui_DrawFont_C(26,60,BLACK,GREEN1,41);
	Gui_DrawFont_C(42,60,BLACK,GREEN1,42);
	Gui_DrawFont_C(58,60,BLACK,GREEN1,43);
	
	//�²�У׼
	Gui_DrawFont_C(10,85,BLACK,GREEN1,44);
	Gui_DrawFont_C(26,85,BLACK,GREEN1,47);
	Gui_DrawFont_C(42,85,BLACK,GREEN1,48);
	Gui_DrawFont_C(58,85,BLACK,GREEN1,49);
	
	//�¶�����
	Gui_DrawFont_C(10,110,BLACK,GREEN1,44);
	Gui_DrawFont_C(26,110,BLACK,GREEN1,45);
	Gui_DrawFont_C(42,110,BLACK,GREEN1,2);
	Gui_DrawFont_C(58,110,BLACK,GREEN1,50);
	
		//����
	Gui_DrawFont_C(10,135,BLACK,GREEN1,22);
	Gui_DrawFont_C(26,135,BLACK,GREEN1,23);

}
/****************************************************************************************/
///ϵͳ����,ʱ��
/******************************************************************************************/
void menu3_0(void)
{
	
	//ʱ������
	Gui_DrawFont_C(10,35,BLACK,GREEN,35);
	Gui_DrawFont_C(26,35,BLACK,GREEN,36);
	Gui_DrawFont_C(42,35,BLACK,GREEN,2);
	Gui_DrawFont_C(58,35,BLACK,GREEN,50);

	//����ת��
	Gui_DrawFont_C(10,60,BLACK,GREEN1,40);
	Gui_DrawFont_C(26,60,BLACK,GREEN1,41);
	Gui_DrawFont_C(42,60,BLACK,GREEN1,42);
	Gui_DrawFont_C(58,60,BLACK,GREEN1,43);
	

}
/****************************************************************************************/
///ϵͳ���ã�����
/******************************************************************************************/
void menu3_1(void)
{

	//ʱ������
	Gui_DrawFont_C(10,35,BLACK,GREEN1,35);
	Gui_DrawFont_C(26,35,BLACK,GREEN1,36);
	Gui_DrawFont_C(42,35,BLACK,GREEN1,2);
	Gui_DrawFont_C(58,35,BLACK,GREEN1,50);

	//����ת��
	Gui_DrawFont_C(10,60,BLACK,GREEN,40);
	Gui_DrawFont_C(26,60,BLACK,GREEN,41);
	Gui_DrawFont_C(42,60,BLACK,GREEN,42);
	Gui_DrawFont_C(58,60,BLACK,GREEN,43);
	
	//�²�У׼
	Gui_DrawFont_C(10,85,BLACK,GREEN1,44);
	Gui_DrawFont_C(26,85,BLACK,GREEN1,47);
	Gui_DrawFont_C(42,85,BLACK,GREEN1,48);
	Gui_DrawFont_C(58,85,BLACK,GREEN1,49);

}
/****************************************************************************************/
///ϵͳ����,�²�
/******************************************************************************************/
void menu3_2(void)
{


	//����ת��
	Gui_DrawFont_C(10,60,BLACK,GREEN1,40);
	Gui_DrawFont_C(26,60,BLACK,GREEN1,41);
	Gui_DrawFont_C(42,60,BLACK,GREEN1,42);
	Gui_DrawFont_C(58,60,BLACK,GREEN1,43);
	
	//�²�У׼
	Gui_DrawFont_C(10,85,BLACK,GREEN,44);
	Gui_DrawFont_C(26,85,BLACK,GREEN,47);
	Gui_DrawFont_C(42,85,BLACK,GREEN,48);
	Gui_DrawFont_C(58,85,BLACK,GREEN,49);
	
	//�¶�����
	Gui_DrawFont_C(10,110,BLACK,GREEN1,44);
	Gui_DrawFont_C(26,110,BLACK,GREEN1,45);
	Gui_DrawFont_C(42,110,BLACK,GREEN1,2);
	Gui_DrawFont_C(58,110,BLACK,GREEN1,50);


}
/****************************************************************************************/
///ϵͳ����,�ز�
/******************************************************************************************/
void menu3_3(void)
{	
	//�²�У׼
	Gui_DrawFont_C(10,85,BLACK,GREEN1,44);
	Gui_DrawFont_C(26,85,BLACK,GREEN1,47);
	Gui_DrawFont_C(42,85,BLACK,GREEN1,48);
	Gui_DrawFont_C(58,85,BLACK,GREEN1,49);
	
	//�¶Ȼز�
	Gui_DrawFont_C(10,110,BLACK,GREEN,44);
	Gui_DrawFont_C(26,110,BLACK,GREEN,45);
	Gui_DrawFont_C(42,110,BLACK,GREEN,2);
	Gui_DrawFont_C(58,110,BLACK,GREEN,50);
	
		//����
	Gui_DrawFont_C(10,135,BLACK,GREEN1,22);
	Gui_DrawFont_C(26,135,BLACK,GREEN1,23);

}
/****************************************************************************************/
///ϵͳ���ã�����
/******************************************************************************************/
void menu3_4(void)
{	
	//�¶�����
	Gui_DrawFont_C(10,110,BLACK,GREEN1,44);
	Gui_DrawFont_C(26,110,BLACK,GREEN1,45);
	Gui_DrawFont_C(42,110,BLACK,GREEN1,2);
	Gui_DrawFont_C(58,110,BLACK,GREEN1,50);
	
		//����
	Gui_DrawFont_C(10,135,BLACK,GREEN,22);
	Gui_DrawFont_C(26,135,BLACK,GREEN,23);

}

/****************************************************************************************/
///ϵͳ����->ʱ��������ҳ
/******************************************************************************************/
void menu31(unsigned char sec,unsigned char min,unsigned char hour,unsigned char day,unsigned char date,unsigned char month,unsigned char year)
{
  unsigned char x[6];
	Lcd_Clear(GREEN1);
		//ʱ������

	Gui_DrawFont_C(10,20,BLACK,GREEN1,35);
	Gui_DrawFont_C(26,20,BLACK,GREEN1,36);
	Gui_DrawFont_C(42,20,BLACK,GREEN1,2);
	Gui_DrawFont_C(58,20,BLACK,GREEN1,50);
	
	//���
	x[0]=year/10;
	x[1]=year%10;
	Gui_DrawFont_C(10,50,BLACK,GREEN,52);	
	Gui_DrawFont_C(26,50,BLACK,GREEN,55);
	Gui_DrawFont_C(42,50,BLACK,GREEN,11);
	Gui_DrawFont_S(58,50,BLACK,GREEN1,2);
	Gui_DrawFont_S(66,50,BLACK,GREEN1,0);
	Gui_DrawFont_S(74,50,BLACK,GREEN1,x[0]);
	Gui_DrawFont_S(82,50,BLACK,GREEN1,x[1]);
	
	//����
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
	
	//ʱ��
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

			//����
	Gui_DrawFont_C(10,140,BLACK,GREEN1,22);
	Gui_DrawFont_C(26,140,BLACK,GREEN1,23);
}
/****************************************************************************************/
///ϵͳ����->ʱ������,���1
/******************************************************************************************/
void menu31_0(unsigned char sec,unsigned char min,unsigned char hour,unsigned char day,unsigned char date,unsigned char month,unsigned char year)
{
  unsigned char x[6];
	
	//���
	x[0]=year/10;
	x[1]=year%10;
	Gui_DrawFont_C(10,50,BLACK,GREEN,52);	
	Gui_DrawFont_C(26,50,BLACK,GREEN,55);
	Gui_DrawFont_C(42,50,BLACK,GREEN,11);
	Gui_DrawFont_S(58,50,BLACK,GREEN1,2);
	Gui_DrawFont_S(66,50,BLACK,GREEN1,0);
	Gui_DrawFont_S(74,50,BLACK,GREEN1,x[0]);
	Gui_DrawFont_S(82,50,BLACK,GREEN1,x[1]);
	
	//����
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
	
	//ʱ��
	x[0]=hour/10;
	x[1]=hour%10;
	x[2]=min/10;
	x[3]=min%10;
	x[4]=sec/10;
	x[5]=sec%10;	

}
/****************************************************************************************/
///ϵͳ����->ʱ������,���2
/******************************************************************************************/
void menu31_1(unsigned char year)
{
  unsigned char x[6];
	
	//���
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
///ϵͳ����->ʱ������,����1
/******************************************************************************************/
void menu31_2(unsigned char sec,unsigned char min,unsigned char hour,unsigned char day,unsigned char date,unsigned char month,unsigned char year)
{
  unsigned char x[6];
	
	//���
	x[0]=year/10;
	x[1]=year%10;
	Gui_DrawFont_C(10,50,BLACK,GREEN1,52);	
	Gui_DrawFont_C(26,50,BLACK,GREEN1,55);
	Gui_DrawFont_C(42,50,BLACK,GREEN1,11);
	Gui_DrawFont_S(58,50,BLACK,GREEN1,2);
	Gui_DrawFont_S(66,50,BLACK,GREEN1,0);
	Gui_DrawFont_S(74,50,BLACK,GREEN1,x[0]);
	Gui_DrawFont_S(82,50,BLACK,GREEN1,x[1]);
	
	//����
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
	
	//ʱ��
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
///ϵͳ����->ʱ������,���ڣ���
/******************************************************************************************/
void menu31_3(unsigned char date,unsigned char month)
{
  unsigned char x[6];
	
	//����
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
///ϵͳ����->ʱ������,���ڣ���
/******************************************************************************************/
void menu31_4(unsigned char date,unsigned char month)
{
  unsigned char x[6];
	
	//����
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
///ϵͳ����->ʱ������,ʱ��1
/******************************************************************************************/
void menu31_5(unsigned char sec,unsigned char min,unsigned char hour,unsigned char day,unsigned char date,unsigned char month,unsigned char year)
{
  unsigned char x[6];
	
	//���
	x[0]=year/10;
	x[1]=year%10;

	
	//����
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
	
	//ʱ��
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

			//����
	Gui_DrawFont_C(10,140,BLACK,GREEN1,22);
	Gui_DrawFont_C(26,140,BLACK,GREEN1,23);
}
/****************************************************************************************/
///ϵͳ����->ʱ������,ʱ
/******************************************************************************************/
void menu31_6(unsigned char sec,unsigned char min,unsigned char hour)
{
  unsigned char x[6];
		
	//ʱ��
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
///ϵͳ����->ʱ������,��
/******************************************************************************************/
void menu31_7(unsigned char sec,unsigned char min,unsigned char hour)
{
  unsigned char x[6];
		
	//ʱ��
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
///ϵͳ����->ʱ������,��
/******************************************************************************************/
void menu31_8(unsigned char sec,unsigned char min,unsigned char hour)
{
  unsigned char x[6];
		
	//ʱ��
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
///ϵͳ����->ʱ������,����
/******************************************************************************************/
void menu31_9(unsigned char sec,unsigned char min,unsigned char hour,unsigned char day,unsigned char date,unsigned char month,unsigned char year)
{
  unsigned char x[6];
	
	//���
	x[0]=year/10;
	x[1]=year%10;

	
	//����
	x[0]=month/10;
	x[1]=month%10;
	x[2]=date/10;
	x[3]=date%10;

	
	//ʱ��
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

			//����
	Gui_DrawFont_C(10,140,BLACK,GREEN,22);
	Gui_DrawFont_C(26,140,BLACK,GREEN,23);
}
/****************************************************************************************/
///ϵͳ����->����ת����ҳ
/******************************************************************************************/
void menu32(void)
{
	Lcd_Clear(GREEN1);
   	//����ת��
	Gui_DrawFont_C(10,15,BLACK,GREEN1,40);
	Gui_DrawFont_C(26,15,BLACK,GREEN1,41);
	Gui_DrawFont_C(42,15,BLACK,GREEN1,42);
	Gui_DrawFont_C(58,15,BLACK,GREEN1,43);
	   	//�ߵ�
	Gui_DrawFont_C(10,35,BLACK,GREEN,73);
	Gui_DrawFont_C(42,35,BLACK,GREEN,72);

	   	//�иߵ�
	Gui_DrawFont_C(10,55,BLACK,GREEN1,74);
	Gui_DrawFont_C(26,55,BLACK,GREEN1,73);
	Gui_DrawFont_C(42,55,BLACK,GREEN1,72);

	   	//�е�
	Gui_DrawFont_C(10,75,BLACK,GREEN1,74);
	Gui_DrawFont_C(42,75,BLACK,GREEN1,72);

		   	//�е͵�
	Gui_DrawFont_C(10,95,BLACK,GREEN1,74);
	Gui_DrawFont_C(26,95,BLACK,GREEN1,75);
	Gui_DrawFont_C(42,95,BLACK,GREEN1,72);

	   	//�͵�
	Gui_DrawFont_C(10,115,BLACK,GREEN1,75);
	Gui_DrawFont_C(42,115,BLACK,GREEN1,72);
}
/****************************************************************************************/
///ϵͳ����->����ת��,�ߵ�
/******************************************************************************************/
void menu32_0(void)
{
	   	//�ߵ�
	Gui_DrawFont_C(10,35,BLACK,GREEN,73);
	Gui_DrawFont_C(42,35,BLACK,GREEN,72);

	   	//�иߵ�
	Gui_DrawFont_C(10,55,BLACK,GREEN1,74);
	Gui_DrawFont_C(26,55,BLACK,GREEN1,73);
	Gui_DrawFont_C(42,55,BLACK,GREEN1,72);

}
/****************************************************************************************/
///ϵͳ����->����ת��,�иߵ�
/******************************************************************************************/
void menu32_1(void)
{
	   	//�ߵ�
	Gui_DrawFont_C(10,35,BLACK,GREEN1,73);
	Gui_DrawFont_C(42,35,BLACK,GREEN1,72);

	   	//�иߵ�
	Gui_DrawFont_C(10,55,BLACK,GREEN,74);
	Gui_DrawFont_C(26,55,BLACK,GREEN,73);
	Gui_DrawFont_C(42,55,BLACK,GREEN,72);

	   	//�е�
	Gui_DrawFont_C(10,75,BLACK,GREEN1,74);
	Gui_DrawFont_C(42,75,BLACK,GREEN1,72);
}
/****************************************************************************************/
///ϵͳ����->����ת��,�е�
/******************************************************************************************/
void menu32_2(void)
{
	   	//�иߵ�
	Gui_DrawFont_C(10,55,BLACK,GREEN1,74);
	Gui_DrawFont_C(26,55,BLACK,GREEN1,73);
	Gui_DrawFont_C(42,55,BLACK,GREEN1,72);

	   	//�е�
	Gui_DrawFont_C(10,75,BLACK,GREEN,74);
	Gui_DrawFont_C(42,75,BLACK,GREEN,72);

		   	//�е͵�
	Gui_DrawFont_C(10,95,BLACK,GREEN1,74);
	Gui_DrawFont_C(26,95,BLACK,GREEN1,75);
	Gui_DrawFont_C(42,95,BLACK,GREEN1,72);

}
/****************************************************************************************/
///ϵͳ����->����ת�٣��е͵�
/******************************************************************************************/
void menu32_3(void)
{
	   	//�е�
	Gui_DrawFont_C(10,75,BLACK,GREEN1,74);
	Gui_DrawFont_C(42,75,BLACK,GREEN1,72);

		   	//�е͵�
	Gui_DrawFont_C(10,95,BLACK,GREEN,74);
	Gui_DrawFont_C(26,95,BLACK,GREEN,75);
	Gui_DrawFont_C(42,95,BLACK,GREEN,72);

	   	//�͵�
	Gui_DrawFont_C(10,115,BLACK,GREEN1,75);

	Gui_DrawFont_C(42,115,BLACK,GREEN1,72);
}
/****************************************************************************************/
///ϵͳ����->����ת�٣��͵�
/******************************************************************************************/
void menu32_4(void)
{
		   	//�е͵�
	Gui_DrawFont_C(10,95,BLACK,GREEN1,74);
	Gui_DrawFont_C(26,95,BLACK,GREEN1,75);
	Gui_DrawFont_C(42,95,BLACK,GREEN1,72);

	   	//�͵�
	Gui_DrawFont_C(10,115,BLACK,GREEN,75);

	Gui_DrawFont_C(42,115,BLACK,GREEN,72);
}
/****************************************************************************************/
///ϵͳ����->�²�У׼��ҳ
/******************************************************************************************/
void menu33(float temperr,unsigned char sym)
{
	int temperr1,x[2];
	temperr1=temperr*10;
	x[0]=temperr1/10;
	x[1]=temperr1%10;
		Lcd_Clear(GREEN1);
	/////�²�У׼
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
		//�¶ȷ�ΧΪ-7~7
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
///ϵͳ����->�²�У׼��ҳ,����
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
///ϵͳ����->�²�У׼��ҳ,cha
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
///ϵͳ����->�¶�������ҳ
/******************************************************************************************/
void menu34(float tempset1,float tempdiff1)
{
	int x[2],y,z;
	z=tempset1;
	x[0]=z/10;
	x[1]=z%10;
	y=tempdiff1;
	Lcd_Clear(GREEN1);
	//�¶����ã�
	Gui_DrawFont_C(10,20,BLACK,GREEN1,44);
	Gui_DrawFont_C(26,20,BLACK,GREEN1,45);
	Gui_DrawFont_C(42,20,BLACK,GREEN1,2);
	Gui_DrawFont_C(58,20,BLACK,GREEN1,50);
	Gui_DrawFont_C(74,20,BLACK,GREEN1,11);
	//�趨�¶ȣ�
	Gui_DrawFont_C(10,50,BLACK,GREEN,2);
	Gui_DrawFont_C(26,50,BLACK,GREEN,3);
	Gui_DrawFont_C(42,50,BLACK,GREEN,44);
	Gui_DrawFont_C(58,50,BLACK,GREEN,45);
	Gui_DrawFont_C(74,50,BLACK,GREEN,11);
	Gui_DrawFont_S(90,50,BLUE,GREEN1,x[0]);
	Gui_DrawFont_S(98,50,BLUE,GREEN1,x[1]);
	Gui_DrawFont_C(106,50,BLACK,GREEN1,10);
	//�¶Ȼز�
	Gui_DrawFont_C(10,80,BLACK,GREEN1,44);
	Gui_DrawFont_C(26,80,BLACK,GREEN1,45);
	Gui_DrawFont_C(42,80,BLACK,GREEN1,46);
	Gui_DrawFont_C(58,80,BLACK,GREEN1,47);
	Gui_DrawFont_C(74,80,BLACK,GREEN1,11);
	Gui_DrawFont_S(90,80,BLUE,GREEN1,y);
	Gui_DrawFont_C(106,80,BLACK,GREEN1,10);
	//����
	Gui_DrawFont_C(10,110,BLACK,GREEN1,22);
	Gui_DrawFont_C(26,110,BLACK,GREEN1,23);
	//�¶ȷ�ΧΪ15~25

}
/****************************************************************************************/
///ϵͳ����->�¶�����->�趨�¶�
/******************************************************************************************/
void menu34_0(float tempset1,float tempdiff1)
{
	int x[2],y,z;
	z=tempset1;
	x[0]=z/10;
	x[1]=z%10;
	y=tempdiff1;
	//�趨�¶ȣ�
	Gui_DrawFont_C(10,50,BLACK,GREEN,2);
	Gui_DrawFont_C(26,50,BLACK,GREEN,3);
	Gui_DrawFont_C(42,50,BLACK,GREEN,44);
	Gui_DrawFont_C(58,50,BLACK,GREEN,45);
	Gui_DrawFont_C(74,50,BLACK,GREEN,11);
	Gui_DrawFont_S(90,50,BLUE,GREEN1,x[0]);
	Gui_DrawFont_S(98,50,BLUE,GREEN1,x[1]);
	Gui_DrawFont_C(106,50,BLACK,GREEN1,10);
	//�¶Ȼز�
	Gui_DrawFont_C(10,80,BLACK,GREEN1,44);
	Gui_DrawFont_C(26,80,BLACK,GREEN1,45);
	Gui_DrawFont_C(42,80,BLACK,GREEN1,46);
	Gui_DrawFont_C(58,80,BLACK,GREEN1,47);
	Gui_DrawFont_C(74,80,BLACK,GREEN1,11);
	Gui_DrawFont_S(90,80,BLUE,GREEN1,y);
	Gui_DrawFont_C(106,80,BLACK,GREEN1,10);


}
/****************************************************************************************/
///ϵͳ����->�¶�����->�¶Ȼز�
/******************************************************************************************/
void menu34_1(float tempset1,float tempdiff1)
{
	int x[2],y,z;
	z=tempset1;
	x[0]=z/10;
	x[1]=z%10;
	y=tempdiff1;
	//�趨�¶ȣ�
	Gui_DrawFont_C(10,50,BLACK,GREEN1,2);
	Gui_DrawFont_C(26,50,BLACK,GREEN1,3);
	Gui_DrawFont_C(42,50,BLACK,GREEN1,44);
	Gui_DrawFont_C(58,50,BLACK,GREEN1,45);
	Gui_DrawFont_C(74,50,BLACK,GREEN1,11);
	Gui_DrawFont_S(90,50,BLUE,GREEN1,x[0]);
	Gui_DrawFont_S(98,50,BLUE,GREEN1,x[1]);
	Gui_DrawFont_C(106,50,BLACK,GREEN1,10);
	//�¶Ȼز�
	Gui_DrawFont_C(10,80,BLACK,GREEN,44);
	Gui_DrawFont_C(26,80,BLACK,GREEN,45);
	Gui_DrawFont_C(42,80,BLACK,GREEN,46);
	Gui_DrawFont_C(58,80,BLACK,GREEN,47);
	Gui_DrawFont_C(74,80,BLACK,GREEN,11);
	Gui_DrawFont_S(90,80,BLUE,GREEN1,y);
	Gui_DrawFont_C(106,80,BLACK,GREEN1,10);
	//����
	Gui_DrawFont_C(10,110,BLACK,GREEN1,22);
	Gui_DrawFont_C(26,110,BLACK,GREEN1,23);

}
/****************************************************************************************/
///ϵͳ����->�¶�����->����
/******************************************************************************************/
void menu34_2(float tempset1,float tempdiff1)
{
	int x[2],y,z;
	z=tempset1;
	x[0]=z/10;
	x[1]=z%10;
	y=tempdiff1;

	//�¶Ȼز�
	Gui_DrawFont_C(10,80,BLACK,GREEN1,44);
	Gui_DrawFont_C(26,80,BLACK,GREEN1,45);
	Gui_DrawFont_C(42,80,BLACK,GREEN1,46);
	Gui_DrawFont_C(58,80,BLACK,GREEN1,47);
	Gui_DrawFont_C(74,80,BLACK,GREEN1,11);
	Gui_DrawFont_S(90,80,BLUE,GREEN1,y);
	Gui_DrawFont_C(106,80,BLACK,GREEN1,10);
	//����
	Gui_DrawFont_C(10,110,BLACK,GREEN,22);
	Gui_DrawFont_C(26,110,BLACK,GREEN,23);

}
/****************************************************************************************/
///ϵͳ����->�¶�����->�趨�¶�->�¶�
/******************************************************************************************/
void menu34_01(float tempset1,float tempdiff1)
{
	int x[2],y,z;
	z=tempset1;
	x[0]=z/10;
	x[1]=z%10;
	y=tempdiff1;
	//�趨�¶ȣ�
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
///ϵͳ����->�¶�����->�趨�¶�->�ز�
/******************************************************************************************/
void menu34_11(float tempset1,float tempdiff1)
{
	int x[2],y,z;
	z=tempset1;
	x[0]=z/10;
	x[1]=z%10;
	y=tempdiff1;

	//�¶Ȼز�
	Gui_DrawFont_C(10,80,BLACK,GREEN1,44);
	Gui_DrawFont_C(26,80,BLACK,GREEN1,45);
	Gui_DrawFont_C(42,80,BLACK,GREEN1,46);
	Gui_DrawFont_C(58,80,BLACK,GREEN1,47);
	Gui_DrawFont_C(74,80,BLACK,GREEN1,11);
	Gui_DrawFont_S(90,80,BLUE,GREEN,y);
	Gui_DrawFont_C(106,80,BLACK,GREEN1,10);

}
