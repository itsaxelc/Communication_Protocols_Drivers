/*
#include <stdint.h>

#include "i2c1.h"

volatile I2C_Status g_status;
volatile uint8_t    g_id;

#include "lcd1602.h"

int main(void)
{
    // Initialisation de I2C1 
    I2C1_Init(I2C1_PINS_PB6_PB7);

    // Initialisation du LCD1602
    LCD1602_Init();

    // Première ligne
    LCD1602_SetCursor(0, 0);
    LCD1602_WriteString("HeLLoCEDRIC");

    // Deuxième ligne
    LCD1602_SetCursor(1, 0);
    LCD1602_WriteString("BOARD:L476");

    while (1)
    {
    }
}
*/
#include "UART/usart2.h"
#include <stdint.h>

int main(void)
{
    USART2_Init();

    while (1)
    {
        USART2_TransmitString("hello Get out of my fucking eyes man\r\n");
        for (volatile uint32_t i = 0U; i < 500000U; i++);
    }
}
