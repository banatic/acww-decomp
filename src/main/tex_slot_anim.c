/* tex_slot_anim: 11 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02057768 @ 0x02057768, 0xe bytes, Thumb
 * func_02057764 @ 0x02057764, 0x2 bytes, Thumb
 * func_02057730 @ 0x02057730, 0x32 bytes, Thumb
 * func_0205772c @ 0x0205772c, 0x2 bytes, Thumb
 * func_020576cc @ 0x020576cc, 0x60 bytes, Thumb
 * func_02057694 @ 0x02057694, 0x38 bytes, Thumb
 * func_02057658 @ 0x02057658, 0x3c bytes, Thumb
 * func_02057640 @ 0x02057640, 0x16 bytes, Thumb
 * func_020575e4 @ 0x020575e4, 0x5c bytes, Thumb
 * func_02057538 @ 0x02057538, 0xaa bytes, Thumb
 * func_020574c4 @ 0x020574c4, 0x72 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_020576cc {
    unsigned int unk_00;
    unsigned int unk_04;
    unsigned int unk_08;
    unsigned int unk_0C;
    unsigned int unk_10;
    char pad_14[4];
    char sub18[0x38];
    unsigned int unk_50;
    char sub54[0x11];
    char sub65[0x13];
    unsigned int unk_78;
    unsigned int unk_7C;
    int unk_80;
    int unk_84;
    int unk_88;
};

typedef struct {
    char pad_00[0x50];
    int unk_50;
    char pad_54[0x24];
    int unk_78;
    int unk_7C;
    int unk_80;
    int unk_84;
} UnkStruct_02057640;

typedef struct {
    u8 pad_00[0x50];
    void *unk_50;
    u8 unk_54[0x11];
    u8 unk_65[0x13];
    void *unk_78;
    void *unk_7C;
    u8 pad_80[0x8c - 0x80];
    u8 unk_8C;
} UnkStruct_020575e4;

typedef struct UnkStruct_02057538 {
    unsigned char pad_00[0x18];
    unsigned char unk_18;
    unsigned char pad_19[0x37];
    int unk_50;
    unsigned char unk_54;
    unsigned char pad_55[0x10];
    unsigned char unk_65;
    unsigned char pad_66[0x12];
    int unk_78;
    unsigned char pad_7C[0x04];
    int unk_80;
    int unk_84;
    int unk_88;
    unsigned char unk_8C;
} UnkStruct_02057538;

typedef struct {
    u8 pad_00[8];
    u32 unk_08;
    u8 pad_0C[0x78 - 0xc];
    u8 *unk_78;
    u32 unk_7C;
} UnkStruct_020574c4;

extern unsigned int strlen(const char *);
extern void *func_020578ec(void *);
extern unsigned int data_020dd184;
extern void *func_020578d4(void *);
extern void func_02057054(void *);
extern unsigned char data_020dd194[];
extern void func_020edb3c(void *);
extern void func_02056fcc(void *p0, int p1, int p2, int p3, int p4);
extern void func_02056ffc(void *);
extern int func_02057778(void *, int, const char *, const char *, int, int, int);
extern void *NNSi_G3dGetTexPatAnmFV(u32, u32, u32);
extern int NNSi_G3dGetTexPatAnmTexNameByIdx(u32, u8);
extern int NNSi_G3dGetTexPatAnmPlttNameByIdx(u32, u8);
extern int NNS_G3dGetResDictIdxByName(u8 *, int);

void func_02057640(UnkStruct_02057640 *s);
int func_02057538(UnkStruct_02057538 *self);
void func_020574c4(UnkStruct_020574c4 *s, int *out2, int *out1);

void func_02057768(unsigned char *p)
{
    unsigned int i;
    unsigned char val;
    i = 0;
    val = (unsigned char) i;
    do {
        p[i] = val;
        i++;
    } while (i < 17);
}

void func_02057764(void *object) {}

void func_02057730(char *dst, const char *src)
{
    if (src) {
        unsigned int n = strlen(src) + 1;
        unsigned int i;
        for (i = 0; i < 17; i++) {
            if (i < n) {
                dst[i] = src[i];
            } else {
                dst[i] = 0;
            }
        }
    }
}

const char *func_0205772c(const void *text)
{
    return (const char *) text;
}

struct UnkStruct_020576cc *func_020576cc(struct UnkStruct_020576cc *s)
{
    s->unk_00 = (unsigned int) &data_020dd184;
    s->unk_08 = 0;
    s->unk_0C = 0;
    s->unk_10 = 0x1000;
    s->unk_00 = (unsigned int) ((unsigned int *) data_020dd194);
    func_020578ec(&s->sub18);
    func_02057768((unsigned char *) s->sub54);
    func_02057768((unsigned char *) s->sub65);
    s->unk_50 = 0;
    s->unk_78 = 0;
    s->unk_7C = 0;
    s->unk_80 = -1;
    s->unk_84 = -1;
    s->unk_88 = -1;
    return s;
}

void *func_02057694(void *self)
{
    *(void **) self = (void *) data_020dd194;
    func_02057640((UnkStruct_02057640 *) self);
    func_02057764((char *) self + 0x65);
    func_02057764((char *) self + 0x54);
    func_020578d4((char *) self + 0x18);
    func_02057054(self);
    return self;
}

void *func_02057658(void *obj)
{
    ((unsigned int *) obj)[0] = (unsigned int) ((unsigned char *) data_020dd194);
    func_02057640((UnkStruct_02057640 *) obj);
    func_02057764((char *) obj + 0x65);
    func_02057764((char *) obj + 0x54);
    func_020578d4((char *) obj + 0x18);
    func_02057054(obj);
    func_020edb3c(obj);
    return obj;
}

void func_02057640(UnkStruct_02057640 *s)
{
    s->unk_50 = 0;
    s->unk_78 = 0;
    s->unk_7C = 0;
    s->unk_80 = -1;
    s->unk_84 = -1;
}

int func_020575e4(UnkStruct_020575e4 *p, void *b, void *c, void *d, void *e, void *f, u8 g)
{
    func_02057640((UnkStruct_02057640 *) p);
    p->unk_8C = g;
    func_02057730((char *) p->unk_54, (const char *) c);
    func_02057730((char *) p->unk_65, (const char *) d);
    p->unk_50 = b;
    p->unk_78 = e;
    p->unk_7C = f;
    func_02056fcc(p, *(u16 *) ((u8 *) f + 4), 0, 0x1000, 0);
    func_02057538((UnkStruct_02057538 *) p);
    return 1;
}

int func_02057538(UnkStruct_02057538 *self)
{
    int local0, local1;

    self->unk_88 = self->unk_84;
    func_02056ffc(self);
    func_020574c4((UnkStruct_020574c4 *) self, &local0, &local1);

    if (self->unk_84 == local0 || self->unk_8C != 0) {
        local0 = -1;
    }
    if (self->unk_80 == local1) {
        local1 = -1;
    }

    {
        const char *r4 = func_0205772c(&self->unk_54);
        const char *r3 = func_0205772c(&self->unk_65);
        if (func_02057778(&self->unk_18, self->unk_50, r4, r3, self->unk_78, local0, local1) != 0) {
            if (local0 != -1) {
                self->unk_84 = local0;
            }
            if (local1 != -1) {
                self->unk_80 = local1;
            }
            return 1;
        }
    }
    return 0;
}

void func_020574c4(UnkStruct_020574c4 *s, int *out2, int *out1)
{
    u8 *v;
    int a, b, x, x2;

    *out1 = -1;
    *out2 = *out1;
    v = NNSi_G3dGetTexPatAnmFV(s->unk_7C, 0, (s->unk_08 << 4) >> 16);
    if (v != 0) {
        a = NNSi_G3dGetTexPatAnmTexNameByIdx(s->unk_7C, v[2]);
        b = NNSi_G3dGetTexPatAnmPlttNameByIdx(s->unk_7C, v[3]);
        if (a != 0) {
            x = NNS_G3dGetResDictIdxByName(s->unk_78 + 0x3c, a);
        } else {
            x = -1;
        }
        *out2 = x;
        {
            u8 *addr = s->unk_78 + *(u16 *) (s->unk_78 + 0x34);
            if (b != 0) {
                x2 = NNS_G3dGetResDictIdxByName(addr, b);
            } else {
                x2 = -1;
            }
            *out1 = x2;
        }
    }
}
