#ifndef __DS1390_H
#define __DS1390_H 			   

void InitDs1390(void);
unsigned int readtime() ;
unsigned int readtime2();
void Settime(unsigned char year,unsigned char month,unsigned char date,unsigned char day,unsigned char hour,unsigned char min,unsigned char sec);

#endif

