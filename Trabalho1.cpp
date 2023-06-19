/*  
   Nome: Davi Salomão Soares Corrêa
   Matrícula: 180118820
   Matéria: Tópicos especiais em engenharia mecatrônica - T01
   Trabalho 1: Contador com atraso e inversão do sentido de contagem
*/

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

int counter = 0;
int direction = 1;

void count()
{
    counter += direction;
    printf("%d\n", counter);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
}

void reverse_direction()
{
    direction = -direction;
}

void app_main(void)
{
    char c = 0;
    while (1)
    {
        c = getchar();
        if (c != 0xff)
        {
            if (c != '\n')
            {
                printf("%c\n", c);
                reverse_direction();
            }
        }
        count();
    }
}

/* 
   Referências:
   [1] serial_get.cpp
   [2] Documentação ESP32/FreeRTOS
*/
