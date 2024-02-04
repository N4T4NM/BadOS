#ifndef STD_H
#define STD_H

#include <types.h>

#define LOWORD(word) (uint16)((word) & 0xFFFF)
#define HIWORD(word) (uint16)((word >> 16) & 0xFFFF)

void UInt64ToStr(uint64 u64, string s);
void StrReverse(string s);
int32 StrLength(string s);


int32 Min(int32 a, int32 b);
int32 Pow(int32 v, int32 p);
#endif