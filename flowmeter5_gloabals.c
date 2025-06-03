#include "globals.h"

// ===== ã°ã­ã¼ãã«å¤æ°ã®å®ä½å®ç¾© =====
int adcValue = 0;
int displayValue = 0;
unsigned char digits[4] = {0, 0, 0, 0};

unsigned char displayMode = 0;
unsigned char flashFlag = 1;
unsigned char flashCount = 0;
unsigned int adc_val = 0;
unsigned int display_val = 0;
unsigned char mode = 0;
unsigned char flash_on = 0;
unsigned int flash_timer = 0;

const unsigned char LED_FONT_TABLE[10] = {
    0b00111111, // 0
    0b00000110, // 1
    0b01011011, // 2
    0b01001111, // 3
    0b01100110, // 4
    0b01101101, // 5
    0b01111101, // 6
    0b00000111, // 7
    0b01111111, // 8
    0b01101111  // 9
};