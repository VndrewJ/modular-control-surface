#include "hid_manager.h"

// Structure definitions for encoder and button reports
typedef struct encoder_report_t{
    int8_t delta;
    uint8_t button;
} encoder_report_t;

typedef struct button_report_t{
    uint8_t button;
} button_report_t;

// Private function for sending HID reports
static void send_hid_report(uint8_t report_id, void const* data, uint16_t len);

bool usb_mounted(void) {
    return tud_mounted();
}

