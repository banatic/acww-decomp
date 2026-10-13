/* func_020ad2e4 @ 0x020ad2e4, 0xbc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int v;
} UnkStruct_020ad2e4;
typedef struct {
    UnkStruct_020ad2e4 x, y, z;
} UnkStruct_020ad2e4_2;
typedef struct {
    int unk_00, unk_04, unk_08;
} UnkStruct_020ad2e4_3;

extern int data_021c67a4;
extern UnkStruct_020ad2e4_2 data_021c67d0;
extern int data_021f47cc;
extern int data_021f47d4;

extern int FX_Div(int a, int b);
extern int FX_MulFunc(int a, int b);

int func_020ad2e4(UnkStruct_020ad2e4_3 *a, int b, int c)
{
    UnkStruct_020ad2e4_2 p;
    int t;
    int d;
    int e;

    if (data_021c67a4 == 0) {
        goto retc;
    }
    p.x = data_021c67d0.x;
    p.y = data_021c67d0.y;
    p.z = data_021c67d0.z;
    t = a->unk_08;
    if (p.z.v > t) {
        d = p.z.v - t;
        if (d > 0xb000) {
            c = (u8) (c >> 5);
            goto retc;
        }
        if ((data_021f47cc & 1) == 0) {
            data_021f47d4 = FX_Div(0xf80, 0xb000);
            data_021f47cc |= 1;
        }
        c = (u8) (c - (u8) (FX_MulFunc(FX_MulFunc(c << 12, data_021f47d4), d) >> 12));
        goto retc;
    }
    d = t - p.z.v;
    if (d > b + 0xc000) {
        return 0;
    }
    e = a->unk_00 - p.x.v;
    if (e < 0) {
        e = -e;
    }
    if (e > b + 0xf000) {
        return 0;
    }
retc:
    return c;
}
