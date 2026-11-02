/* catalog_caught: 5 functions, module ov114
 * mwccarm 1.2/base -O4,s
 * func_ov114_0229c1e4 @ 0x0229c1e4, 0xe4 bytes, Thumb
 * func_ov114_0229c1b8 @ 0x0229c1b8, 0x2c bytes, Thumb
 * func_ov114_0229c1a0 @ 0x0229c1a0, 0x18 bytes, Thumb
 * func_ov114_0229c190 @ 0x0229c190, 0x10 bytes, Thumb
 * func_ov114_0229c180 @ 0x0229c180, 0x10 bytes, Thumb
 */

#include "types.h"

typedef struct {
    char pad_00[0x1264];
    int bits[3];
    char pad_1270[0x1294 - 0x1270];
    int unk_1294;
    char pad_1298[0x12b7 - 0x1298];
    u8 unk_12B7;
} UnkStruct_0229c1e4;

typedef struct UnkStruct_0229c1b8 {
    char pad_00[0x1264];
    unsigned int bits[1];
} UnkStruct_0229c1b8;

typedef struct {
    char pad_00[0x12ac];
    unsigned short unk_12AC;
} func_ov114_0229c1a0_struct;

extern void *func_020984e8(void);
extern void *func_020996ac(void *h);
extern int func_0203cdcc(void *a, volatile u16 *w);

void func_ov114_0229c1e4(UnkStruct_0229c1e4 *self)
{
    int i;
    void *h;
    volatile u16 t;
    int j;

    for (i = 0; i < 3; i++) {
        self->bits[i] = 0;
    }
    h = func_020984e8();
    t = 0xfff1;
    if (self->unk_12B7 == 0) {
        for (j = 0; j < self->unk_1294; j++) {
            t = ((unsigned int) j < 0x38) ? (u16) (j + 0x12e8) : (u16) 0x12e8;
            if (func_0203cdcc(func_020996ac(h), &t) != 0) {
                self->bits[j >> 5] |= 1 << (j & 0x1f);
            }
        }
    } else {
        for (j = 0; j < self->unk_1294; j++) {
            t = ((unsigned int) j < 0x38) ? (u16) (j + 0x12b0) : (u16) 0x12b0;
            if (func_0203cdcc(func_020996ac(h), &t) != 0) {
                self->bits[j >> 5] |= 1 << (j & 0x1f);
            }
        }
    }
}

int func_ov114_0229c1b8(UnkStruct_0229c1b8 *p, int idx)
{
    int ret = 1;
    int mask = 1 << (idx & 31);
    int word = idx >> 5;
    if (!(mask & p->bits[word])) {
        ret = 0;
    }
    return ret;
}

int func_ov114_0229c1a0(func_ov114_0229c1a0_struct *ptr, unsigned short mask)
{
    if ((ptr->unk_12AC & mask) != 0) {
        return 1;
    }
    return 0;
}

void func_ov114_0229c190(unsigned short *p, unsigned short mask)
{
    unsigned short *q = (unsigned short *) ((char *) p + 0x12ac);
    *q = (unsigned short) (*q | mask);
}

void func_ov114_0229c180(unsigned short *p, unsigned short mask)
{
    unsigned short v;
    p = (unsigned short *) ((char *) p + 0x12ac);
    v = *p;
    v &= ~mask;
    *p = v;
}
