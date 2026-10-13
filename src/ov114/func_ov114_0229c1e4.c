/* func_ov114_0229c1e4 @ 0x0229c1e4, 0xe4 bytes, Thumb, module ov114
 * mwccarm 1.2/base -O4,s
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
