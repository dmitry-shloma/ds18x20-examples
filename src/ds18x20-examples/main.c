#include "config.h"

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "./../onewire/onewire.h"
#include "./../lcd/lcd.h"

// 123.4
// numbers[0] = 123
// numbers[1] = 4
inline void explodeDoubleNumber(int* numbers, double flt) {
  numbers[0] = abs((int) flt);
  numbers[1] = abs((int) ((flt - ((int) flt)) * 10));
}

inline void printTemp(double d, uint8_t i)
{
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

double getTemp(uint64_t ds18b20s) {
  uint8_t temperatureL;
  uint8_t temperatureH;
  double retd = 0;


  setDevice(ds18b20s);
  writeByte(CMD_CONVERTTEMP);

  _delay_ms(750);

  setDevice(ds18b20s);
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
  
  oneWireInit(PIND7);
  
  double temperature;
  uint8_t n = 8;
  uint64_t roms[n];
  searchRom(roms, &n);
  char txt[17] = "devices [";
  char num[5];
  itoa(n, num, 10);
  strcat(txt, num);
  strcat(txt, "]");
  lcdClear();
  lcdGotoXY(0, 0);
  lcdPuts(txt);
  _delay_ms(2000);
  while (1) {
    for (uint8_t i = 0; i < n; i++) {
      temperature = getTemp(roms[i]);
      printTemp(temperature, i + 1);
      _delay_ms(500);
    }
  }
}
// site: http://micro-pi.ru
