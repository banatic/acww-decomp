/* func_02012e58 @ 0x02012e58, 0x368 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

// func_02012e58  main  0x02012e58  0x368  Thumb

typedef struct Pair {
    int x;
    int y;
} Pair;
typedef struct UnkStruct_02012e58 {
    u8 unk_00;
    u8 unk_01;
    u8 lo : 4;
    u8 hi : 4;
} UnkStruct_02012e58;
typedef struct Vec {
    int x;
    int y;
    int z;
} Vec;
typedef struct Vec4 {
    int x;
    int y;
    int z;
    int w;
} Vec4;

typedef struct UnkStruct_02012e58_2 {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    u8 pad_14[0x1c - 0x14];
    int unk_1C;
    int unk_20;
    u8 pad_24[0x88 - 0x24];
    int unk_88;
    int unk_8C;
    int unk_90;
} UnkStruct_02012e58_2;

typedef struct UnkStruct_02012e58_3 {
    int unk_00;
    u8 pad_04[8];
    Pair unk_0C;
} UnkStruct_02012e58_3;

extern UnkStruct_02012e58_3 *data_021c80bc;

extern int func_0204ed30(UnkStruct_02012e58_3 *c, int);
extern int func_0201354c(UnkStruct_02012e58_2 *s, int *p, int a);
extern void func_02013440(UnkStruct_02012e58_2 *s);
extern int func_020131c0(UnkStruct_02012e58_2 *s, int a);
extern void func_0204f818(int *a, int *b, int c);
extern int func_02013450(UnkStruct_02012e58_2 *s, Pair *o, Pair *p, int bits, Pair *c, UnkStruct_02012e58_3 *ctx);
extern int func_02013384(UnkStruct_02012e58_2 *s, Pair *p);
extern UnkStruct_02012e58 func_02013304(UnkStruct_02012e58_2 *s, Pair *p);
extern void func_0204f794(void *d, int a, int b);
extern int func_020ea990(void *a, void *b);
extern void func_020133b4(UnkStruct_02012e58_2 *s, int a, int b, Pair *p);

void func_02012e58(UnkStruct_02012e58_2 *self, int arg)
{
    int s0c;
    int v;
    int m2;
    int s18;
    int best;
    int i;
    int n1;
    int n2;
    int s2c;
    int bx;
    int by;
    int s38;
    int j;
    Pair cp;
    Pair pos;
    Pair outp;
    UnkStruct_02012e58 outA;
    UnkStruct_02012e58 outB;
    Pair t1;
    Pair t2;
    Pair t3;
    Pair t4;
    Pair t5;
    Vec d1;
    Vec4 d2;
    UnkStruct_02012e58_3 *ctx;
    int mask;
    int found;
    int d;
    Pair *q;

    ctx = data_021c80bc;
    if (ctx == 0) {
        return;
    }
    v = func_0204ed30(ctx, arg);
    if (v == 0) {
        self->unk_90 = func_0201354c(self, &self->unk_1C, arg);
        self->unk_04 = 0;
        func_02013440(self);
        self->unk_88 = 0;
        self->unk_8C = 2;
        return;
    }
    mask = func_020131c0(self, self->unk_88);
    m2 = mask;
    q = &ctx->unk_0C;
    cp.x = q->x;
    cp.y = q->y;
    bx = 0;
    pos.x = 0;
    pos.y = 0;
    by = 0;
    found = 0;
    outp.x = 0;
    outp.y = 0;
    best = -0x1000;
    func_0204f818(&pos.x, &pos.y, arg);
    if ((v & ~mask) == 0) {
        t1.x = pos.x;
        t1.y = pos.y;
        if (func_02013450(self, &outp, &t1, mask, &cp, ctx) != 0) {
            self->unk_1C = outp.x;
            self->unk_20 = outp.y;
            self->unk_8C = 1;
            self->unk_88 = mask;
        }
    } else if (self->unk_8C != 1) {
        n1 = 0;
        n2 = self->unk_88;
        if (func_02013384(self, &pos) != ~0) {
            outA = func_02013304(self, &pos);
            n1 = outA.hi;
            n2 = outA.lo;
            m2 |= n1;
        }
        func_0204f794(&d2, self->unk_0C, self->unk_10);
        for (i = 0; i < 4; i++) {
            if (((m2 >> i) & 1) != 0) {
                continue;
            }
            s18 = v;
            s18 &= (1 << i);
            if (s18 == 0) {
                continue;
            }
            t2.x = pos.x;
            t2.y = pos.y;
            if (func_02013450(self, &outp, &t2, s18, &cp, ctx) == 0) {
                continue;
            }
            func_0204f794(&d1, outp.x, outp.y);
            d = func_020ea990(&d2, &d1);
            if (best < 0 || d < best) {
                bx = outp.x;
                by = outp.y;
                best = d;
                found = s18;
            }
        }
        if (found != 0) {
            if (self->unk_8C == 0) {
                func_020133b4(self, n1 | found, n2, &pos);
                n1 |= found;
            }
            self->unk_1C = bx;
            self->unk_20 = by;
            self->unk_8C = 0;
            self->unk_88 = found;
        } else {
            t3.x = pos.x;
            t3.y = pos.y;
            if (func_02013450(self, &outp, &t3, mask, &cp, ctx) != 0) {
                self->unk_1C = outp.x;
                self->unk_20 = outp.y;
                self->unk_8C = 1;
                self->unk_88 = mask;
            }
        }
        self->unk_04 = 1;
    } else if (self->unk_8C == 1) {
        outB = func_02013304(self, &pos);
        s0c = outB.lo;
        s2c = func_020131c0(self, s0c);
        func_0204f794(&d2, self->unk_0C, self->unk_10);
        mask |= s2c;
        for (j = 0; j < 4; j++) {
            if (((mask >> j) & 1) != 0) {
                continue;
            }
            s38 = v;
            s38 &= (1 << j);
            if (s38 == 0) {
                continue;
            }
            t4.x = pos.x;
            t4.y = pos.y;
            if (func_02013450(self, &outp, &t4, s38, &cp, ctx) == 0) {
                continue;
            }
            func_0204f794(&d1, outp.x, outp.y);
            d = func_020ea990(&d2, &d1);
            if (best < 0 || d < best) {
                bx = outp.x;
                by = outp.y;
                best = d;
                found = s38;
            }
        }
        if (found != 0) {
            if (s0c == 0) {
                s0c = self->unk_88;
            }
            self->unk_1C = bx;
            self->unk_20 = by;
            func_020133b4(self, outB.hi | found, s0c, &pos);
            self->unk_8C = 0;
            self->unk_88 = found;
        } else {
            t5.x = pos.x;
            t5.y = pos.y;
            if (func_02013450(self, &outp, &t5, s2c, &cp, ctx) != 0) {
                self->unk_1C = outp.x;
                self->unk_20 = outp.y;
                self->unk_8C = 1;
                self->unk_88 = s2c;
            }
        }
        self->unk_04 = 1;
    }
    self->unk_90 = 4;
}
