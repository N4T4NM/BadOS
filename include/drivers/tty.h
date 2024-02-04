#ifndef TTY_H
#define TTY_H

#define TTY_COLUMNS 80
#define TTY_ROWS 25

#define TTY_VIDEO_ADDRESS 0xB8000

#include <types.h>

typedef enum {
    TTY_BLACK,
    TTY_BLUE,
    TTY_GREEN,
    TTY_CYAN,
    TTY_RED,
    TTY_MAGENTA,
    TTY_BROWN,
    TTY_LIGHT_GRAY,
    TTY_DARK_GRAY,
    TTY_LIGHT_BLUE,
    TTY_LIGHT_GREEN,
    TTY_LIGHT_CYAN,
    TTY_LIGHT_RED,
    TTY_LIGHT_MAGENTA,
    TTY_YELLOW,
    TTY_WHITE
} TTYColor;

void InitTTY();

void TTYSetPosition(Point point);
Point TTYGetPosition();

TTYColor TTYGetBackground();
TTYColor TTYGetForeground();

void TTYSetForeground(TTYColor color);
void TTYSetBackground(TTYColor color);

void TTYClearScreen();
void TTYWriteChar(uint8 c);
void TTYWrite(string str);
void TTYWriteLine(string str);
#endif