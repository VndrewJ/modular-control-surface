#include "encoder.h"

Encoder::Encoder(ENCODER_PARAMS params) 
    : clk_dt_pin(params.clk_dt_pin), 
        sw_pin(params.sw_pin), pio(params.pio), 
        sm(params.sm)
{

    init();
};

void Encoder::init()
{
    // Initialise PIO for encoder
    pio_add_program(pio, &quadrature_encoder_program);
    quadrature_encoder_program_init(pio, sm, clk_dt_pin, 0);
    last_step = quadrature_encoder_get_count(pio, sm);

    // Set the button pin as input with pull-up
    gpio_init(sw_pin);
    gpio_set_dir(sw_pin, GPIO_IN);
    gpio_pull_up(sw_pin);
}

Encoder::Direction Encoder::read_enc()
{
    // Read the encoder state, returns the amount of steps since last read
    int cur_step = quadrature_encoder_get_count(pio, sm);
    int delta = cur_step - last_step;
    int detents = floor_div(delta, 4); // Only count full detents (4 steps per detent)
    last_step += detents * 4; // Only update last_step by the number of full detents we've moved
    return detents > 0 ? Direction::CLOCKWISE : 
        detents < 0 ? Direction::COUNTERCLOCKWISE : 
                    Direction::NONE;
}

bool Encoder::read_sw()
{
    // Read the button state, returns true if the button is pressed
    return !gpio_get(sw_pin);
}

int Encoder::floor_div(int a, int b)
{
    // Floor div helper for hysteresis error in encoder reading
    return a / b - (a % b != 0 && (a ^ b) < 0);
}