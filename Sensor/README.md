# Hotori Sensor

センサーの情報を通知するモジュールです。モーションセンサーの情報を取得し、動きを検知すると、BLE(Bluetooth Low Energy)でアドバタイズします。ブロードキャスト通信を使うことで、複数のデバイスに同時に情報を送ることができます。

## Device

[ATOM Matrix](https://m5stack.com/products/atom-matrix-esp32-development-kit) に[PIR モーションセンサー](https://m5stack.com/products/pir-module)を接続しています。

## Build

PlatformIO でビルドしています。必要に応じて platformio.ini を修正してください。

```Ini
[env:m5stick-c]
platform = espressif32
board = m5stick-c
framework = arduino
monitor_speed = 115200
```
