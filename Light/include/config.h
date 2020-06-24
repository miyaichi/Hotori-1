#pragma once

#define PROJECT_ID "HOTORI" // Project Identification ID

#define MOTIONSENSOR_PIN ((gpio_num_t)G32) // Motion sensor PIN No

#define BLE_DEVICE_NAME "Hotori" // Device name
#define BLE_COMPANY_ID 0xffff    // Company ID

// colorMap (tab10)
CRGB colorMap[] = {
    0x1f77b4,
    0xff7f0e,
    0x2ca02c,
    0xd62728,
    0x9467bd,
    0x8c564b,
    0xe377c2,
    0x7f7f7f,
    0xbcbd22,
    0x17becf,
};

#define FLASHING_INTERVAL 10                     // Flashing interval (Second)
#define BRIGHTNESS_FUNCTION brightnessBySigmonid // Brightness function