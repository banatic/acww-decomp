/* room_object_body_6: 3 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02211394 @ 0x02211394, 0x80 bytes, Thumb
 * func_ov004_02211388 @ 0x02211388, 0xc bytes, Thumb
 * func_ov004_0221137c @ 0x0221137c, 0xc bytes, Thumb
 */

#include "types.h"

struct UnkStruct_02211394 {
    unsigned int a : 4;
    unsigned int b : 4;
    unsigned int c : 16;
    unsigned int d : 2;
    unsigned int e : 2;
    unsigned int f : 1;
    unsigned int g : 5;
};

union UnkStruct_02211394_2 {
    struct UnkStruct_02211394 b;
    int w[2];
};

typedef struct {
    unsigned int a : 8;
    unsigned int b : 16;
    unsigned int c : 8;
} BF;

typedef union {
    unsigned int w;
    BF unk_00;
} UnkStruct_02211388;

typedef struct {
    unsigned int a : 26;
    unsigned int b : 2;
    unsigned int c : 4;
} BF_0221137c;

typedef union {
    unsigned int w;
    BF_0221137c unk_00;
} UnkStruct_0221137c;

int func_ov004_02211394(int p0, int p1, int p2, int p3, u8 p4, int p5)
{
    union UnkStruct_02211394_2 s;

    s.b.a = p0;
    s.b.b = p1;
    s.b.c = p2;
    s.b.d = p3;
    s.b.e = p5;
    s.b.f = p4;
    s.b.g = 1;
    return s.w[0];
}

unsigned int func_ov004_02211388(unsigned int v)
{
    UnkStruct_02211388 u;
    u.w = v;
    return u.unk_00.b;
}

unsigned int func_ov004_0221137c(unsigned int v)
{
    UnkStruct_0221137c u;
    u.w = v;
    return u.unk_00.b;
}
