#include"gpio.h"
std::vector<int> RaspiGpio::Pins;

RaspiGpio::RaspiGpio(int pin , int type ): m_pin(pin) , m_type(type)
{

     this->ExportPin();
     sleep(1); 
     this->DirectionPin(type);
     sleep(1); 

     Pins.push_back(m_pin);


}


int RaspiGpio::ExportPin()
{

char buffer[MAX_BUFFER]; 
std::ofstream myStream ;
myStream.open("/sys/class/gpio/export" , std::ios::app); 
int byte = snprintf(buffer , MAX_BUFFER , "%d" , m_pin); 

if ( myStream)
{
    myStream<<buffer ; 
    myStream.close(); 
}

else
{
     perror("cannot open the export file Export"); 
}


return 0 ; 

}


int UnexportPin(int pin)
{
    
char buffer[MAX_BUFFER]; 
std::ofstream myStream ;
myStream.open("/sys/class/gpio/unexport" , std::ios::app); 
int byte = snprintf(buffer , MAX_BUFFER , "%d" , pin); 

if ( !myStream)
{
    perror("Cannot Open the File for Export"); 
}

myStream<<buffer ; 
myStream.close(); 

return 0 ; 
}



int RaspiGpio::DirectionPin(int typ) 
{

char path[MAX_BUFFER];
snprintf(path , MAX_BUFFER , "/sys/class/gpio/gpio%d/direction" , m_pin);
std::string path2 =path; 
std::ofstream myStream(path2.c_str() ); 
if(myStream)
{
switch (typ)
{
case IN:
   myStream<<"in";    
    break;

case OUT : 
myStream<<"out"; 
break;

default: 
 perror("Invalid Type");
    break;
}
}



else {perror("cannot open file direction "); std::cout<<"gpio number : " << m_pin << std::endl; }

myStream.close(); 
return 0 ; 
}



int RaspiGpio::digitalReadPin() const 
{
    char path[MAX_BUFFER];
    char result[MAX_BUFFER];
    int bytes= snprintf(path , MAX_BUFFER ,"/sys/class/gpio/gpio%d/value" , m_pin); 
    std::string path2 = path ; 
    std::ifstream myStream(path2.c_str()); 
   if ( myStream.read(result , bytes)) 
   {
      
       return atoi(result);
   }

   perror("cannot read gpio values"); 
   return EXIT_FAILURE; 
}


int RaspiGpio::digitalWritePin(int value)
{
char path[MAX_BUFFER];
snprintf(path , MAX_BUFFER , "/sys/class/gpio/gpio%d/value" , m_pin); 
std::string path2=path;
std::ofstream myStream(path2.c_str() , std::ios::app ); 
switch (value)
{
case LOW:
 myStream<<"0";
    
    break;

case HIGH : 
myStream<<"1";
break;

default:
perror("invalid type  should LOW 0 OR HIGH 1");
    break;
}
myStream.close(); 
return 0 ;
}



 void RaspiGpio::CleanPin()
 {
    for(int i (0) ; i < Pins.size() ; i++)
    {
     UnexportPin(Pins[i]);
     sleep(1);
    }
     
      
 }



int RaspiGpio::milisecondDelay(int millisecond)
{
    struct timespec ts;
    ts.tv_sec=millisecond / 1000 ; //number of sec in the given integer
    ts.tv_nsec=(millisecond % 1000 ) * 1000000L;  //number of microsecond in the given integer :: exemple (100 % 1000) = 100 . 
    int err=nanosleep(&ts , (struct timespec*)NULL ); 
    return err;   
}



/*I2C +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/



I2C::I2C(char adapter):  m_adaptaer(adapter)
{
    char path[100];
    snprintf(path , 100 , "/dev/i2c-%d" , m_adaptaer);
    do {m_file = ::open(path,O_RDWR );} while (m_file < 1);
}


I2C::~I2C()
{
  ::close(m_file);
}


bool I2C::WriteOneByte_ReadBuff(uint8_t Byte , uint8_t *buff , int length, char m_addr)
{
    int ios ,wr,rd;
    uint8_t buffer[1] = {Byte};
    do { ios =::ioctl(m_file , I2C_SLAVE , m_addr);  if (ios == -1) { perror("ioctl from Write One Byte i2c: ");}} while(ios == -1);
    do { wr =::write(m_file,buffer,1); if (wr != 1) { perror("write from readbyte: ");}} while (wr != 1); 
    do {rd =::read(m_file,buff,length); if(rd != length) perror("read from Writeone Byte readBuff");} while(rd != length);
 return true;
}

bool I2C::ReadNowByte(uint8_t *buffer , char m_addr)
 
 {
    
    int ios; 
    int i;
    int wr;
    do { ios =::ioctl(m_file , I2C_SLAVE , m_addr);  if (ios == -1) { perror("ioctl from readbytenow i2c: ");}} while(ios == -1);
    RaspiGpio::milisecondDelay(200);
    do {  i =::read(m_file , buffer , sizeof(buffer));if ( i != sizeof(buffer)) {perror("read from readbytenow: ");}} while (i != sizeof(buffer));
    
   return true; 
      
 }



uint8_t I2C::ReadBytes(const char ByteToRead, char m_addr)
{
    char buffer[10]={0};
    int ios; 
    int i;
    int wr ; 
    buffer[0]=ByteToRead;
      
    do { ios =::ioctl(m_file , I2C_SLAVE , m_addr); if (ios == -1) { perror("ioctl from readbyte i2c: ");}} while(ios == -1);
    RaspiGpio::milisecondDelay(50); 

   
    do { wr =::write(m_file,buffer,1); if (wr != 1) { perror("write from readbyte: ");}} while (wr != 1); // the pointer of i2c will point to the last writen byte : that is why we write the adress of the byte we want to read .
    
    RaspiGpio::milisecondDelay(50); 
    do {  i =::read(m_file , buffer , 1); if ( i != 1) {perror("read from readbyte: ");}} while (i !=1);  
    RaspiGpio::milisecondDelay(50); 
  return (uint8_t) buffer[0];
}





bool I2C::Write3Byte(uint8_t MSB , uint8_t LSB , uint8_t length, char m_addr)
{
    uint8_t buffer[3] = {MSB , LSB , length};
    int ios;
    int wr;
   do { ios =::ioctl(m_file , I2C_SLAVE , m_addr); if (ios == -1) { perror("ioctl from write i2c: ");}} while ( ios == -1);
   RaspiGpio::milisecondDelay(50); 

   do { wr = ::write(m_file , buffer , 3); if ( wr != 3 ) {perror("write write");}}while (wr != 3); 
   RaspiGpio::milisecondDelay(50); 
     
    
  return true;
}



bool I2C::Write_Bytes(__u8 *buffer , int length, char m_addr)
{
    int ios;
    int wr;
    do { ios =::ioctl(m_file , I2C_SLAVE , m_addr); if (ios == -1) { perror("ioctl from write i2c: ");}} while ( ios == -1);
   RaspiGpio::milisecondDelay(50); 

    do { wr = ::write(m_file , buffer , length); if ( wr != length ) {perror("write write");}}while (wr != length); 
   RaspiGpio::milisecondDelay(50); 
     
    
  return true;

}



 bool I2C::i2cWrRd(__u8 *buffewr , __u8 *result , int send_length , int read_length, char m_addr) // this for write reg adress and read without a stop bit between write and read that mean the data train is : Start | Write | ADDR | ACK | Start ( another start in place of stop with a normal write and read request.) | Read | ACK | Stop 

 {
   struct i2c_msg msgs[2];
   struct i2c_rdwr_ioctl_data msgst[1];
  
   msgs[0].addr = m_addr; 
   msgs[0].flags = 0; 
   msgs[0].len = send_length; 
   msgs[0].buf = buffewr; 

    msgs[1].addr = m_addr;
    msgs[1].flags = I2C_M_RD | I2C_M_NOSTART;
    msgs[1].len = read_length;
    msgs[1].buf = result;

    msgst[0].msgs = msgs;
    msgst[0].nmsgs = 2;

   int i; 

   do {i = ioctl(m_file, I2C_RDWR, &msgst); if (i < 0) {perror("ioctl i2cWrRD : ");} } while ( i < 0); 

 

   return 0; 




 }


int I2C::WriteByte(char command , char reg, char m_addr)
{
 
int ios;
int wr;
char buffer[2];
 
buffer[0]= reg;
buffer[1]=command; 

do { ios =::ioctl(m_file , I2C_SLAVE , m_addr); if (ios == -1) { perror("ioctl from write i2c: ");}} while ( ios == -1);
RaspiGpio::milisecondDelay(50); 

do { wr = ::write(m_file , buffer , 2); if ( wr != 2 ) {perror("write write");}}while (wr != 2); 
RaspiGpio::milisecondDelay(50); 


return 0;

}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/



/*SPI+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/



Spi::Spi()

{
    char path[MAX_BUFFER]; 
    snprintf(path , MAX_BUFFER , "/dev/spidev0.0"); 

     std::cout<<"controler begin open" << std::endl; 
    do {_fd = ::open(path , O_RDWR);} while(_fd < 0); 
     std::cout<<"controler end open" << std::endl;    
}





bool Spi::transfer(uint8_t *rxData , const uint8_t *txData )

{
  
struct spi_ioc_transfer msg[1] = {};
memset(msg , 0 , sizeof msg); 

if (!rxData || !txData) { return false ;}

msg[0].tx_buf = (uint64_t) txData;
msg[0].rx_buf = (uint64_t) rxData; 
msg[0].len = 2; 
msg[0].speed_hz = 1000000; 
msg[0].delay_usecs = 0;
msg[0].bits_per_word = 8; 

uint8_t mode = SPI_MODE_3; 


int r = ioctl(_fd , SPI_IOC_WR_MODE  , &mode);  if ( r < 0) { perror("Error Write in ioctl Tranfer function"); return false; }


r = ioctl(_fd , SPI_IOC_MESSAGE(1) , &msg); 


if ( r ==-1) { perror("ERROR ioctl MESSAGE(1)");  return false;}

return true; 

}















Spi::~Spi() 
{
    int cd;

    do { cd = ::close(_fd); } while ( cd < 0); 
}







/*


SPI::SPI(int devicePort , int speed ,int bitperworld )
{
 _speed = speed; 
 _bitperworld = bitperworld; 
char path[MAX_BUFFER]; 
snprintf(path,MAX_BUFFER,"/dev/spidev0.%d" , devicePort);
do {_spi_fd= ::open(path , O_RDWR);} while(_spi_fd < 1);  
}



uint16_t SPI::transfer(uint16_t value)
{
uint16_t _rxData =0;
static struct spi_ioc_transfer tr;
memset(&tr , 0, sizeof(tr));

tr.bits_per_word= _bitperworld; 

//tr.speed_hz = _speed;
tr.len = 1;
uint8_t mode = SPI_MODE_3;
int rd , rc , a , b , c , x; 
tr.rx_buf= (unsigned long) &_rxData;
tr.tx_buf= (unsigned long) &value; 
//std::cout<<"transmiision data : " << (int)value << std::endl;
//std::cout<<"received data before transsmission : " << (int) _rxData << std::endl;
//int spi_bitsPerWord = 8;

std::cout<<"here1"<< std::endl ; 
do {a =ioctl(_spi_fd, SPI_IOC_WR_MODE, &mode);}while( a < 0);
std::cout<<"here2"<< std::endl ; 

std::cout<<"here1"<< std::endl ; 
do {b = ioctl(_spi_fd, SPI_IOC_WR_BITS_PER_WORD, &_bitperworld);}while(b < 0); 
std::cout<<"here1"<< std::endl ; 

std::cout<<"here1"<< std::endl ; 
do {c=ioctl(_spi_fd, SPI_IOC_WR_MAX_SPEED_HZ, &_speed); }while(c <0);
std::cout<<"here1"<< std::endl ; 

std::cout<<"here1"<< std::endl ; 
do {rd = ioctl( _spi_fd , SPI_IOC_RD_MODE, &mode);}while ( rd < 0);
std::cout<<"here1"<< std::endl ; 

std::cout<<"here1"<< std::endl ; 
do {x = ioctl(_spi_fd, SPI_IOC_RD_MAX_SPEED_HZ, &_speed);}while(x < 0); 
std::cout<<"here1"<< std::endl ; 

std::cout<<"here1"<< std::endl ; 

do { rc = ioctl( _spi_fd, SPI_IOC_MESSAGE(1), &tr); } while ( rc < 0);

std::cout<<"here2"<< std::endl ; 
//std::cout<<"received data after transsmission : " << (int)_rxData << std::endl;
return _rxData; 
}








/*


uint8_t SPI::transfer(uint8_t value)
{
unsigned char _rxData =0;
static struct spi_ioc_transfer tr;
memset(&tr , 0, sizeof(tr));

tr.bits_per_word= _bitperworld; 

//tr.speed_hz = _speed;
tr.len = 1;
uint8_t mode = SPI_MODE_3;
int rd , rc , a , b , c , x; 
tr.rx_buf= (unsigned long) &_rxData;
tr.tx_buf= (unsigned long) &value; 
//std::cout<<"transmiision data : " << (int)value << std::endl;
//std::cout<<"received data before transsmission : " << (int) _rxData << std::endl;
int spi_bitsPerWord = 8;
do {a =ioctl(_spi_fd, SPI_IOC_WR_MODE, &mode);}while( a < 0);
do {b = ioctl(_spi_fd, SPI_IOC_WR_BITS_PER_WORD, &spi_bitsPerWord);}while(b < 0); 
do {c=ioctl(_spi_fd, SPI_IOC_WR_MAX_SPEED_HZ, &_speed); }while(c <0);
do {rd = ioctl( _spi_fd , SPI_IOC_RD_MODE, &mode);}while ( rd < 0);
do {x = ioctl(_spi_fd, SPI_IOC_RD_MAX_SPEED_HZ, &_speed);}while(x < 0); 
std::cout<<"here1"<< std::endl ; 

do { rc = ioctl( _spi_fd, SPI_IOC_MESSAGE(1), &tr); } while ( rc < 0);

std::cout<<"here2"<< std::endl ; 
//std::cout<<"received data after transsmission : " << (int)_rxData << std::endl;
return _rxData; 
}




SPI::~SPI() 
{
    int cd;

    do { cd = ::close(_spi_fd); } while ( cd < 0); 
}


*/










