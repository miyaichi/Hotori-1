# Hotori Light

センサーの情報を受け、明かりを点滅させるモジュールです。

BLE(Bluetooth Low Energy)でセンサーデバイスを探し、デバイスからのアドバタイジング・パケットに書かれたセンサー情報を読み取り、情報に基づいて明かりを点滅させます。

## Device

[ATOM Matrix](https://m5stack.com/products/atom-matrix-esp32-development-kit) を使っています。また、ケーブルなしで運用できるよう [ATOM TailBat](https://m5stack.com/products/atom-tailbat?variant=32169047064666) も接続していますが、稼働時間はあまり長くありません。

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
#define BLE_DEVICE_NAME "HotoriLight" // Device name
#define BLE_COMPANY_ID 0xffff         // Company ID
```

## Color Pallet

ボタンを押すと点滅する色がサイクリックに変わりますが、色のパレットは config.h に以下のように定義されています。必要に応じて修正してください。

```cpp
RTC_DATA_ATTR static int colorIndex;
CRGB colors[] = {
    CRGB::White,
    CRGB::Red,
    CRGB::Yellow,
    CRGB::Green,
    CRGB::Cyan,
    CRGB::Blue,
    CRGB::Magenta,
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
