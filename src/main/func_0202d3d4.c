/* func_0202d3d4 @ 0x0202d3d4, 0x1f8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u8 *unk_00;
    u32 unk_04;
    u32 unk_08;
} UnkStruct_0202d3d4;

extern UnkStruct_0202d3d4 *func_0204e414(void);
extern u8 data_020c893c[];
extern u16 *func_02037e0c(u8 *cell, int a, int b, int c);

void func_0202d3d4(int *p, int *out)
{
    unsigned int flag1;
    unsigned int q1;
    unsigned int q2;
    unsigned int q3;
    unsigned int q4;
    unsigned int q5;
    unsigned int q6;
    unsigned int q7;
    unsigned int q8;
    int W;
    int H;
    int y;
    int xinit;
    u8 *cellzero;
    int argzero;
    int ainit;
    int binit;
    unsigned int flagzero;
    unsigned int flagone;
    unsigned int qone;
    unsigned int z8;
    unsigned int z7;
    unsigned int z6;
    unsigned int z5;
    unsigned int z4;
    unsigned int z3;
    unsigned int z2;
    unsigned int z1;
    int b;
    int a;
    u8 res;
    u8 *cell;
    u16 *cur;
    unsigned int id;
    int x;
    UnkStruct_0202d3d4 *obj;
    int i;
    u32 *q;

    obj = func_0204e414();
    res = 0;
    *out = 0;
    if (obj == 0) {
        goto tail;
    }
    q = (u32 *) ((int) obj + 4);
    W = q[0];
    H = q[1];
    y = 1;
    xinit = 1;
    cellzero = 0;
    ainit = 0;
    binit = 0;
    flagone = 1;
    flagzero = 0;
    qone = 1;
    z8 = 0;
    z7 = 0;
    z6 = 0;
    z5 = 0;
    z4 = 0;
    z3 = 0;
    z2 = 0;
    z1 = 0;
    argzero = 0;
    for (; y < H - 1; y++) {
        for (x = xinit; x < W - 1; x++) {
            if ((u32) x < obj->unk_04 && (u32) y < obj->unk_08 && obj->unk_00 != 0) {
                cell = obj->unk_00 + (x + y * obj->unk_04) * 0x28;
            } else {
                cell = cellzero;
            }
            if (cell != 0) {
                cur = func_02037e0c(cell, argzero, argzero, argzero);
                if (cur != 0) {
                    for (a = ainit; a < 0x10; a++) {
                        for (b = binit; b < 0x10; b++) {
                            flag1 = flagzero;
                            id = *cur;
                            if (id >= 0xc8 && id <= 0xcf) {
                                flag1 = flagone;
                            }
                            if (flag1 == 1) {
                                if ((res & 2) != 0) {
                                    res |= 2;
                                }
                            } else {
                                q7 = q6 = q5 = q4 = q3 = q2 = q1 = qone;
                                q8 = z8;
                                if (id <= 5) {
                                    q8 = qone;
                                }
                                if (q8 == 0) {
                                    if (!(id >= 6 && id <= 0xb)) {
                                        q7 = z7;
                                    }
                                }
                                if (q7 == 0) {
                                    if (!(id >= 0xc && id <= 0x11)) {
                                        q6 = z6;
                                    }
                                }
                                if (q6 == 0) {
                                    if (!((id >= 0x12 && id <= 0x19) || id == 0x1c)) {
                                        q5 = z5;
                                    }
                                }
                                if (q5 == 0) {
                                    if (!((id >= 0x8a && id <= 0x8f) || (id >= 0x90 && id <= 0x95) ||
                                          (id >= 0x96 && id <= 0x9b) || (id >= 0x9c && id <= 0xa3) || id == 0xa5)) {
                                        q4 = z4;
                                    }
                                }
                                if (q4 == 0) {
                                    if (id != 0x1a) {
                                        q3 = z3;
                                    }
                                }
                                if (q3 == 0) {
                                    if (id != 0xa4) {
                                        q2 = z2;
                                    }
                                }
                                if (q2 == 0) {
                                    if (id != 0x1d) {
                                        q1 = z1;
                                    }
                                }
                                if (q1 == 1) {
                                    if ((res & 4) != 0) {
                                        res |= 4;
                                    }
                                }
                            }
                            if (res == 6) {
                                break;
                            }
                            cur++;
                        }
                        if (res == 6) {
                            break;
                        }
                    }
                }
            }
            if (res == 6) {
                break;
            }
        }
        if (res == 6) {
            break;
        }
    }
tail:
    for (i = 0; i < 4; i++) {
        if (((res >> i) & 1) == 0) {
            *p = data_020c893c[i];
            *out = *out + 1;
            p++;
        }
    }
}
