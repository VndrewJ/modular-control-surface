#pragma once

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/timer.h"

#include "quadrature_encoder.pio.h"

class Encoder
{
    public:
        Encoder(int clk_pin, int dt_pin, int sw_pin);

        // Initialize the encoder drivers and set the pins as inputs with pull-ups
        void init();

        // Read the encoder state, returns the amount of steps since last read
        int_fast8_t read_enc();

        // Read the button state, returns true if the button is pressed
        bool read_sw();

    private:
        // PIO vars
        PIO pio;
        uint sm;                // State Machine
        uint pio_offset;   // Offset of the PIO program in the PIO instruction memory

        // encoder vars
        int clk_pin;
        int dt_pin;
        int sw_pin;
};