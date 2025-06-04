# 1 "../flowmeter5_gloabals.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 285 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\include/language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "../flowmeter5_gloabals.c" 2
# 1 "../globals.h" 1



extern unsigned int adc_val;
extern unsigned int display_val;
extern unsigned char mode;
extern unsigned char flash_on;
extern unsigned int flash_timer;
extern unsigned char flashCount;

extern const unsigned char LED_FONT_TABLE[10];
# 2 "../flowmeter5_gloabals.c" 2


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
    0b00111111,
    0b00000110,
    0b01011011,
    0b01001111,
    0b01100110,
    0b01101101,
    0b01111101,
    0b00000111,
    0b01111111,
    0b01101111
};
