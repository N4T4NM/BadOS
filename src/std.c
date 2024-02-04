#include <std.h>

void UInt64ToStr(uint64 u64, string s) {
    int32 i = 0;
    do {
        s[i++] = u64 % 10 + '0';
    } while((u64 /= 10) > 0);

    s[i] = '\0';

    StrReverse(s);
}

void StrReverse(string s) {
    int32 right = StrLength(s) - 1;
    int32 left = 0;

    while(left < right) {
        uint8 c = s[left];
        s[left++] = s[right];
        s[right--] = c;
    }
}

int32 StrLength(string s) {
    int i = 0;
    while(s[i] != '\0') i++;
    return i;
}

int32 Min(int32 a, int32 b) {
    if(a < b)
        return a;

    return b;
}

int32 Pow(int32 v, int32 p) {
    for(int32 i = 1; i < p; i++)
        v *= 2;

    return v;
}