/*  
	Nome: Davi Salomão Soares Corrêa
	Matricula: 180118820
 	Materia: Tópicos especiais em engenharia mecatrônica - T01
  	Trabalho 02: Sinal "Pulse-Width Modulation" (PWM) configurável via código
*/

#include <stdio.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define LED_PIN GPIO_NUM_2  // LED interno (azul)

void app_main() {
    esp_rom_gpio_pad_select_gpio(LED_PIN);
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);
    
    int duty_cycle = 0;
    int direction = 1;  // Direção de incremento do ciclo de trabalho
    int k = 10;         // Multiplicador para ajuste
    while (1) {
        gpio_set_level(LED_PIN, 1);
        vTaskDelay(duty_cycle * k / portTICK_PERIOD_MS);            

        gpio_set_level(LED_PIN, 0);
        vTaskDelay((10 - duty_cycle) * k / portTICK_PERIOD_MS);

        duty_cycle += direction;
        
        if (duty_cycle >= 10 || duty_cycle <= 0) {
            direction *= -1;
        }
    }
} // Este código varia o ciclo de trabalho para controlar a intensidade luminosa

/* 
    Referências:
        [1] out_pin.cpp
        [2] documentação ESP32/FreeRTOS
        [3] código parcialmente construído em aula com Prof. Dr. Jones Yudi
*/
