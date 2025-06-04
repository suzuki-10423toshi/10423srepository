#ifndef FLOWMETER5_DEFINE_H
#define FLOWMETER5_DEFINE_H

#include <xc.h>
#ifndef __16F887
#error "?????????? PIC16F887 ??????????"
#endif

// ===== ピン定義 =====
// LEDラッチピン RC0
#define LED_LATCH PORTCbits.RC0

// ===== ADC対応定数 =====
#define ADC_MIN_VAL 177   // 4mA相当のADC値
#define ADC_MAX_VAL 896   // 20mA相当のADC値

// ===== フラッシング制御 =====
#define FLASH_COUNT_MAX 25  // 約0.5秒間隔（20ms * 25）

// ===== 7セグメント フォントテーブル（共通アノード想定・ビット順はMSB→LSB） =====
// 例: 0b01111110 -> "0", 0b00110000 -> "1"
extern const unsigned char _LED_FONT_TABLE[10];  // ???? 


// ===== モード表示フォント（例: A, B, C... Hを表示） =====
const unsigned char MODE_FONT_TABLE[8] = {
    0b01110111, // A (Mode 0)
    0b00011111, // b
    0b01001110, // C
    0b00111101, // d
    0b01001111, // E
    0b01000111, // F
    0b01111011, // G
    0b00110111  // H
};

#endif