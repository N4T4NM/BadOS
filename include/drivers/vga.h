#ifndef VGA_H
#define VGA_H

#define VGA_VIDEO_ADDRESS 0xA0000
#define BACKBUFFER_ADDRESS_A 0x10000
#define BACKBUFFER_ADDRESS_B 0x1F000

#define VGA_WIDTH_PIXELS 640
#define VGA_HEIGHT_PIXELS 480
#define VGA_BUFFER_LENGTH 38400

#include <types.h>

typedef enum {
    VGA_BLACK,
    VGA_WHITE
} VGAColor;

void InitVGA();

void VGABeginDraw();
void VGAFillPixelsLinear(VGAColor color, int32 length);
void VGAClear(VGAColor color);
void VGAEndDraw();

#endif