#include <drivers/tty.h>
#include <drivers/ports.h>
#include <stream.h>

#define TTY_CTRL 0x3D4
#define TTY_DATA 0x3D5

static TTYColor BACKGROUND;
static TTYColor FOREGROUND;
static Stream TTY;

void InitTTY() {
    BACKGROUND = TTY_BLACK;
    FOREGROUND = TTY_WHITE;

    Stream tty = { (uint8*)TTY_VIDEO_ADDRESS, (uint8*)TTY_VIDEO_ADDRESS };
    TTY = tty;
}

void TTYSetPosition(Point point) {
    int offset = (point.Y * TTY_COLUMNS + point.X);
    Seek(&TTY, SEEK_BEGIN, offset * 2);

    PortWriteUInt8(TTY_CTRL, 0x0E);
    PortWriteUInt8(TTY_DATA, (uint8)(offset >> 8));

    PortWriteUInt8(TTY_CTRL, 0x0F);
    PortWriteUInt8(TTY_DATA, (uint8)(offset & 0xFF));
}
Point TTYGetPosition() {
    PortWriteUInt8(TTY_CTRL, 0x0E);
    int offset = PortReadUInt8(TTY_DATA) << 8;

    PortWriteUInt8(TTY_CTRL, 0x0F);
    offset += PortReadUInt8(TTY_DATA);

    offset *= 2;

    int y = offset / (2 * TTY_COLUMNS);
    int x = (offset - (y * 2 * TTY_COLUMNS)) / 2;

    Point p = { x, y };
    return p;
}

TTYColor TTYGetBackground() {
    return BACKGROUND;
}
TTYColor TTYGetForeground() {
    return FOREGROUND;
}

void TTYSetBackground(TTYColor background) {
    BACKGROUND = background;
    return;
}
void TTYSetForeground(TTYColor foreground) {
    FOREGROUND = foreground;
    return;
}

void TTYClearScreen() {
    Point zero = {0, 0};
    TTYSetPosition(zero);

    int sz = TTY_COLUMNS * TTY_ROWS;
    for(int i = 0; i < sz; i++) 
        TTYWriteChar(' ');

    TTYSetPosition(zero);
}
void TTYWriteChar(uint8 c) {
    Point p = TTYGetPosition();
    if(c == '\n') {
        p.X = 0;
        p.Y++;
    } else {
        uint8 color = FOREGROUND | (BACKGROUND << 4);
        uint16 write = c | (color << 8);

        WriteInt16(&TTY, write);
        p.X++;
    }

    TTYSetPosition(p);
}

void TTYWrite(string str) {
   int i = 0;
   while(str[i] != 0)
        TTYWriteChar(str[i++]);
}
void TTYWriteLine(string str) {
    TTYWrite(str);    
    TTYWrite("\n");
}