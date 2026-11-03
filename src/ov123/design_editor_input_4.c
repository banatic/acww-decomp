/* design_editor_input_4: 5 functions, module ov123
 * mwccarm 1.2/base -O4,s
 * func_ov123_0229a538 @ 0x0229a538, 0x94 bytes, Thumb
 * func_ov123_0229a4bc @ 0x0229a4bc, 0x7c bytes, Thumb
 * func_ov123_0229a438 @ 0x0229a438, 0x84 bytes, Thumb
 * func_ov123_0229a364 @ 0x0229a364, 0xd4 bytes, Thumb
 * func_ov123_0229a340 @ 0x0229a340, 0x22 bytes, Thumb
 */

#include "types.h"

typedef struct UnkStruct_0229a538 {
    u8 pad_00[0xa2];
    u8 unk_A2;
    u8 pad_A3;
    u8 unk_A4;
} UnkStruct_0229a538;

typedef struct UnkStruct_0229a438 {
    u8 pad_00[0xa4];
    u8 unk_A4;
    u8 pad_A5[3];
    u8 unk_A8;
    u8 unk_A9;
    u8 pad_AA[0xaf - 0xa9 - 1];
    u8 unk_AF;
    u8 unk_B0;
} UnkStruct_0229a438;

typedef struct UnkStruct_0229a364 {
    u8 pad_00[0xa2];
    u8 unk_A2;
    u8 pad_A3;
    u8 unk_A4;
    u8 pad_A5[3];
    u8 unk_A8;
    u8 unk_A9;
    u8 pad_AA[3];
    u8 unk_AD;
    u8 unk_AE;
} UnkStruct_0229a364;

struct func_ov123_0229a340_unk {
    unsigned char pad_00[0xaf];
    unsigned char unk_AF;
    unsigned char unk_B0;
};

extern int func_ov123_0229ac80(UnkStruct_0229a538 *self, int a, int b, u8 c, int d, int e);
extern void func_ov123_0229a5cc(UnkStruct_0229a538 *self, int a, int b, u8 c, int d);
extern void func_0200467c(int a);
extern void func_ov123_0229a654(UnkStruct_0229a538 *self, int a, int b, u8 c);
extern void func_ov123_0229a988(UnkStruct_0229a538 *self, u8 c);
extern void func_ov123_0229a918(UnkStruct_0229a538 *self, u8 c);
extern void func_ov123_0229ae24(void *);
extern void func_ov123_02299f08(void *);
extern void func_ov123_02299878(void *);
extern void func_ov123_02299e28(void *);
extern void func_ov123_02299640(void *, int);
extern unsigned char *func_ov002_02208098(UnkStruct_0229a438 *self, unsigned char value);
extern int func_ov123_02299650(UnkStruct_0229a364 *self, int a);
extern int func_ov123_0229ab80(UnkStruct_0229a364 *self, u8 a, u8 b, u8 c, u8 d, u8 e, int f);
extern void func_ov123_0229ab18(UnkStruct_0229a364 *self, int a, int b, int c, int d, u8 e);
extern void func_ov123_0229a9b0(UnkStruct_0229a364 *self, int a, int b, int c, int d, u8 e, int f);
extern int func_ov123_0229a8dc(void *ptr, unsigned char a, unsigned char b);
extern void func_ov123_0229b160(void *ptr, int val);

void func_ov123_0229a538(UnkStruct_0229a538 *self, int a, int b)
{
    u8 st = self->unk_A4;

    if (st <= 2) {
        func_ov123_0229ac80(self, a, b, self->unk_A2, st, 1);
    } else if (st >= 3 && st <= 4) {
        func_ov123_0229a5cc(self, a, b, self->unk_A2, st - 3);
        func_0200467c(0x867);
    } else {
        if (st >= 9 && st <= 0xb) {
            func_0200467c(0x867);
        }

        switch (self->unk_A4) {
            case 9:
                func_ov123_0229a654(self, a, b, self->unk_A2);
                break;
            case 0xb:
                func_ov123_0229a988(self, self->unk_A2);
                break;
            case 0xa:
                func_ov123_0229a918(self, self->unk_A2);
                break;
        }
    }
}

void func_ov123_0229a4bc(void *self)
{
    unsigned char v;
    func_ov123_0229ae24(self);
    v = *(unsigned char *) ((char *) self + 0xa4);
    if (v >= 6 && v <= 8) {
        func_ov123_02299f08(self);
        func_ov123_02299878(self);
        return;
    }
    func_ov123_02299e28(self);
    func_ov123_0229a538((UnkStruct_0229a538 *) self, (unsigned char) (*(unsigned char *) ((char *) self + 0xa8)), (unsigned char) (*(unsigned char *) ((char *) self + 0xa9)));
    v = *(unsigned char *) ((char *) self + 0xa4);
    if (v <= 2) {
        func_0200467c(0x85f);
        func_0200467c(0x861);
        func_ov123_02299640(self, 0x1000);
    }
    func_ov123_02299878(self);
    func_ov123_02299640(self, 0x40);
}

void func_ov123_0229a438(UnkStruct_0229a438 *self)
{
    self->unk_A8 = self->unk_AF;
    self->unk_A9 = self->unk_B0;

    if (self->unk_A4 >= 6 && self->unk_A4 <= 8) {
        func_ov123_02299f08((void *) self);
        func_ov002_02208098(self, 6);
    } else {
        func_ov123_02299e28((void *) self);
        func_ov123_0229a538((UnkStruct_0229a538 *) self, (u8) self->unk_A8, (u8) self->unk_A9);
        if (self->unk_A4 <= 2) {
            func_0200467c(0x85f);
            func_0200467c(0x861);
            func_ov002_02208098(self, 5);
        }
        func_ov123_02299640((void *) self, 0x40);
    }
}

inline u8 inline_fn(UnkStruct_0229a364 *arg0)
{
    return arg0->unk_AD;
}

void func_ov123_0229a364(UnkStruct_0229a364 *self)
{
    u8 a8;
    u8 a9;
    u8 ad;
    u8 ae;
    int x0;
    int x1;
    int y0;
    int y1;
    if (func_ov123_02299650(self, 0x100) == 0) {
        return;
    }
    if ((self->unk_A4 < 6) || (self->unk_A4 > 8)) {
        return;
    }
    func_ov123_02299e28((void *) self);
    a8 = self->unk_A8;
    ad = inline_fn(self);
    if (ad >= a8) {
        x0 = a8;
        x1 = ad;
    } else {
        x1 = a8;
        x0 = ad;
    }
    a9 = self->unk_A9;
    ae = self->unk_AE;
    if (ae >= self->unk_A9) {
        y1 = a9;
        y0 = ae;
    } else {
        y0 = a9;
        y1 = ae;
    }
    switch (self->unk_A4) {
        case 8:
            func_ov123_0229ab80(self, ad, ae, a8, a9, self->unk_A2, 0);
            break;

        case 6:
            func_ov123_0229ab18(self, x0, y1, x1, y0, self->unk_A2);
            break;

        case 7:
            func_ov123_0229a9b0(self, x0, y1, x1, y0, self->unk_A2, 0);
            break;
    }

    func_ov123_02299640((void *) self, 0x40);
    func_0200467c(0x867);
}

void func_ov123_0229a340(struct func_ov123_0229a340_unk *p)
{
    func_ov123_0229b160(p, func_ov123_0229a8dc(p, p->unk_AF, p->unk_B0));
}
