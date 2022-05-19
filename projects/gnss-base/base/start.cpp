#include <unistd.h>
#include "oled.h"
#include "fonts.h"

int main()
{
    I2C* i2c1 = new I2C(1);
    Oled lcd(i2c1);
    sleep(0.1);

    lcd.init();
    sleep(0.1);

    lcd.text(0, 26, "Stopped!", Oled::DOUBLE_SIZE);
    lcd.display();

   return 0;
}
