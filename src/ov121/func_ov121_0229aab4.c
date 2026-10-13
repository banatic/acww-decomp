/* func_ov121_0229aab4 @ 0x0229aab4, 0xcc bytes, Thumb, module ov121
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_0229aab4 {
    u8 pad_00[0xae];
    u8 unk_AE;
} UnkStruct_0229aab4;

extern int func_020984e8(void);
extern int func_02099fe8(void);
extern u16 *func_020993a8(int a);
extern void func_ov121_0229af7c(UnkStruct_0229aab4 *self, int a, int b);
extern void func_ov121_0229a50c(UnkStruct_0229aab4 *self);
extern unsigned int func_ov121_0229abac(UnkStruct_0229aab4 *self, u8 a);
extern void func_0206f190(volatile u16 *out, void *a, void *b, void *c);
extern void func_0209a000(volatile u16 *p, int a);
extern void func_ov121_0229afb8(UnkStruct_0229aab4 *self);
extern void RtcSendPxiCommand(int a);

void func_ov121_0229aab4(UnkStruct_0229aab4 *self)
{
    volatile u16 t[2];
    int ok;
    u16 lo;
    u16 hi;
    int a;
    int b;
    unsigned int n;
    u16 w;

    a = func_020984e8();
    b = func_02099fe8();
    t[0] = *func_020993a8(a);

    ok = 0;
    lo = t[0];
    hi = t[0];
    if (hi >= 0x11a8 && lo <= 0x12a7) {
        ok = 1;
    }

    if (ok != 0) {
        if (b == -1) {
            func_ov121_0229af7c(self, 4, 1);
            return;
        }
    }

    func_ov121_0229a50c(self);
    n = func_ov121_0229abac(self, self->unk_AE);
    if (n < 8) {
        w = (u16) (n + 0x12a8);
    } else {
        w = 0x12a8;
    }
    t[1] = w;

    func_0206f190(&t[1], (char *) self + 0x954, (char *) self + 0xd8, (char *) self + 0xb8);

    ok = 0;
    lo = t[0];
    hi = t[0];
    if (hi >= 0x11a8 && lo <= 0x12a7) {
        ok = 1;
    }

    if (ok != 0) {
        func_0209a000(t, 0);
    }

    func_ov121_0229afb8(self);
    RtcSendPxiCommand(0x6b);
}
