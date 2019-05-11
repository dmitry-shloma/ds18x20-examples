#include "config.h"

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "OneWire.h"
#include "LCD.h"

// 123.4
// numbers[0] = 123
// numbers[1] = 4
inline void explodeDoubleNumber(int* numbers, double flt) {
  numbers[0] = abs((int) flt);
  numbers[1] = abs((int) ((flt - ((int) flt)) * 10));
}

inline void printTemp(double d, uint8_t i) {
  char text[17] = "T[";
  int fs[2];
  char num[5];
  
  itoa(i, num, 10);
  strcat(text, num);
  strcat(text, "]=");
  
  explodeDoubleNumber(fs, d);
  if (d < 0) {
    strcat(text, "-");
  }
  itoa(fs[0], num, 10);
  strcat(text, num);
  strcat(text, ".");
  itoa(fs[1], num, 10);
  strcat(text, num);
  strcat(text, "'C");
  lcdClear();
  lcdGotoXY(0, 0);
  lcdPuts(text);
}

double getTemp(uint8_t pin) {
  uint8_t temperatureL;
  uint8_t temperatureH;
  double retd = 0;
  
  oneWireInit(pin);
  
  skipRom();
  writeByte(CMD_CONVERTTEMP);
  
  _delay_ms(750);
  
  skipRom();
  writeByte(CMD_RSCRATCHPAD);
  
  temperatureL = readByte();
  temperatureH = readByte();
  
  retd = ((temperatureH << 8) + temperatureL) * 0.0625;
  
  return retd;
}

int main(void) {
  _delay_ms(100);
  lcdInit();
  lcdClear();
  lcdSetDisplay(LCD_DISPLAY_ON);
  lcdSetCursor(LCD_CURSOR_OFF);

  double temperature;
  
  uint8_t pin = 0;
  
  while (1) {
    temperature = getTemp(pin);
    printTemp(temperature, pin);
    if (pin == 4) {
      pin = 0;
    } else {
      pin++;
    }
    _delay_ms(500);
  }
}

// site: http://micro-pi.ru