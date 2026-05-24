#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "hardware/gpio.h"

// I2C defines
// This example will use I2C0 on GPIO8 (SDA) and GPIO9 (SCL) running at 400KHz.
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
#define I2C_PORT i2c0
#define I2C_SDA 8
#define I2C_SCL 9

// Encoder pins
#define ENC_CLK 0
#define ENC_DT 1
#define ENC_SW 2

void init_encoder_pins()
{
    // Initialize each encoder pin
    gpio_init(ENC_CLK);
    gpio_init(ENC_DT);
    gpio_init(ENC_SW);
    
    // Set as inputs
    gpio_set_dir(ENC_CLK, GPIO_IN);
    gpio_set_dir(ENC_DT, GPIO_IN);
    gpio_set_dir(ENC_SW, GPIO_IN);

    // Pull up the pins (encoder usually pulls low when active)
    gpio_pull_up(ENC_CLK);
    gpio_pull_up(ENC_DT);
    gpio_pull_up(ENC_SW);
}


int main()
{
    stdio_init_all();
    sleep_ms(2000); // Sleep for a bit to allow the console to initialize

    printf("Initializing encoder pins...\n");
    init_encoder_pins();
    printf("Encoder pins initialized\n");

    // I2C Initialisation. Using it at 400Khz.
    // i2c_init(I2C_PORT, 400*1000);
    
    // gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    // gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    // gpio_pull_up(I2C_SDA);
    // gpio_pull_up(I2C_SCL);
    // For more examples of I2C use see https://github.com/raspberrypi/pico-examples/tree/master/i2c

    printf("Starting encoder monitoring...\n");
    
    while (true) {
        // Read the encoder state
        bool clk_state = gpio_get(ENC_CLK);
        bool dt_state = gpio_get(ENC_DT);
        bool sw_state = gpio_get(ENC_SW);

        // Print the encoder state to the console
        printf("CLK: %d, DT: %d, SW: %d\n", clk_state, dt_state, sw_state);

        sleep_ms(100); // Sleep for a bit to avoid flooding the console
    }
}
