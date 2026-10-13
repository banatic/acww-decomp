/* func_ov004_02211394 @ 0x02211394, 0x80 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
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
