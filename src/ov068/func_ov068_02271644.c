/* func_ov068_02271644 @ 0x02271644, 0x19c bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct Vec {
    int x, y, z;
} Vec;
typedef struct UnkStruct_02271644_2 {
    int a;
} UnkStruct_02271644_2;
typedef struct UnkStruct_02271644 {
    u8 pad_00[0x5c];
    int v;
} UnkStruct_02271644;

typedef struct UnkStruct_02271644_3 {
    u8 pad_00[0x1e0];
    UnkStruct_02271644_2 sub;
    u8 pad_1E4[0x204 - 0x1e4];
    Vec vec;
    u8 pad_210[0x238 - 0x210];
    short unk_238;
    short unk_23A;
    u8 pad_23C[0x24a - 0x23c];
    u8 unk_24A;
    u8 unk_24B;
    u8 unk_24C;
    s8 unk_24D;
    u8 pad_24E[1];
    u8 unk_24F;
    u8 pad_250[0x257 - 0x250];
    u8 unk_257;
} UnkStruct_02271644_3;

extern int func_020644cc(int);
extern int func_ov003_02234d70(UnkStruct_02271644_3 *);
extern UnkStruct_02271644 *func_020961a8(int);
extern void func_ov003_0222d518(UnkStruct_02271644_3 *, int);
extern int func_ov068_02271494(UnkStruct_02271644_3 *, UnkStruct_02271644_2 *);
extern int FX_Div(int, int);

void func_ov068_02271644(UnkStruct_02271644_3 *self)
{
    unsigned int n;
    UnkStruct_02271644_2 *p;
    int t;
    volatile int sx, sy, sz;
    Vec *v;
    int old24b, old24c;
    UnkStruct_02271644 *s;
    int *q;
    short d;

    old24b = self->unk_24B;
    n = (u8) func_020644cc(0x64);
    v = &self->vec;
    p = &self->sub;
    old24c = self->unk_24C;
    sx = v->x;
    sy = v->y;
    sz = v->z;
    func_ov003_02234d70(self);
    if (self->unk_24A) {
        s = func_020961a8(4);
        if (s == 0) {
            return;
        }
        q = &s->v;
        if (self->unk_238 != 1) {
            return;
        }
        if (self->unk_24D != 8) {
            return;
        }
        d = (short) ((v->x > *q) ? 0x2aaa : -0x2aaa);
        self->unk_238 = 0;
        self->unk_23A = d;
        func_ov003_0222d518(self, 0x119a);
        return;
    }
    t = self->unk_24F;
    if (t % 10 == 0 && n > 0x1e) {
        self->unk_24C = (u8) (old24c == 0);
    } else if (t % 5 == 0 && n > 0x1e) {
        self->unk_24B = (u8) (old24b == 0);
    }
    if (old24b) {
        v->x = v->x + self->unk_257 * 0x30;
    } else {
        v->x = v->x - self->unk_257 * 0x30;
    }
    if (old24c) {
        v->y = v->y + self->unk_257 * 0x30;
    } else {
        v->y = v->y - self->unk_257 * 0x30;
    }
    if (func_ov068_02271494(self, p)) {
        self->unk_24B = (u8) (old24b == 0);
        v->x = sx;
    }
    if (FX_Div(0x15000, 0x10000) > v->y || FX_Div(0x32000, 0x10000) < v->y) {
        self->unk_24C = (u8) (old24c == 0);
        v->y = sy;
    }
}
