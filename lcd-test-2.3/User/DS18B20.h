#ifndef __DS18B20_H
#define __DS18B20_H 			   

unsigned int reset_ds18b20(void);
int read_temp_ds18b20(void);
unsigned char read_byte_ds18b20(void);
unsigned char read_bit_ds18b20(void);
void write_byte_ds18b20(unsigned char dat);
void ds18b20_init(void); 
void write_bit_ds18b20(unsigned char dat);


#endif
