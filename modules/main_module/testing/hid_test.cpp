/*
HID Test, tests the HID connection to a PC with the previous encoder tests.
*/
#include <stdio.h>
#include <stdint.h>

#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "hardware/gpio.h"
#include "lib/encoder/encoder.h"
#include "usb/hid_manager.h"       

// Encoder pins
#define ENC_CLK_DT 0
#define ENC_SW 2
#define ENC_PIO pio0
#define ENC_SM 0

// Main module report ID
#define MAIN_REPORT_ID (REPORT_ID_ENCODER | 0x01)

struct encoder_report_t{
    int8_t delta;
    uint8_t button;
};


int main()
{
    encoder_report_t report;
    bool button_state = 0;

    stdio_init_all();
    tusb_init();

    printf("Initializing encoder...\n");
    Encoder encoder({
        .clk_dt_pin = ENC_CLK_DT,
        .sw_pin = ENC_SW,
        .pio = ENC_PIO,
        .sm = ENC_SM
    });

    printf("Encoder initialized\n");

    // Wait for USB to be mounted and ready
    while(!usb_mounted()) {
        tud_task(); // Handle USB events
        sleep_ms(100);
    }
    
    while (true) {

        tud_task(); // Handle USB events
        report.delta = static_cast<int8_t>(encoder.read_enc());
        report.button = static_cast<uint8_t>(encoder.read_sw());

        // Sends if encoder state has changed
        if (report.delta != 0) {
            send_hid_report(MAIN_REPORT_ID, &report, sizeof(report));
        }

        // Prints if button is pressed
        if (report.button != button_state) {
            button_state = report.button;
            send_hid_report(MAIN_REPORT_ID, &report, sizeof(report));
        }
        sleep_ms(1);
        tud_hid_ready(); // Ensure the report is sent before the next loop
    }
}
