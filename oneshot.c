#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/time.h"

// Definição dos pinos dos LEDs e do botão
#define LED_PIN_BLUE 11
#define LED_PIN_RED 12
#define LED_PIN_GREEN 13
#define BUTTON_PIN 5

bool cycle_active = false; // Indica se o ciclo está rodando
int led_state = 0; // Controla qual LED está sendo desligado

// Callback do temporizador para desligar os LEDs um por um
int64_t led_cycle_callback(alarm_id_t id, void *user_data) {
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
            cycle_active = false; // Desativa o ciclo, esperando nova ativação
            printf("Todos os LEDs desligados. Pressione o botão para reiniciar o ciclo.\n");
            return 0;
    }

    led_state++;
    add_alarm_in_ms(3000, led_cycle_callback, NULL, false); // Reprograma o temporizador
    return 0;
}

void start_led_cycle() {
    printf("Iniciando ciclo dos LEDs!\n");
    gpio_put(LED_PIN_BLUE, 1);
    gpio_put(LED_PIN_RED, 1);
    gpio_put(LED_PIN_GREEN, 1);
    led_state = 0;
    cycle_active = true;
    
    // Iniciar o primeiro desligamento após 3 segundos
    add_alarm_in_ms(3000, led_cycle_callback, NULL, false);
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
        if (gpio_get(BUTTON_PIN) == 0 && !cycle_active) {
            sleep_ms(50); // Debounce
            if (gpio_get(BUTTON_PIN) == 0) {
                start_led_cycle(); // Inicia um novo ciclo quando o botão for pressionado
            }
        }
        sleep_ms(10);
    }
}
