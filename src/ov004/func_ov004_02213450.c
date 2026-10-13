/* func_ov004_02213450 @ 0x02213450, 0x7c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_0203ee14(void *self, void *ptr);
extern void func_020a8164(void *ptr, void *data);
extern void *func_ov004_0220fde0(void *self);
extern int func_0204bc50(void *p, int a);
extern void *data_ov004_022531b0;

typedef struct UnkStruct_02213450 {
    char pad_00[8];
    unsigned int unk_08;
} UnkStruct_02213450;

typedef struct Main {
    char pad_00[0xec];
    char sub[0x1e];
    signed char unk_10A;
    char pad_10B[0x21];
    UnkStruct_02213450 *unk_12C;
} Main;

int func_ov004_02213450(Main *self)
{
    void *p;
    volatile u16 vv[2];
    int m;
    u16 t;
    int r;

    p = self;
    if (self != 0) {
        p = (char *) self + 0xec;
    }
    func_0203ee14(self, p);
    self->unk_12C->unk_08 = 1;
    vv[1] = (u16) func_0204bc50(func_ov004_0220fde0(self), 0);
    m = 0;
    t = vv[1];
    if (t >= 0x47d8 && t <= 0x4a47) {
        m = 1;
    }
    if (m != 0) {
        r = (t - 0x47d8) >> 2;
    } else {
        r = -1;
    }
    func_020a8164((char *) self + 0xec, &data_ov004_022531b0);
    self->unk_10A = (signed char) r;
    return 1;
}
