#include <M5Atom.h>
#include <BLEDevice.h>
#include "config.h"

RTC_DATA_ATTR static int colorIndex = 0;

RTC_DATA_ATTR static uint8_t sequence;
static BLEServer *pServer;
static BLEAdvertising *pAdvertising;

CRGB changeColor()
{
  if (++colorIndex >= (sizeof(colorMap) / sizeof(colorMap[0])))
    colorIndex = 0;
  return colorMap[colorIndex];
}

void fillLED(CRGB color)
{
  static struct
  {
    uint8_t x;
    uint8_t y;
    CRGB leds[NUM_LEDS];
  } _ledBuffer = {5, 5};

  for (int i = 0; i < NUM_LEDS; i++)
    _ledBuffer.leds[i] = color;
  M5.dis.displaybuff((uint8_t *)&_ledBuffer);
}

void ledOn()
{
  M5.dis.setBrightness(20);
}

void ledOff()
{
  M5.dis.setBrightness(0);
}

static uint8_t brightnessBySigmonid(float x)
{
  x *= 10;                                 // expand the unit interval
  float y = (tanh(x / 2) + 1) / 2;         // sigmoid
  uint8_t brightness = (uint8_t)(y * 100); // map the results to brightness
  return brightness;
}

void flashing(int seconds)
{
  static const int points = 100; // data points
  static const int period = 720; // interval (degree)
  static const int step = period / points;
  static bool mutex = false;

  if (mutex)
    return;

  mutex = true;
  Serial.printf("Flashing  %d seconds\r\n", seconds);
  int _delay = seconds * 1000 / points;
  for (int radian = 270; radian < 270 + period; radian += step)
  {
    float x = sin(radian * PI / 180);            // map to unit interval [-1, 1]
    uint8_t brightness = BRIGHTNESS_FUNCTION(x); // calc brightness
    M5.dis.setBrightness(brightness);
    delay(_delay);
  }
  ledOff();
  mutex = false;
}

void enter_deep_sleep()
{
  Serial.println("Enter deep sleep.");
  delay(1000);
  int value = digitalRead(MOTIONSENSOR_PIN);
  esp_sleep_enable_ext0_wakeup(MOTIONSENSOR_PIN, (value == 0) ? 1 : 0);
  esp_sleep_enable_timer_wakeup(60 * 1000 * 1000);
  esp_deep_sleep_start();
}

void btn_scan(void *arg)
{
  while (1)
  {
    M5.update();
    if (M5.Btn.wasPressed())
    {
      Serial.println("Change Color");
      fillLED(changeColor());
      flashing(FLASHING_INTERVAL);
    }
    delay(1000);
  }
}

void ble_scan(void *arg)
{
  while (1)
  {
    BLEScan *pble_scan = BLEDevice::getScan();
    pble_scan->setActiveScan(false);

    Serial.println("Scan start.");
    BLEScanResults scanResult = pble_scan->start(3);
    for (int i = 0; i < scanResult.getCount(); i++)
    {
      BLEAdvertisedDevice device = scanResult.getDevice(i);
      if (!device.haveManufacturerData())
        continue;

      std::string data = device.getManufacturerData();
      int companyId = data[1] << 8 | data[0];
      if (companyId != BLE_COMPANY_ID || sequence == data[2] || strncmp(&data[3], PROJECT_ID, strlen(PROJECT_ID)))
        continue;

      sequence = data[2];
      int motionStatus = data[3 + strlen(PROJECT_ID)];
      Serial.printf("Device Found. sequence: %d, motion: %d\r\n", sequence, motionStatus);
      if (motionStatus == 1)
        flashing(FLASHING_INTERVAL);
    }
    Serial.println("Scan end.");

    delay(1000);
  }
}

void setup()
{
  M5.begin(true, false, true);

  BLEDevice::init(BLE_DEVICE_NAME);

  fillLED(colorMap[colorIndex]);
  delay(1000);
  ledOff();

  xTaskCreatePinnedToCore(btn_scan, "btn_scan", 4096, NULL, 1, NULL, 0);
  xTaskCreatePinnedToCore(ble_scan, "ble_scan", 4096, NULL, 1, NULL, 0);
}

void loop()
{
}
