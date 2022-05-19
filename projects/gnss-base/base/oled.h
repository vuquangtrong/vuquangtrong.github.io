#ifndef OLED_H
#define OLED_H

#include "gpio.h"

class Oled
{

public:
    /** Possible colors for drawing */
    enum tColor { BLACK, WHITE };

    /** Filling mode */
    enum tFillmode { HOLLOW, SOLID };

    /** Supported text sizes. Normal=6x8 pixels, Double=12x16 pixels */
    enum tSize { NORMAL_SIZE, DOUBLE_SIZE };

    /** Scroll effects supported by the display controller, note that there is no plain vertical scrolling */
    enum tScrollEffect { NO_SCROLLING=0, HORIZONTAL_RIGHT=0x26, HORIZONTAL_LEFT=0x27, DIAGONAL_RIGHT=0x29, DIAGONAL_LEFT=0x2A };


Oled(I2C *dev, uint_fast8_t height = 64 , uint_fast8_t width = 132);
void init();
void display();
void text(uint_fast8_t x, uint_fast8_t y, const char* s, tSize scaling = NORMAL_SIZE, tColor color =WHITE);
void clear(tColor color =BLACK);
void clearBlack();
void clearWhite();
void set_power(bool enable);
private:

void   draw_byte(uint_fast8_t x, uint_fast8_t y, uint8_t b, tColor color);
void   draw_bytes(uint_fast8_t x, uint_fast8_t y,  uint8_t* data, uint_fast8_t size, tSize scaling, tColor color);
size_t draw_character(uint_fast8_t x, uint_fast8_t y, char c, tSize scaling, tColor color);
I2C *_dev;
const uint_fast8_t _width;
const uint_fast8_t _height;
 uint_fast8_t _pages;
 uint_fast16_t bufsize;
};





#endif
