#include <drivers/vga.h>
#include <std.h>
#include <stream.h>

static Stream s_vga;
static Stream s_buffers[2];

static int32 s_currentBuffer;
static int32 s_nextBuffer;
static int32 s_pixel;

void InitVGA() {
    Stream vga_s = { (uint8*)VGA_VIDEO_ADDRESS, (uint8*)VGA_VIDEO_ADDRESS };
    Stream backBufferA_s = { (uint8*)BACKBUFFER_ADDRESS_A, (uint8*)BACKBUFFER_ADDRESS_A };
    Stream backBufferB_s = { (uint8*)BACKBUFFER_ADDRESS_B, (uint8*)BACKBUFFER_ADDRESS_B };

    s_vga = vga_s;

    s_buffers[0] = backBufferA_s;
    s_buffers[1] = backBufferB_s;

    s_currentBuffer = 0;
    s_nextBuffer = 1;
}
void VGABeginDraw() {
    s_pixel = 0;
    Seek(&s_buffers[s_currentBuffer], SEEK_BEGIN, 0);
}

void ClearPixelsBE(uint8* pChar, int32 offset, int32 count) {
    int32 mask = (Pow(2, count) - 1) << (8 - (offset + count));
    *pChar &= ~(mask & 0xFF);
}
void FillPixelsBE(uint8* pChar, int offset, int count) {
    int32 mask = (Pow(2, count) - 1) << (8 - (offset + count));
    *pChar |= mask & 0xFF;
}

void VGAFillPixelsLinear(VGAColor color, int32 length) {
    /*
        ========== VIDEO LAYOUT ==========
        last bit -> 0000 0000 <- first bit
        first pixel              last pixel
    */

    Stream* pDraw = &s_buffers[s_currentBuffer];

    int32 bitOffset = s_pixel % 8;
    int32 bitLen = Min(8 - bitOffset, length);

    s_pixel += length;

    if(color == 0x00) {
        ClearPixelsBE(pDraw->pPosition, bitOffset, bitLen);
        length -= bitLen;
        
        if(bitOffset + bitLen >= 8)
            Seek(pDraw, SEEK_CURRENT, 1);

        while(length - 8 > -1) {
            WriteUInt8(pDraw, 0x00);
            length -= 8;
        }

        if(length > 0) ClearPixelsBE(pDraw->pPosition, 0, length);
    } else {
        FillPixelsBE(pDraw->pPosition, bitOffset, bitLen);
        length -= bitLen;

        if(bitOffset + bitLen >= 8)
            Seek(pDraw, SEEK_CURRENT, 1);

        while(length - 8 > -1) {
            WriteUInt8(pDraw, 0xFF);
            length -= 8;
        }

        if(length > 0) FillPixelsBE(pDraw->pPosition, 0, length);
    }
}
void VGAClear(VGAColor color) {
    Stream s = s_buffers[s_currentBuffer];
    for(uint64 i = 0; i < VGA_BUFFER_LENGTH; i++)
        s.pStart[i] = 0x00;

    Seek(&s_buffers[s_currentBuffer], SEEK_BEGIN, 0);
}

void VGAEndDraw() {
    Stream* pCurrent = &s_buffers[s_currentBuffer];
    Stream* pOther = &s_buffers[s_nextBuffer];
    Stream* pVGA = &s_vga;

    Seek(pVGA, SEEK_BEGIN, 0);
    for(int64 i = 0; i < VGA_BUFFER_LENGTH; i++) {
        if(pCurrent->pStart[i] == pOther->pStart[i])
            Seek(pVGA, SEEK_CURRENT, 1);
        pVGA->pStart[i] = pCurrent->pStart[i];
    }

    int32 temp = s_currentBuffer;
    s_currentBuffer = s_nextBuffer;
    s_nextBuffer = temp;
}