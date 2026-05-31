#pragma once

#include <stdio.h>
#include <algorithm>
#include <climits>

#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/timer.h"

#include "quadrature_encoder.pio.h"

struct ENCODER_PARAMS{
    int clk_dt_pin;         // CLK and DT pins are consecutive so only need to specify CLK pin
    int sw_pin;

    PIO pio;
    uint sm;                // State Machine    
    //uint pio_offset;      // Dont need this offset pin as only using 1 PIO program
};

class Encoder
{
    public:
        enum Direction {
            CLOCKWISE = 1,
            COUNTERCLOCKWISE = -1,
            NONE = 0
        };

        Encoder(ENCODER_PARAMS params);

        // Initialize the encoder drivers and set the pins as inputs with pull-ups
        void init();

        // Read the encoder state, returns the amount of steps since last read
        Direction read_enc();

        // Read the button state, returns true if the button is pressed
        bool read_sw();

        // Floor div helper for hysteresis error in encoder reading
        int floor_div(int a, int b);

    private:
        // PIO vars
        PIO pio;
        uint sm;                // State Machine
        //uint pio_offset;      // Dont need this offset pin as only using 1 PIO program

        // encoder vars
        int clk_dt_pin;
        int sw_pin;
        int last_step;
};