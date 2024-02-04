#ifndef STREAM_H
#define STREAM_H
#include <types.h>

typedef struct {
    uint8* pStart;
    uint8* pPosition;
} Stream;

typedef enum {
    SEEK_BEGIN,
    SEEK_CURRENT
} SeekFrom;

void Seek(Stream* pStream, SeekFrom from, int64 offset);
void Write(Stream* pStream, uint8* pBuffer, int64 count);
void WriteUInt8(Stream* pStream, uint8 u8);
void WriteInt16(Stream* pStream, int16 i16);

void Copy(Stream* pSource, Stream* pTarget, int64 count);

uint8 Peek(Stream* pStream);
uint8 ReadUInt8(Stream* pStream);
int32 ReadInt32(Stream* pStream);

#endif