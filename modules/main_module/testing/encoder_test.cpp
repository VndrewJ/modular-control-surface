#include <stdio.h>

#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "hardware/gpio.h"
#include "lib/encoder.h"

// // I2C defines
// // This example will use I2C0 on GPIO8 (SDA) and GPIO9 (SCL) running at 400KHz.
// // Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
// #define I2C_PORT i2c0
// #define I2C_SDA 8
// #define I2C_SCL 9

// Encoder pins
#define ENC_CLK_DT 0
#define ENC_SW 2
#define ENC_PIO pio0
#define ENC_SM 0


int main()
{
    bool button_state = 0;
    stdio_init_all();
    sleep_ms(2000); // Sleep for a bit to allow the console to initialize

    printf("Initializing encoder...\n");
    Encoder encoder({
        .clk_dt_pin = ENC_CLK_DT,
        .sw_pin = ENC_SW,
        .pio = ENC_PIO,
        .sm = ENC_SM
    });

    printf("Encoder initialized\n");

    // I2C Initialisation. Using it at 400Khz.
    // i2c_init(I2C_PORT, 400*1000);
    
    // gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    // gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    // gpio_pull_up(I2C_SDA);
    // gpio_pull_up(I2C_SCL);
    // For more examples of I2C use see https://github.com/raspberrypi/pico-examples/tree/master/i2c
    
    while (true) {
        Encoder::Direction dir = encoder.read_enc();
        bool button_pressed = encoder.read_sw();

        // Prints if encoder state has changed
        if (dir != Encoder::Direction::NONE) {
            printf("Encoder direction: %d\n", static_cast<int>(dir));
        }

        // Prints if button is pressed
        if (button_pressed != button_state) {
            button_state = button_pressed;
            if (button_pressed) {
                printf("Button pressed!\n");
            } else {
                printf("Button released!\n");
            }
        }

        // 1khz update rate
        sleep_ms(1);
    }
}
