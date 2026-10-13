/* func_020aa888 @ 0x020aa888, 0x138 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_020aa888 {
    void *unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    u8 pad_14[0x30 - 0x14];
    u8 unk_30;
} UnkStruct_020aa888;

extern int func_020abd98(void *p);
extern int func_020a7e50(void);
extern int func_020a8028(int *a, int *b);
extern int func_020abcfc(void *p);
extern int func_020abd14(void *p);
extern int _s32_div_f(int a, int b);
extern int func_020a7e44(void);
extern int func_020a7ebc(void);
extern int func_020a7e94(void);
extern void RtcSendPxiCommand(int a, int _x);

void func_020aa888(UnkStruct_020aa888 *self)
{
    // DECLS
    int hiV;
    int lo;
    int a;
    int t;
    int loV;
    int d;
    int v;
    int b;
    int m;
    int up;
    int hit;
    int i;
    int dn;
    int gt;
    int hi;
    // ENDDECLS

    if (self->unk_30 == 0) {
        goto L950;
    }
    if (func_020abd98(self->unk_00) == 0) {
        goto L950;
    }
    if (func_020a7e50() != 0) {
        if (func_020a8028(&a, &b) != 0) {
            lo = func_020abcfc(self->unk_00);
            hi = func_020abd14(self->unk_00);
            v = b - self->unk_10;
            if (v < hi) {
                v = hi;
            } else if (v > lo) {
                v = lo;
            }
            self->unk_08 = _s32_div_f((v - lo) << 12, hi - lo);
        }
        self->unk_04 = 0;
        goto L950;
    }
    if (func_020a7e44() == 0) {
        goto L950;
    }
    up = func_020a7ebc();
    dn = func_020a7e94();
    if (up == 0 && dn == 0) {
        self->unk_04 = 0x28;
    } else {
        self->unk_04 = self->unk_04 + 0x51;
        t = self->unk_04;
        if (t < 0) {
            t = 0;
        } else if (t > 0x199) {
            t = 0x199;
        }
        self->unk_04 = t;
    }
    if (up != 0) {
        self->unk_08 = self->unk_08 + self->unk_04;
    }
    if (dn != 0) {
        self->unk_08 = self->unk_08 - self->unk_04;
    }
    d = self->unk_08;
    if (d < 0) {
        d = 0;
    } else if (d > 0x1000) {
        d = 0x1000;
    }
    self->unk_08 = d;
L950:
    loV = self->unk_0C;
    d = self->unk_08;
    t = d - loV;
    if (t < 0) {
        t = -t;
    }
    if (t < 0x51) {
        goto Lend;
    }
    if (d > loV) {
        gt = 1;
    } else {
        gt = 0;
    }
    if (gt != 0) {
        hiV = d;
    } else {
        hiV = loV;
    }
    if (gt == 0) {
        loV = d;
    }
    hit = 0;
    i = 0;
    goto test;
body:
    m = 0x199 * i;
    if (m >= loV) {
        if (m < hiV) {
            hit = 1;
            goto after;
        }
    }
    i++;
test:
    if (i < 0xa) {
        goto body;
    }
after:
    if (hiV == 0x1000) {
        hit = 1;
    }
    if (hit != 0) {
        RtcSendPxiCommand(0x19, hiV);
    }
Lend:
    self->unk_0C = self->unk_08;
}
