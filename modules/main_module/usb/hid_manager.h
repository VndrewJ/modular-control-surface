#ifndef HID_MANAGER_H
#define HID_MANAGER_H

#include <stdint.h>

#include "usb_descriptors.h"
#include "module_manager.h"

#ifdef __cplusplus
extern "C" {
#endif

// Simple check for if the USB is mounted
bool usb_mounted(void);


/*
Sends HID report to pc, returns true if successful.
Requires a report struct of chosen peripheral. See module_manager.h for report structure
*/ 
bool send_hid_report(uint8_t report_id, void const* data, uint16_t len);

#ifdef __cplusplus
}
#endif

#endif // HID_MANAGER_H

