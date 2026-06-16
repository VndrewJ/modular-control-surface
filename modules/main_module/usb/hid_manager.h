#ifndef HID_MANAGER_H
#define HID_MANAGER_H

#include <stdint.h>

#include "usb_descriptors.h"
#include "module_manager.h"

bool usb_mounted(void);

bool send_hid_report(uint8_t report_id, void const* data, uint16_t len);


#endif // HID_MANAGER_H

