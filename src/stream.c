#include <stream.h>
void Seek(Stream* pStream, SeekFrom from, int64 offset) {
    switch (from)
    {
        case SEEK_BEGIN:
            pStream->pPosition = pStream->pStart + offset;
            break;
        case SEEK_CURRENT:
            pStream->pPosition += offset;
            break;
    }
}
void Write(Stream* pStream, uint8* pBuffer, int64 count) {
    for(int64 i = 0; i < count; i++)
        *pStream->pPosition++ = *pBuffer++;
}
void WriteUInt8(Stream* pStream, uint8 u8) {
    *pStream->pPosition++ = u8;
}
void WriteInt16(Stream* pStream, int16 i16) {
    uint8* pBuffer = (uint8*)&i16;
    Write(pStream, pBuffer, 2);
}

void Copy(Stream* pSource, Stream* pTarget, int64 count) {
    Write(pTarget, pSource->pPosition, count);
}

uint8 Peek(Stream* pStream){
    return *pStream->pPosition;
}
uint8 ReadUInt8(Stream* pStream) {
    return *pStream->pPosition++;
}
int32 ReadInt32(Stream* pStream) {
    int32 i32 = *(int32*)pStream->pPosition;
    pStream->pPosition += 4;

    return i32;
}