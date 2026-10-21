#include <stdint.h>
#include "UART/usart2.h"

int main(void)
{
    USART2_Init();

    while (1)
    {
        USART2_TransmitString("hello from USART2\r\n");
        for (volatile uint32_t i = 0U; i < 500000U; i++);
    }
}