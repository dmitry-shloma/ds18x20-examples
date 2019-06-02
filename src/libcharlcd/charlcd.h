#ifndef CHARLCD_H
#define CHARLCD_H

#define LCDDATAPORT        PORTD  // Порт и пины,
#define LCDDATADDR         DDRD   // к которым подключены
#define LCDDATAPIN         PIND   // сигналы D4-D7.
#define LCD_D4             3
#define LCD_D5             4
#define LCD_D6             5
#define LCD_D7             6

#define LCDCONTROLPORT     PORTD  // Порт и пины,
#define LCDCONTROLDDR      DDRD   // к которым подключены
#define LCD_RS             0      // сигналы RS, RW и E.
#define LCD_RW             1
#define LCD_E              2

#define LCD_STROBEDELAY_US 5      // Задержка строба

#define LCD_COMMAND        0
#define LCD_DATA           1

#define LCD_CURSOR_OFF     0
#define LCD_CURSOR_ON      2
#define LCD_CURSOR_BLINK   3

#define LCD_DISPLAY_OFF    0
#define LCD_DISPLAY_ON     4

#define LCD_SCROLL_LEFT    0
#define LCD_SCROLL_RIGHT   4

#define LCD_STROBDOWN      0
#define LCD_STROBUP        1

#define DELAY              1

#include <stdint.h>

void lcdSendNibble(char byte, char state);
char lcdGetNibble(char state);
char lcdRawGetByte(char state);
void lcdRawSendByte(char byte, char state);
char lcdIsBusy(void);
void lcdInit(void);
void lcdSetCursor(char cursor);
void lcdSetDisplay(char state);
void lcdClear(void);
void lcd_set_cursor_pos(char row, char col);
void lcdDisplayScroll(char pos, char dir);
void lcd_print_text(const char *text);
void lcdPutsf(char *str);
void lcdPutse(uint8_t *str);
void lcdLoadCharacter(char code, char *pattern);
void lcdLoadCharacterf(char code, char *pattern);
void lcdLoadCharactere(char code, char *uint8_t);

#endif // CHARLCD_H
