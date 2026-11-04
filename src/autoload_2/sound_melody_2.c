/* sound_melody_2: 2 functions, module autoload_2
 * mwccarm 1.2/base -O4,p
 * func_020f6350 @ 0x020f6350, 0x178 bytes, ARM
 * func_020f61e4 @ 0x020f61e4, 0x16c bytes, ARM
 */

#include "types.h"

typedef struct {
    unsigned char pad_00[0x3c];
    unsigned char unk_3C;
} State;

typedef struct {
    unsigned char pad_00[6];
    unsigned char unk_06;
    unsigned char pad_07[0x1d - 0x7];
    unsigned char unk_1D;
} UnkStruct_020f6350;

typedef struct {
    unsigned char pad_00[4];
    unsigned short unk_04;
    signed char unk_06;
    unsigned char pad_07[3];
    unsigned char unk_0A;
} Player;

typedef struct {
    unsigned char pad_00[0x28];
    void *unk_28;
    UnkStruct_020f6350 *unk_2C;
    State *unk_30;
} Glob;

// Sound/animation step; fx32 math with v == 100 handled separately.

struct UnkStruct_020f61e4 {
    int unk_00;
    unsigned short unk_04;
    signed char unk_06;
    unsigned char unk_07;
    signed char unk_08;
    signed char unk_09;
    unsigned char unk_0A;
    unsigned char unk_0B;
};

struct UnkStruct_020f61e4_2 {
    unsigned char pad_00[0xc];
    int unk_0C;
    unsigned char pad_10[2];
    unsigned char unk_12;
};

struct UnkStruct_020f61e4_3 {
    unsigned char pad_00[0x2c];
    struct UnkStruct_020f61e4_2 *unk_2C;
};

extern Glob data_021fd1bc;
extern unsigned char data_0213f0a4;
extern unsigned short data_021fd264;
extern int func_020eed18(Player *p, int n);
extern int NNS_SndArcPlayerStartSeqArc(Player *p, unsigned short seq, int flags);
extern void *func_020eef70(void);
extern void NNS_SndHeapLoadState(void *heap, int state);
extern int func_0210e1d0(unsigned short n, void *heap);
extern int func_0210e198(int n, void *heap);
extern int func_020eedb8(int, unsigned short, struct UnkStruct_020f61e4 *);
extern void func_020f6194(struct UnkStruct_020f61e4 *);
extern int func_020f6000(struct UnkStruct_020f61e4 *);
extern void func_020f609c(struct UnkStruct_020f61e4 *, int);
extern fx32 FX_Div(fx32, fx32);

void func_020f6350(Player *p, unsigned short value)
{
    State *st = data_021fd1bc.unk_30;
    UnkStruct_020f6350 *x;
    void *heap;
    unsigned short n;
    int flag;

    if (st->unk_3C == 1) {
        return;
    }

    func_020eed18(p, 0);
    st->unk_3C = 2;

    data_021fd264 = p->unk_04;
    p->unk_04 = value;
    flag = 0;
    p->unk_0A = 1;
    p->unk_06 = -1;

    if (NNS_SndArcPlayerStartSeqArc(p, p->unk_04, flag) != 0) {
        if (data_021fd264 == p->unk_04) {
            flag = 1;
        }
        func_020eed18(p, 0);
    }

    if (flag) {
        return;
    }

    x = data_021fd1bc.unk_2C;
    if (x == 0) {
        return;
    }

    if (x->unk_06 != 0) {
        data_0213f0a4 = 2;
    } else {
        data_0213f0a4 = (data_0213f0a4 == 1) ? 2 : 1;
    }

    if (data_0213f0a4 == 1) {
        heap = func_020eef70();
        NNS_SndHeapLoadState(heap, x->unk_1D + 1);
    } else if (data_0213f0a4 == 2) {
        heap = data_021fd1bc.unk_28;
        func_020eef70();
        NNS_SndHeapLoadState(heap, 0);
    }

    n = p->unk_04;
    func_0210e1d0(n, heap);
    func_0210e198(n + 0x25f, heap);
}

void func_020f61e4(struct UnkStruct_020f61e4 *self, int a1)
{
    struct UnkStruct_020f61e4_2 *k;
    unsigned char en;
    int r;
    int v;
    int t;
    int flag;

    if (self->unk_0A == 0) {
        return;
    }
    if (self->unk_08 == -1) {
        flag = (self->unk_00 != 0);
        switch (flag) {
            case 0:
                func_020eedb8(0, self->unk_04, self);
                break;
            default:
                break;
        }
        func_020f6194(self);
        return;
    }
    self->unk_07 = self->unk_07 + 1;
    k = (*(struct UnkStruct_020f61e4_3 *) &data_021fd1bc).unk_2C;
    en = k->unk_12;
    if (self->unk_07 >= self->unk_0B) {
        r = func_020f6000(self);
        self->unk_07 = 0;
        if (r) {
            return;
        }
    }
    if (en == 0) {
        return;
    }
    self->unk_06 = self->unk_06 + 1;
    self->unk_07 = 0;
    if (self->unk_06 < 0x10) {
        func_020f609c(self, a1);
    } else if (self->unk_06 >= 0x10) {
        func_020f6000(self);
        return;
    }
    v = self->unk_08;
    t = k->unk_0C;
    if (v == 0x64) {
        self->unk_0B = (unsigned char) (t >> 12);
        return;
    }
    self->unk_0B = (unsigned char) ((fx32) (((long long) t * FX_Div(v << 12, 0x64000) + 0x800) >> 12) >> 12);
}
