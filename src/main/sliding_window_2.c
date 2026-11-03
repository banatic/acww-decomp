/* sliding_window_2: 20 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0208a9c8 @ 0x0208a9c8, 0x1a bytes, Thumb
 * func_0208a9ac @ 0x0208a9ac, 0x1a bytes, Thumb
 * func_0208a9a4 @ 0x0208a9a4, 0x6 bytes, Thumb
 * func_0208a978 @ 0x0208a978, 0x2c bytes, Thumb
 * func_0208a944 @ 0x0208a944, 0x34 bytes, Thumb
 * func_0208a8d4 @ 0x0208a8d4, 0x6e bytes, Thumb
 * func_0208a8cc @ 0x0208a8cc, 0x6 bytes, Thumb
 * func_0208a8ac @ 0x0208a8ac, 0x20 bytes, Thumb
 * func_0208a890 @ 0x0208a890, 0x1a bytes, Thumb
 * func_0208a848 @ 0x0208a848, 0x48 bytes, Thumb
 * func_0208a844 @ 0x0208a844, 0x4 bytes, Thumb
 * func_0208a840 @ 0x0208a840, 0x4 bytes, Thumb
 * func_0208a824 @ 0x0208a824, 0x1a bytes, Thumb
 * func_0208a80c @ 0x0208a80c, 0x16 bytes, Thumb
 * func_0208a808 @ 0x0208a808, 0x4 bytes, Thumb
 * func_0208a804 @ 0x0208a804, 0x4 bytes, Thumb
 * func_0208a7f0 @ 0x0208a7f0, 0x14 bytes, Thumb
 * func_0208a784 @ 0x0208a784, 0x6c bytes, Thumb
 * func_0208a738 @ 0x0208a738, 0x4c bytes, Thumb
 * func_0208a664 @ 0x0208a664, 0xd4 bytes, Thumb
 */

#include "types.h"

typedef struct {
    unsigned char pad_00[52];
    unsigned long unk_34;
} UnkStruct_0208a9a4;

typedef struct {
    unsigned char pad_00[0x54];
    unsigned char unk_54;
} UnkStruct_0208a978;

typedef struct UnkStruct0908A944 {
    char pad_00[0x34];
    int unk_34;
    int unk_38;
    char pad_3C[0x0c];
    int unk_48;
    int unk_4C;
    char pad_50[0x09];
    unsigned char unk_59;
    unsigned char unk_5A;
} UnkStruct_0208a944;

typedef struct {
    unsigned char pad_00[52];
    unsigned long unk_34;
} UnkStruct_0208a8cc;

typedef struct {
    unsigned char pad_00[0x34];
    int unk_34;
    int unk_38;
    unsigned char pad_3C[0x1D];
    unsigned char unk_59;
} UnkStruct_0208a890;

struct UnkStruct_0208a848 {
    char pad_00[0x38];
    int unk_38;
    char pad_3C[0xc];
    int unk_48;
    int unk_4C;
    char pad_50[0x9];
    unsigned char unk_59;
    unsigned char unk_5A;
};

typedef struct {
    char pad_00[0x3c];
    int unk_3C;
    char pad_40[0x8];
    int unk_48;
    char pad_4C[0x4];
    int unk_50;
} UnkStruct_0208a824;

typedef struct {
    char pad_00[0x40];
    int unk_40;
    char pad_44[8];
    int unk_4C;
} UnkStruct_0208a80c;

typedef struct UnkStruct_0208a664 UnkStruct_0208a664;

struct UnkStruct_0208a664 {
    void **vtable;
    unsigned char pad_04[0x30 - 4];
    int unk_30;
};

typedef struct RetStruct {
    int unk_00;
    int unk_04;
} RetStruct;

extern void func_0208a510(void *);
extern void func_0208a4dc(struct UnkStruct_0208a848 *self);
extern int func_0208aef0(UnkStruct_0208a824 *);
extern int func_0208aeec(UnkStruct_0208a80c *);
extern int func_0208a1cc(void *ptr);
extern void func_02051ad8(void *p);
extern void func_0208a1f0(void *p, const void *q);
extern void func_0208a1ec(void *p, int q);
extern void *func_0208a1e8(void *p, int q);
extern const char data_020d71a4[];
extern const char data_020d71ac[];
extern RetStruct *func_0208a1c8(void *p);
extern void *func_0208a1e0(void *p, int v, int z);

void func_0208a944(UnkStruct_0208a944 *p);
void func_0208a8cc(UnkStruct_0208a8cc *p);
void func_0208a890(UnkStruct_0208a890 *s);
void func_0208a664(void *self);

void *func_0208a9c8(void *arg0)
{
    unsigned char *ptr;
    int r2;
    int r1;

    r1 = *(int *) ((char *) arg0 + 0x34);
    if (r1 == 0) {
        r2 = 1;
    } else {
        r2 = 0;
    }
    if (r2 != 0) {
        r1 = 1;
        ptr = (unsigned char *) ((char *) arg0 + 0x54);
        *ptr = (unsigned char) r1;
    }
    return (void *) r2;
}

void *func_0208a9ac(void *r0)
{
    unsigned char *r0_2;
    int r1;
    int r2;

    r1 = *(int *) ((char *) r0 + 0x34);
    if (r1 == 2) {
        r2 = 1;
    } else {
        r2 = 0;
    }

    if (r2 != 0) {
        r1 = 1;
        r0_2 = (unsigned char *) ((char *) r0 + 0x55);
        *r0_2 = (unsigned char) r1;
    }

    return (void *) (unsigned int) r2;
}

void func_0208a9a4(UnkStruct_0208a9a4 *p)
{
    p->unk_34 = 0;
}

void func_0208a978(UnkStruct_0208a978 *p)
{
    if (p->unk_54) {
        p->unk_54 = 0;
        func_0208a510(p);
        func_0208a664(p);
        func_0208a944((UnkStruct_0208a944 *) p);
    }
}

void func_0208a944(UnkStruct_0208a944 *p)
{
    if (p->unk_59 != 0) {
        p->unk_38 = 1;
        p->unk_48 = 0;
        p->unk_4C = 0;
    } else {
        p->unk_38 = 3;
        p->unk_48 = -5;
        p->unk_4C = (p->unk_5A == 0) ? 5 : -5;
    }
    p->unk_34 = 1;
}

void func_0208a8d4(unsigned char *r0)
{
    unsigned char *p;
    int r1, r2;

    p = r0 + 0x59;
    if (*p == 0) {
        if (*(int *) (r0 + 0x38) > 2) {
            *(int *) (r0 + 0x48) += 6;
            p = r0 + 0x5a;
            if (*p != 0) {
                r2 = 6;
            } else {
                r1 = 5;
                r2 = ~r1;
            }
            *(int *) (r0 + 0x4c) += r2;
        } else {
            *(int *) (r0 + 0x48) -= 1;
            p = r0 + 0x5a;
            if (*p != 0) {
                r1 = 0;
                r2 = ~r1;
            } else {
                r2 = 1;
            }
            *(int *) (r0 + 0x4c) += r2;
        }
    }
    *(int *) (r0 + 0x38) -= 1;
    if (*(int *) (r0 + 0x38) > 0) {
        return;
    }
    *(int *) (r0 + 0x48) = 0;
    *(int *) (r0 + 0x4c) = 0;
    func_0208a8cc((UnkStruct_0208a8cc *) r0);
}

void func_0208a8cc(UnkStruct_0208a8cc *p)
{
    p->unk_34 = 2;
}

void func_0208a8ac(unsigned char *p)
{
    if (p[0x55]) {
        p[0x55] = 0;
        func_0208a890((UnkStruct_0208a890 *) p);
    }
}

void func_0208a890(UnkStruct_0208a890 *s)
{
    if (s->unk_59 != 0) {
        s->unk_38 = 1;
    } else {
        s->unk_38 = 2;
    }
    s->unk_34 = 3;
}

void func_0208a848(struct UnkStruct_0208a848 *self)
{
    if (self->unk_59 == 0) {
        self->unk_48 -= 11;
        self->unk_4C += (self->unk_5A ? -11 : 11);
    }
    self->unk_38 -= 1;
    if (self->unk_38 <= 0) {
        func_0208a4dc(self);
        func_0208a9a4((UnkStruct_0208a9a4 *) self);
    }
}

int func_0208a844(int *p0)
{
    return p0[13];
}

int func_0208a840(int p0)
{
    return ((int) (p0) + (12));
}

int func_0208a824(UnkStruct_0208a824 *s)
{
    int a;
    a = func_0208aef0(s);
    return s->unk_3C + a + s->unk_48 + s->unk_50;
}

int func_0208a80c(UnkStruct_0208a80c *s)
{
    int r = func_0208aeec(s);
    int b = s->unk_4C;
    int a = s->unk_40;
    return b + (a + r);
}

int func_0208a808(int *p0)
{
    return p0[15];
}

int func_0208a804(int *p0)
{
    return p0[16];
}

int func_0208a7f0(void *ptr)
{
    int result;
    result = func_0208a1cc((char *) ptr + 0xc);
    return (result << 3) + 0x18;
}

void func_0208a784(void *p)
{
    unsigned int *u32 = (unsigned int *) p;
    unsigned char *u8 = (unsigned char *) p;
    u32[0x34 >> 2] = 0;
    u32[0x38 >> 2] = 0;
    u32[0x3c >> 2] = 0;
    u32[0x40 >> 2] = 0;
    u32[0x44 >> 2] = -1;
    u32[0x48 >> 2] = 0;
    u32[0x4c >> 2] = 0;
    u32[0x50 >> 2] = 0;
    u8[0x54] = 0;
    u8[0x55] = 0;
    u8[0x57] = 0;
    u8[0x58] = 0;
    u8[0x59] = 0;
    u8[0x5a] = 0;
    u8[0x5b] = 0;
    u8[0x5c] = 0;
    func_02051ad8((char *) p + 0x60);
    func_02051ad8((char *) p + 0x90);
    *(unsigned int *) ((char *) p + 0xc8) = 0;
    func_0208a4dc((struct UnkStruct_0208a848 *) p);
}

void func_0208a738(void *p)
{
    func_0208a1f0((char *) p + 0xc, data_020d71a4);
    func_0208a1ec((char *) p + 0xc, 1);
    func_0208a1e8((char *) p + 0xc, 0);
    func_0208a1f0((char *) p + 0x20, data_020d71ac);
    func_0208a1ec((char *) p + 0x20, 1);
    func_0208a1e8((char *) p + 0x20, 0);
}

void func_0208a664(void *self)
{
    u32 r6;
    u32 r7;
    UnkStruct_0208a664 *p0;
    UnkStruct_0208a664 *p1;
    int maxVal;
    int r;
    int slot;
    u32 shift;
    p0 = *((UnkStruct_0208a664 **) (((char *) self) + 0xc0));
    if (p0) {
        r6 = ((int (*)(UnkStruct_0208a664 *)) p0->vtable[3])(p0);
    } else {
        r6 = 0;
    }
    p1 = *((UnkStruct_0208a664 **) (((char *) self) + 0xc4));
    if (p1) {
        maxVal = ((int (*)(UnkStruct_0208a664 *)) p1->vtable[3])(p1);
        r7 = maxVal;
    } else {
        r7 = 0;
    }
    {
        u32 a = (r6 + 7) >> 3;
        u32 b = (r7 + 7) >> 3;
        int r4 = (a > b) ? ((int) a) : ((int) b);
        maxVal = func_0208a1c8(((char *) self) + 0xc)->unk_04 - 1;
        r = r4 - 1;
        slot = maxVal;
        if (r < 0) {
            slot = 0;
        } else if (r <= maxVal) {
            slot = r;
        }
        func_0208a1e0(((char *) self) + 0xc, slot, 0);
        func_0208a1e0(((char *) self) + 0x20, slot, 0);
        if ((*((unsigned char *) (((char *) self) + 0x5c))) != 0) {
            shift = ((u32) r4) << 3;
            p0 = *((UnkStruct_0208a664 **) (((char *) self) + 0xc0));
            if (p0) {
                p0->unk_30 = (shift > r6) ? ((shift - r6) >> 1) : (0);
            }
            p1 = *((UnkStruct_0208a664 **) (((char *) self) + 0xc4));
            if (p1) {
                p1->unk_30 = (shift > r7) ? ((shift - r7) >> 1) : (0);
            }
        } else {
            p0 = *((UnkStruct_0208a664 **) (((char *) self) + 0xc0));
            if (p0) {
                p0->unk_30 = 0;
            }
            p1 = *((UnkStruct_0208a664 **) (((char *) self) + 0xc4));
            if (p1) {
                p1->unk_30 = 0;
            }
        }
    }
}
