

//Oled sh1106 Driver on Raspberry Pi written in C++


#include "oled.h"
#include "fonts.h"

static  uint8_t frame[132*64/8];

Oled::Oled(I2C *dev , uint_fast8_t height , uint_fast8_t width): _dev(dev),_width(width) , _height(height)
{
    _pages = (_height + 7) / 8;
    bufsize = 1024;
}

void Oled::init()
{
uint8_t buff[] = {
    0x00,
    0xAE,
    0xD5,
    0x80,
    0xA8,
    (uint8_t)(_height -1),
    0xD3,
    0x00,
    0x40,
    0x8D,
    0x14,
    0x20,
    0x00,
    0xA1,
    0xC8,
    0xDA,
    0x12,
    0x81,
    0xFF,
    0xD9,
    0x22,
    0xDB,
    0x20,
    0xA4,
    0xA6,
    0x2E
};

_dev->Write_Bytes(buff , sizeof(buff) ,0x3c);

RaspiGpio::milisecondDelay(100);

this->clear();
this->display(); 

set_power(true);

}




void Oled::clear(tColor color )
{
 if (color == WHITE)
    memset(frame , 0xFF , 1024);
 else
     memset(frame , 0x00 , 1024);
}



void Oled::clearBlack()
{
    memset(frame , 0x00 , 1024);
}



void Oled::clearWhite()
{
    memset(frame , 0xFF , 1024);
}



void Oled::display()
{
    uint16_t index = 0;
    for(int page = 0 ; page < 8 ; page ++ )
    {

     page = uint_fast16_t(page);
     uint8_t buff[] = {
         0x00,
        (uint8_t) (0xB0 + page),
         0x00,
         0x10,
     };

     _dev->Write_Bytes(buff,sizeof(buff),0x3c);


     uint8_t data[_width +1];
     data[0] = 0x40;

     for (uint_fast8_t column = 0; column < _width ; column ++)
     {
     data[column+1] = frame[index];
     index++;
     }

     _dev->Write_Bytes(data , sizeof(data),0x3c);
    }
}








void Oled::draw_byte(uint_fast8_t x, uint_fast8_t y, uint8_t b, tColor color)
{
    // Invalid position
    if (x >= _width || y >= _height)
    {
        return;
    }

    uint_fast16_t buffer_index = y / 8 * _width + x;

    if (color == WHITE) //write a Byte in white color 
    {
        // If the y position matches a page, then it goes quicker
        if (y % 8 == 0)
        {
            if (buffer_index < bufsize)
            {
                frame[buffer_index] |= b;
            }
        }
        else  //write a byte in black color
        {
            uint16_t w = (uint16_t) b << (y % 8);
            if (buffer_index < bufsize)
            {
                frame[buffer_index] |= (w & 0xFF);
            }
            uint16_t buffer_index2 = buffer_index + _width;
            if (buffer_index2 < bufsize)
            {
                frame[buffer_index2] |= (w >> 8);
            }
        }
    }
    else
    {
        // If the y position matches a page, then it goes quicker
        if (y % 8 == 0)
        {
            if (buffer_index < bufsize)
            {
                frame[buffer_index] &= ~b;
            }
        }
        else
        {
            uint16_t w = (uint16_t) b << (y % 8);
            if (buffer_index < bufsize)
            {
                frame[buffer_index] &= ~(w & 0xFF);
            }
            uint16_t buffer_index2 = buffer_index + _width;
            if (buffer_index2 < bufsize)
            {
                frame[buffer_index2] &= ~(w >> 8);
            }
        }
    }
    return;
}


void Oled::draw_bytes(uint_fast8_t x, uint_fast8_t y,  uint8_t* data, uint_fast8_t size, tSize scaling, tColor color)
{
    for (uint_fast8_t column = 0; column < size; column++)
    {
        uint8_t b;
       
            b = pgm_read_byte(data);
        
        data++;
        if (scaling == DOUBLE_SIZE)
        {
            // Stretch vertically
            uint16_t w = 0;
            for (uint_fast8_t bit = 0; bit < 7; bit++)
            {
                if (b & (1 << bit))
                {
                    uint_fast8_t pos = bit << 1;
                    w |= ((1 << pos) | (1 << (pos + 1)));
                }
            }

            // Output 2 times to strech hozizontally            
            draw_byte(x, y, w & 0xFF, color);
            draw_byte(x, y + 8, (w >> 8), color);
            x++;
            draw_byte(x, y, w & 0xFF, color);
            draw_byte(x, y + 8, (w >> 8), color);
            x++;
        }
        else // NORMAL_SIZE
        {
            draw_byte(x++, y, b, color);
        }
    }

}



size_t Oled::draw_character(uint_fast8_t x, uint_fast8_t y, char c, tSize scaling, tColor color)
{
    // Invalid position
    if (x >= _width || y >= _height || c < 32)
    {
        return 0;
    }

    // Remap extended Latin1 character codes
    switch ((unsigned char) c)
    {
        case 252 /* u umlaut */:
            c = 127;
            break;
        case 220 /* U umlaut */:
            c = 128;
            break;
        case 228 /* a umlaut */:
            c = 129;
            break;
        case 196 /* A umlaut */:
            c = 130;
            break;
        case 246 /* o umlaut */:
            c = 131;
            break;
        case 214 /* O umlaut */:
            c = 132;
            break;
        case 176 /* degree   */:
            c = 133;
            break;
        case 223 /* szlig    */:
            c = 134;
            break;
    }

    uint16_t font_index = (c - 32)*6;

    // Invalid character code/font index
    if (font_index >= sizeof (oled_font6x8))
    {
        return 0;
    }

    draw_bytes(x, y, &oled_font6x8[font_index], 6, scaling, color);
    return 1;
}







void Oled::set_power(bool enable)
{

   uint8_t buffEnable[] = {0x00,0x8D,0x14,0xAF};
   uint8_t buffDisable[] ={0x00,0xAE,0x8D,0x10};

    if (enable)
      _dev->Write_Bytes(buffEnable,sizeof(buffEnable),0x3c);
    
  
    else
      _dev->Write_Bytes(buffDisable,sizeof(buffDisable),0x3c);

}





void Oled::text(uint_fast8_t x, uint_fast8_t y, const char* s, tSize scaling, tColor color)
{
        while (*s)
    {
        draw_character(x, y, *s, scaling, color);
        if (scaling == DOUBLE_SIZE)
        {
            x += 12;
        }
        else // NORMAL_SIZE
        {
            x += 6;
        }
        s++;
}

}


#if 0
int main()
{

    I2C *_dev = new I2C(1);
    Oled Display(_dev);
    RaspiGpio::milisecondDelay(100);
    std::cout<<"begin init" << std::endl;
    Display.init();
    std::cout<<"end init" << std::endl;
    RaspiGpio::milisecondDelay(2000);

    while (1)
    {
        std::cout<<"begin clear" << std::endl;
        Display.text(4,2,"Hallo");
        Display.display();
    }
    
    
    
    return 0;
}
#endif
