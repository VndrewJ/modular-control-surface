#ifndef USB_DESCRIPTORS_H
#define USB_DESCRIPTORS_H

#include "tusb.h"

// Base report IDs where 0 is reserved for the main module. Additional modules iterate off it. 
// I.e Additional button modules would have report ID 0x21, 0x22, etc.
enum {
    REPORT_ID_ENCODER = 0x10,
    REPORT_ID_BUTTON  = 0x20,
};

#endif // USB_DESCRIPTORS_H
