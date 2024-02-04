#include <player.h>
#include <clock.h>
#include <drivers/vga.h>
#include <stream.h>

int32 ReadVarInt(Stream* pBuffer) {
    int32 index = 0;
    int32 value = 0;

    while(1) {
        uint8 c = ReadUInt8(pBuffer);
        value |= (c & 0x7F) << index;

        if((c & 0x80) == 0) break;
        index += 7;
    }

    return value;
}

void Render(Stream* pVideoSource) {
    int32 pixel = 0;
    while(pixel < VIDEO_FRAME_LENGTH) {
        uint8 color = ReadUInt8(pVideoSource);
        int32 length = ReadVarInt(pVideoSource);

        VGAFillPixelsLinear(color, length);
        pixel += length;
    }
}

/*
Performance seems to be acceptable, only giving problems on some sections
maybe this is due to VGA being slow?
The python preview seems to have problems at the exact same section, it may be my shitty
encoder.

Finally, I found the issue: My encoder was just copying the slowness directly from the .mp4 file,
some frames were literally lagging, dumb shit I know.
*/
void Play() {
    Stream video = { (uint8*)VIDEO_ADDRESS, (uint8*)VIDEO_ADDRESS };
    InitVGA();
    InitClock();
    
    /*
    This is a safeguard against GDB's bullshit, sometimes it decides to create life
    and changes behavior. If we don't do this check, our code may start reading
    uninitialized memory.
    */
    int32 frameCount;
    do { 
        Seek(&video, SEEK_BEGIN, 0);
        frameCount = ReadInt32(&video);
    } while(frameCount == 0);

    int32 rendered = 0;
    
    uint64 s = ClockTimeSinceStartupMs();
    uint64 now;
    while(rendered < frameCount) {

        VGABeginDraw();
        Render(&video);

        while(TRUE) {
            now = ClockTimeSinceStartupMs();
            
            /* 33 ms of delay corresponds to 30 fps*/
            if(now - s > 33) break;
        }
        s = now;

        //Display data and swap buffers
        VGAEndDraw(); 
        rendered++;
    }
}