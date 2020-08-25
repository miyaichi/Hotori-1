# Hotori Sensor

センサーの情報を通知するモジュールです。モーションセンサーの情報を取得し、動きを検知すると、明かりを点滅させるとともに、BLE(Bluetooth Low Energy)でアドバタイズします。ブロードキャスト通信を使うことで、複数のデバイスに同時に情報を送ることができます。

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

## BLE Device

config.h でデバイス名と企業 ID を定義しています。センサーデバイスの識別は企業 ID で行っています。

```cpp
#define BLE_DEVICE_NAME "Hotori" // Device name
#define BLE_COMPANY_ID 0xffff    // Company ID
```

## Color Pallet

ボタンを押すと点滅する色がサイクリックに変わりますが、色のパレットは config.h に以下のように定義されています。必要に応じて修正してください。

```cpp
RTC_DATA_ATTR static int colorIndex;
CRGB colors[] = {
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
```

## Flashing

明かりの点滅は以下のようにコントロールされています。

- x = \sin\theta \theta : [270^\circ - 990^\circ] の区間で 100 のデータポイントを生成します。
- x から LED の明るさ(0-100)を計算し、設定します。
- 点滅サイクル(10 秒)で 100 回明るさを変えられるよう、ディレイします。

明るさの計算にはシグモイド関数を使った brightnessByLinear() を実装しています。config.h の点滅サイクルや明るさの計算ロジックを変えることで、点滅の感じを変えることができます。

```cpp
#define FLASHING_INTERVAL 10                     // Flashing interval (Second)
#define BRIGHTNESS_FUNCTION brightnessBySigmonid // Brightness function
```
