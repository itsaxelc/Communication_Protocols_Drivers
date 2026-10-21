#include <stdint.h>
#include "i2c1.h"
#include "lcd1602.h"

int main(void)
{
    I2C1_Init(I2C1_PINS_PB6_PB7);
    LCD1602_Init();

    LCD1602_SetCursor(0, 0);
    LCD1602_WriteString("Hello");

    LCD1602_SetCursor(1, 0);
    LCD1602_WriteString("BOARD:L476");

    while (1) { }
}