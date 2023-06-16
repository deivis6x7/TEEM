/*  
	Nome: Davi Salomão Soares Corrêa
	Matrícula: 180118820
 	Matéria: Tópicos especiais em engenharia mecatrônica - T01
  	Trabalho 1: Contador delay com inversão do sentido de contagem
*/

#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

int counter = 0;
int direction = 1;

void count()
{
    counter = counter + direction;
    printf("%d\n", counter);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
}

void reverse_dir()
{
    direction = -direction;
}

void app_main(void)
{
    char c = 0;
    char str[100];
    memset(str, 0, sizeof(str));
    while (1)
    {
        c = getchar();
        if (c != 0xff)
        {
            if (c != '\n')
            {
                str[strlen(str)] = c;
                printf("%c\n", c);
                reverse_dir();
            }
        }
        count();
    }
}

/* 
    Referências:
        [1] serial_get.cpp
        [2] documentação ESP32/FreeRTOS
*/