#ifndef HID_MANAGER_H
#define HID_MANAGER_H

#include <stdint.h>

#include "usb_descriptors.h"

bool usb_mounted(void);

void send_encoder_report(uint8_t report, int8_t delta, uint8_t button);
void send_button_report(uint8_t report, uint8_t button);


#endif // HID_MANAGER_H

