#include "hid_manager.h"

bool send_hid_report(uint8_t report_id, void const* data, uint16_t len){
    if ( !tud_hid_ready() ) return false;

    return tud_hid_report(report_id, data, len);   
}

bool usb_mounted(void) {
    return tud_mounted();
}

