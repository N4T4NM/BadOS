#ifndef TYPES_H
#define TYPES_H

typedef unsigned char bool;

typedef unsigned char uint8;
typedef char int8;

typedef unsigned short uint16;
typedef short int16;

typedef unsigned int uint32;
typedef int int32;

typedef unsigned long uint64;
typedef long int64;

typedef uint8* string;

typedef struct {
    int X;
    int Y;
} Point;

#define TRUE 1
#define FALSE 0
#define NULL 0

#endif