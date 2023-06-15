/*  
	Nome: Davi Salomão Soares Corrêa
	Matricula: 180118820
 	Materia: Tópicos especiais em engenharia mecatrônica - T01
  	Trabalho 01: contador delay com inversão do sentido de contagem
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
        if (c != 0xff)
        {
            c = getchar();
            if (c != '\n')
            {
                str[strlen(str)] = c;
                printf("%c", c);
                reverse_dir();
            }
            vTaskDelay(100 / portTICK_PERIOD_MS);
        }
        count();
    }
}

/* 
    Referências:
        serial_get.cpp
        documentação ESP32/FreeRTOS
*/