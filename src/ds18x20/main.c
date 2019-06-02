#define F_CPU 8000000UL

#include <avr/io.h>
#include <string.h>
#include <stdlib.h>
#include <util/delay.h>

#include "./../libcharlcd/charlcd.h"
#include "./../libds18s20/ds18S20.h"

#define I_MAX 4

// Convert the temperature reading to a string
void ConvertTemperature2String(uint8_t LSB, uint8_t MSB, char *buffer);

// Convert sensor reading to a string
void ConvertTemperature2String(uint8_t LSB, uint8_t MSB, char *buffer)
{
    int16_t Temperature=0;
    char hp[3] = "";

    Temperature = MSB;
    Temperature <<= 8;
    Temperature |= LSB;

    if (Temperature<0)
        *buffer='-';

    itoa(abs(Temperature)/2,hp,10);
    strcat(buffer,hp);

    if (LSB & 0x01)
        strcat(buffer,".5C");
    else
        strcat(buffer,".0C");

    return;
}

int main(void)
{
    lcdInit();
    lcdClear();
    lcdSetDisplay(LCD_DISPLAY_ON);
    lcdSetCursor(LCD_CURSOR_OFF);

    DDRB = 0b00000000;
    PORTB = 0b11111111;

    int i = 0;

    while(1) {
        TSDS18x20 DS18x20;
        TSDS18x20 *pDS18x20 = &DS18x20;

        if ((PINB&(1 << PB0)) == 1) { // Верхняя кнопка нажата
            i = i < I_MAX ? ++i: 0;
        }

        lcdClear();
        lcd_set_cursor_pos(0, 0);

        // Init DS18B20 sensor
        if (DS18x20_Init(pDS18x20, &PORTC, i)) {
            lcd_print_text("НЕТ ТЕРМОМЕТРА");
        } else {
            char buf[2] = "";
            itoa(i + 1, buf, 10);
            char buf2[3] = "T[";
            strcat(buf2, buf);
            strcat(buf2, "]=");
            lcd_print_text(buf2);

            lcd_set_cursor_pos(0, 5);
            // Initiate a temperature conversion and get the temperature reading
            if (DS18x20_MeasureTemperature(pDS18x20)) {
                char buffer[5] = "";
                ConvertTemperature2String(
                    pDS18x20->scratchpad[0],
                    pDS18x20->scratchpad[1],
                    buffer);
                lcd_print_text(buffer);
            } else {
                lcd_print_text("ОШИБКА: 41");
            }
            _delay_ms(500);
        }
    }
    return 0;
}

//#define F_CPU 8000000UL

//#include <avr/io.h>
//#include <util/delay.h>
//#include <stdlib.h>
//#include <string.h>
//#include <math.h>

//#include "./../onewire/onewire.h"
//#include "./../char-lcd/charlcd.h"

//// 123.4
//// numbers[0] = 123
//// numbers[1] = 4
//void explodeDoubleNumber(int* numbers, double flt)
//{
//  numbers[0] = abs((int) flt);
//  numbers[1] = abs((int) ((flt - ((int) flt)) * 10));
//}

//void printTemp(double d, uint8_t i)
//{
//  char text[17] = "T[";
//  int fs[2];
//  char num[5];
  
//  itoa(i, num, 10);
//  strcat(text, num);
//  strcat(text, "]=");
  
//  explodeDoubleNumber(fs, d);
//  if (d < 0) {
//    strcat(text, "-");
//  }
//  itoa(fs[0], num, 10);
//  strcat(text, num);
//  strcat(text, ".");
//  itoa(fs[1], num, 10);
//  strcat(text, num);
//  strcat(text, "'C");
//  lcdClear();
//  lcd_set_cursor_pos(0, 0);
//  lcd_print_text(text);
//}

//double getTemp(uint64_t ds18b20s)
//{
//  uint8_t temperatureL;
//  uint8_t temperatureH;
//  double retd = 0;


//  setDevice(ds18b20s);
//  writeByte(CMD_CONVERTTEMP);

//  _delay_ms(750);

//  setDevice(ds18b20s);
//  writeByte(CMD_RSCRATCHPAD);

//  temperatureL = readByte();
//  temperatureH = readByte();

//  retd = ((temperatureH << 8) + temperatureL) * 0.0625;

//  return retd;
//}

//int main(void)
//{
//  _delay_ms(100);
//  lcdInit();
//  lcdClear();
//  lcdSetDisplay(LCD_DISPLAY_ON);
//  lcdSetCursor(LCD_CURSOR_OFF);
  
//  oneWireInit(PIND7);
  
//  double temperature;
//  uint8_t n = 8;
//  uint64_t roms[n];
//  searchRom(roms, &n);
//  char txt[17] = "devices [";
//  char num[5];
//  itoa(n, num, 10);
//  strcat(txt, num);
//  strcat(txt, "]");
//  lcdClear();
//  lcd_set_cursor_pos(0, 0);
//  lcd_print_text(txt);
//  _delay_ms(2000);
//  while (1) {
//    for (uint8_t i = 0; i < n; i++) {
//      temperature = getTemp(roms[i]);
//      printTemp(temperature, i + 1);
//      _delay_ms(500);
//    }
//  }
//}
