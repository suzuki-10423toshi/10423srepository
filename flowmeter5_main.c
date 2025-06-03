#include <xc.h>
#include "flowmeter5_define.h"
#include "globals.h"

#define _XTAL_FREQ 8000000  // 8MHz クロック定義

unsigned char digit_val[4];  // 4桁表示用の配列_修正済

// A/D初期化
void ADC_Init(void) {
    ADCON0 = 0b00000001;  // AN0選択、A/D変換ON
    ADCON1 = 0b00000000;  // すべてアナログ入力、VREFはVDD/VSS
}

// A/D読み取り
unsigned int Read_ADC(void) {
    __delay_us(10);         // 変換準備待ち
    GO_nDONE = 1;           // 変換開始
    while (GO_nDONE);       // 変換終了待ち
  return ((unsigned int)(ADRESH << 8) | ADRESL); //  10bit ADC値返す_修正済
}

// 4桁7セグメント表示の桁分け
void Split_Display(unsigned int display, unsigned char* digits) {
    digits[0] = display / 1000;
    digits[1] = (display / 100) % 10;
    digits[2] = (display / 10) % 10;
    digits[3] = display % 10;
}

// LED表示送信
void Send_LED_Data(unsigned char* digits, unsigned char mode) {
    for (int i = 0; i < 4; i++) {
        SSPBUF = LED_FONT_TABLE[digits[i]];
        while (!SSPSTATbits.BF);
    }
    SSPBUF = MODE_FONT_TABLE[mode];
    while (!SSPSTATbits.BF);
    
    LED_LATCH = 0;
    LED_LATCH = 1;
}

// 各モードごとのスケーリング
unsigned int Scale_Display(unsigned int adc_val, unsigned char mode) {
    float current = ((float)(adc_val - ADC_MIN_VAL) / (ADC_MAX_VAL - ADC_MIN_VAL)) * 16.0 + 4.0;

    float scale_max[] = {30.0, 50.0, 75.0, 100.0, 150.0, 200.0, 300.0, 500.0};
    float flow = ((current - 4.0) / 16.0) * scale_max[mode];
    
    return (unsigned int)(flow + 0.5);  // 四捨五入
}

void main(void) {
    // ポート初期化
    TRISCbits.TRISC0 = 0;  // RC0ピンを出力に設定_修正
    TRISA0 = 1; // AN0入力
    TRISC0 = 0; // RC0 出力（LED_LATCH）
    TRISC3 = 0; // SCK
    TRISC5 = 0; // SDO
    TRISB0 = 1; // Mode切替ボタン
    TRISB1 = 1; // その他ボタン

    LED_LATCH = 0;

    // SPI設定
    SSPSTAT = 0x40;
    SSPCON = 0x20;

    // A/D設定
    ADC_Init();

    mode = 0;
    flash_on = 0;
    flash_timer = 0;

    while (1) {
        adc_val = Read_ADC();
        display_val = Scale_Display(adc_val, mode);

        // 20.5mA (ADC=~920相当) 以上で点滅処理ON
        if (adc_val >= 920) {
            flash_on = 1;
        } else {
            flash_on = 0;
        }

        // 点滅処理
        if (flash_on) {
            flash_timer++;
            if (flash_timer >= FLASH_COUNT_MAX) {
                flash_timer = 0;
                static unsigned char flash_state = 0;
                flash_state = !flash_state;
                if (flash_state) {
                    Split_Display(display_val, digit_val);
                    Send_LED_Data(digit_val, mode);
                } else {
                    unsigned char blank[4] = {0, 0, 0, 0};
                    Send_LED_Data(blank, mode);
                }
            }
        } else {
            Split_Display(display_val, digit_val);
            Send_LED_Data(digit_val, mode);
        }

        // 簡易ディレイ
        __delay_ms(20);
    }
}
