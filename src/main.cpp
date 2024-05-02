#include <stdio.h>
#include "pico/stdlib.h"
#include <hardware/gpio.h>
#include <hardware/uart.h>
#include "crc.h"

#define RS485_RX_PIN  21
#define RS485_TX_PIN  20

volatile bool ledState = true;

int main() {
    stdio_init_all();

    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
    gpio_put(PICO_DEFAULT_LED_PIN, 1);

    uart_init(uart1, 38400);
    gpio_set_function(RS485_RX_PIN, GPIO_FUNC_UART);
    gpio_set_function(RS485_TX_PIN, GPIO_FUNC_UART);

    

    while (true) {
        // Wait for a null bute
        uint8_t byte;
        do { uart_read_blocking(uart1, &byte, 1); }
        while (byte);

        gpio_put(PICO_DEFAULT_LED_PIN, 0);
        uint64_t timestamp = time_us_64();

        // Read the destination
        uint8_t dest;
        uart_read_blocking(uart1, &dest, 1);

        // Print header
        uint32_t us = timestamp % 1000000;
        uint32_t s = timestamp / (uint64_t)1000000;
        uint32_t m = s / 60;
        uint32_t h = m / 60;
        printf("%c %02d:%02d:%02d.%06d ", (dest == 0x05)?'>':'<', h%24, m%60, s%60, us);
        
        // Read 0x7E
        uart_read_blocking(uart1, &byte, 1);
        //printf("7E ");

        // Read data until next 0x7E
        while (true) {
            uart_read_blocking(uart1, &byte, 1);
            if (byte == 0x7E) { break; }
            printf("%02X", byte);
        }
        //printf("7E ");
        printf("\n");

        gpio_put(PICO_DEFAULT_LED_PIN, 1);
    }
    return 0;
}