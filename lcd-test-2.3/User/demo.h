#ifndef __DEMO_H
#define __DEMO_H 			   

void welcome(void);
void time_now(unsigned char sec,unsigned char min,unsigned char hour,unsigned char day,unsigned char date,unsigned char month,unsigned char year);
void time_now1(unsigned char sec,unsigned char min,unsigned char hour,unsigned char day,unsigned char date,unsigned char month,unsigned char year);
float Font_Test(float tempset,float temperr,unsigned char symbol);
float temp_dq(float temperr,unsigned char symbol);
void hoting(void);
void colding(void);
void normal(void);
void unnormal(void);
void stop(void);

void menu(void);
void menu_0(void);
void menu_1(void);
void menu_2(void);
void menu_3(void);

void menu1(void);
void menu1_0(void);
void menu1_1(void);
void menu1_2(void);

void menu2(void);         ////ʱ������
void menu2_0(void);
void menu2_1(void);
void menu2_2(void);
void menu2_3(void);

void menu21(unsigned char valid);     ///��һ��
void menu21_0();
void menu21_1(unsigned char valid);
void menu21_2(unsigned char valid);
void menu21_21(unsigned char valid);   //��Ч
void menu21_22(void);  //��Ч
void menu21_3(unsigned char valid);
void menu211(unsigned char sec,unsigned char min,unsigned char hour); //����ʱ��
void menu212(unsigned char sec,unsigned char min,unsigned char hour); //�ر�ʱ��
void menu211_0(unsigned char sec,unsigned char min,unsigned char hour);//ʱ1
void menu211_1(unsigned char sec,unsigned char min,unsigned char hour);//ʱ2
void menu211_2(unsigned char sec,unsigned char min,unsigned char hour);//��1
void menu211_3(unsigned char sec,unsigned char min,unsigned char hour);//��2
void menu211_4(unsigned char sec,unsigned char min,unsigned char hour);//��1
void menu211_5(unsigned char sec,unsigned char min,unsigned char hour);//��2
void menu211_6(unsigned char sec,unsigned char min,unsigned char hour);//����

void menu22(unsigned char valid);     ///�ڶ���


void menu23(unsigned char valid);     ///������


void menu3(void);
void menu3_0(void);
void menu3_1(void);
void menu3_2(void);
void menu3_3(void);
void menu3_4(void);

///ʱ������
void menu31(unsigned char sec,unsigned char min,unsigned char hour,unsigned char day,unsigned char date,unsigned char month,unsigned char year);
void menu31_0(unsigned char sec,unsigned char min,unsigned char hour,unsigned char day,unsigned char date,unsigned char month,unsigned char year);
void menu31_1(unsigned char year);
void menu31_2(unsigned char sec,unsigned char min,unsigned char hour,unsigned char day,unsigned char date,unsigned char month,unsigned char year);
void menu31_3(unsigned char date,unsigned char month);
void menu31_4(unsigned char date,unsigned char month);
void menu31_5(unsigned char sec,unsigned char min,unsigned char hour,unsigned char day,unsigned char date,unsigned char month,unsigned char year);
void menu31_6(unsigned char sec,unsigned char min,unsigned char hour);
void menu31_7(unsigned char sec,unsigned char min,unsigned char hour);
void menu31_8(unsigned char sec,unsigned char min,unsigned char hour);
void menu31_9(unsigned char sec,unsigned char min,unsigned char hour,unsigned char day,unsigned char date,unsigned char month,unsigned char year);

////////////////ϵͳ����->���ȵ���
void menu32(void);
void menu32_0(void);
void menu32_1(void);
void menu32_2(void);
void menu32_3(void);
void menu32_4(void);
////////////////ϵͳ����->�¶�У���
void menu33(float temperr,unsigned char sym);
void menu33_0(float temperr,unsigned char sym);
void menu33_1(float temperr,unsigned char sym);
////////////ϵͳ����->�¶�����
void menu34(float tempset,float tempdiff);
void menu34_0(float tempset,float tempdiff);
void menu34_1(float tempset1,float tempdiff1);
void menu34_2(float tempset1,float tempdiff1);
void menu34_01(float tempset1,float tempdiff1);
void menu34_11(float tempset1,float tempdiff1);
#endif
