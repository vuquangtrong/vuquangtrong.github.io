#ifndef RASPI_GPIO_H
#define RASPI_GPIO_H


#include<unistd.h>
#include<iostream>
#include<fstream>
#include<cstdlib> 
#include<string>
#include<vector>
#include<ctime>
#include<linux/i2c-dev.h> 
#include <linux/i2c.h>
#include<linux/spi/spidev.h> 
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<cstring>

#include <cmath> 
#include <cstdio> 



#define HIGH 1
#define LOW 0
#define OUT 1
#define IN 0
#define MAX_BUFFER 100  //GPIO MAX transmission Data
#define READ_MODE 1
#define WRITE_MODE 0 


class RaspiGpio //for read and write digital values and delay in milisecond

{

public : 


RaspiGpio(int pin , int type); 

int digitalReadPin() const ; 
int digitalWritePin(  int value);

static void CleanPin(); 
static int milisecondDelay(int millisecond); 


private : 
static std::vector<int> Pins ;
int ExportPin();  
int DirectionPin(int type);

int m_pin ; 
int m_type;
}; 



int UnexportPin(int pin); 




class I2C 

{
 public:

 I2C(char adaptaer);
 ~I2C();  
 uint8_t ReadBytes(const char ByteToRead , char m_addr); 
 bool ReadNowByte(uint8_t *buffer, char m_addr); 
 bool Write3Byte(uint8_t MSB , uint8_t LSB , uint8_t length, char m_addr);
 int WriteByte(char command , char reg , char m_addr ); 

 bool i2cWrRd(__u8 *buffewr , __u8 *result , int send_length , int read_length, char m_addr); 
 bool Write_Bytes(__u8 *buffer , int length, char m_addr);
 bool  WriteOneByte_ReadBuff(uint8_t Byte , uint8_t *buff , int length, char m_addr);


 private : 

 char m_addr ; 
 char m_adaptaer; 
 int m_file ; 

};




/*
class SPI 

{

public : 

SPI( int devicePort , int speed , int bitsperworld  ); 
uint16_t transfer(uint16_t value );  //this is transfer a value for writing values . and this can read value that will be returned from the fonction  . choose IOCTL_RD for read  
~SPI(); 

private : 

int _spi_fd ; 
int _clockmode;  
int _speed  ,  _bitperworld;

};

*/


class Spi 

{
 public: 

 Spi(); 
 ~Spi(); 
 bool transfer(uint8_t *rxData ,const uint8_t *txData ); 
 private: 
  int _fd;
 


};





int bitRead(uint8_t Byte , int bitnum);



static uint8_t pgm_read_byte(uint8_t *ptr)
{
  return *ptr;
}


static int16_t pgm_read_word(uint8_t *ptr)
{
  return ptr[0] + (ptr[1]<<8);
}



#endif