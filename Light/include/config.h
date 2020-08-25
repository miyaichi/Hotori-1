#pragma once

#define PROJECT_ID "HOTORI" // Project Identification ID

#define MOTIONSENSOR_PIN ((gpio_num_t)G32) // Motion sensor PIN No

#define BLE_DEVICE_NAME "Hotori" // Device name
#define BLE_COMPANY_ID 0xffff    // Company ID

// colorMap (tab10)
CRGB colorMap[] = {
    0x1f77b4, // tab:blue
    0xff7f0e, // tab:orange
    0x2ca02c, // tab:green
    0xd62728, // tab:red
    0x9467bd, // tab:purple
    0x8c564b, // tab:brown
    0xe377c2, // tab:pink
    0x7f7f7f, // tab:gray
    0xbcbd22, // tab:olive
    0x17becf, // tab:cyan
};

#define FLASHING_INTERVAL 10                     // Flashing interval (Second)
#define BRIGHTNESS_FUNCTION brightnessBySigmonid // Brightness function