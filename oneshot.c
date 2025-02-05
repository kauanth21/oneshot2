#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/time.h"

// Definição dos pinos dos LEDs e do botão
#define LED_PIN_BLUE 11
#define LED_PIN_RED 12
#define LED_PIN_GREEN 13
#define BUTTON_PIN 5

bool leds_active = false; // Indica se os LEDs estão ativos

// Função para desligar os LEDs um por um
int64_t turn_off_led_callback(alarm_id_t id, void *user_data) {
    static int led_state = 0;
    
    switch (led_state) {
        case 0:
            gpio_put(LED_PIN_BLUE, 0);
            printf("LED Azul desligado\n");
            break;
        case 1:
            gpio_put(LED_PIN_RED, 0);
            printf("LED Vermelho desligado\n");
            break;
        case 2:
            gpio_put(LED_PIN_GREEN, 0);
            printf("LED Verde desligado\n");
            leds_active = false; // Permite pressionar o botão novamente
            return 0;
    }
    
    led_state++;
    add_alarm_in_ms(3000, turn_off_led_callback, NULL, false);
    return 0;
}

int main() {
    stdio_init_all();
    sleep_ms(500);
    printf("Sistema iniciado!\n");
    
    gpio_init(LED_PIN_BLUE);
    gpio_set_dir(LED_PIN_BLUE, GPIO_OUT);
    gpio_init(LED_PIN_RED);
    gpio_set_dir(LED_PIN_RED, GPIO_OUT);
    gpio_init(LED_PIN_GREEN);
    gpio_set_dir(LED_PIN_GREEN, GPIO_OUT);
    
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);
    
    while (true) {
        if (gpio_get(BUTTON_PIN) == 0 && !leds_active) {
            sleep_ms(50); // Debounce
            if (gpio_get(BUTTON_PIN) == 0) {
                printf("Botão pressionado! Ligando LEDs...\n");
                gpio_put(LED_PIN_BLUE, 1);
                gpio_put(LED_PIN_RED, 1);
                gpio_put(LED_PIN_GREEN, 1);
                leds_active = true;
                
                add_alarm_in_ms(3000, turn_off_led_callback, NULL, false);
            }
        }
        sleep_ms(10);
    }
}
