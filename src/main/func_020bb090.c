/* func_020bb090 @ 0x020bb090, 0xfc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int pad_00;
    u16 unk_04;
    u16 unk_06;
    int unk_08;
    int unk_0C;
} UnkStruct_020bb090;

extern int data_021f6f70;
extern UnkStruct_020bb090 data_021f7270;
extern u16 data_021f6f74[];

void func_020bb090(void)
{
    int parity;
    int y1;
    int span;
    int gB, gA, rB, rA, bB, bA;
    int mr, mg, c;
    int y, y0;
    int t, inv;
    int cA, cB;
    u16 *dst;
    volatile u16 w[6];

    parity = (data_021f6f70 + 1) % 2;
    w[3] = data_021f7270.unk_04;
    w[1] = w[3];
    w[4] = data_021f7270.unk_06;
    w[2] = w[4];
    dst = (u16 *) ((char *) data_021f6f74 + parity * 0x180);
    y0 = data_021f7270.unk_08;
    y1 = data_021f7270.unk_0C;
    y = 0;
    span = y1 - y0;
    cB = w[2];
    gB = ((u32) cB << 22) >> 27;
    cA = w[1];
    gA = ((u32) cA << 22) >> 27;
    rB = ((u32) (cB << 27)) >> 27;
    rA = ((u32) (cA << 27)) >> 27;
    bB = ((u32) cB << 17) >> 27;
    bA = ((u32) cA << 17) >> 27;
    for (; y < 0xc0; y++) {
        if (y <= y0) {
            w[0] = w[3];
        } else if (y >= y1) {
            w[0] = w[4];
        } else {
            t = ((y - y0) << 8) / span;
            inv = 0x100 - t;
            c = (int) (u16) ((bA * inv + bB * t) >> 8) << 10;
            mr = (u16) ((rA * inv + rB * t) >> 8);
            mg = (int) (u16) ((gA * inv + gB * t) >> 8) << 5;
            c = c | (mr | mg);
            w[0] = (u16) c;
        }
        *dst = w[0];
        dst++;
    }
    data_021f6f70 = parity;
}
