/* scene_music: 7 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02036714 @ 0x02036714, 0x40 bytes, Thumb
 * func_020366e0 @ 0x020366e0, 0x34 bytes, Thumb
 * func_020366c0 @ 0x020366c0, 0x20 bytes, Thumb
 * func_0203668c @ 0x0203668c, 0x34 bytes, Thumb
 * func_0203665c @ 0x0203665c, 0x2e bytes, Thumb
 * func_02036648 @ 0x02036648, 0x14 bytes, Thumb
 * func_02036584 @ 0x02036584, 0xc2 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_020366e0 {
    char pad_00[10];
    unsigned short unk_0A;
};

struct UnkStruct_020366c0 {
    char pad_00[10];
    unsigned short unk_0A;
};

struct UnkStruct_0203668c {
    char pad_00[8];
    unsigned char unk_08;
    char pad_09;
    unsigned short unk_0A;
};

struct UnkStruct_02036584 {
    u8 pad_00[0xc];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
};

extern int func_020b65c4(void);
extern int func_020b5e10(void);
extern int func_020b5e84(unsigned char *);
extern int func_02036754(int);
extern void func_020356c4(int a, int b, int c, int d);
extern void func_02035638(unsigned int value);
extern void func_02035624(int);
extern unsigned int data_021c526c;
extern int func_020984e8(void);
extern int func_02099020(int a, int b);
extern int func_0203736c(int a, int b, int c, int d, int e, int f, int g);
extern void func_02035684(int a, int b, int c);

int func_02036714(void)
{
    int r4;
    int r5;
    int r0;

    r4 = func_020b65c4();
    r5 = func_020b5e84((unsigned char *) func_020b5e10());
    r4 = func_02036754(r4);
    r0 = func_02036754(r5);
    if (r4 == r0) {
        if (r4 != 0xffff) {
            return 1;
        }
    }
    return 0;
}

void func_020366e0(struct UnkStruct_020366e0 *param1, int param2)
{
    int ret;
    int c;
    int d;

    ret = func_02036754(param2);
    c = 0x7f;
    d = 0;
    if (ret == 1) {
        c = 0x38;
    }
    if (ret == 0x14 || ret == 0x5c) {
        d = 1;
    }
    func_020356c4(0x11, ret, c, d);
    param1->unk_0A = (unsigned short) ret;
}

void func_020366c0(struct UnkStruct_020366c0 *p)
{
    if (p->unk_0A != 0xffff) {
        func_02035638(p->unk_0A);
        p->unk_0A = 0xffff;
    }
}

void func_0203668c(struct UnkStruct_0203668c *s)
{
    int a;
    int b;

    a = func_020b65c4();
    if (s->unk_08 == a) {
        return;
    }

    b = func_02036754(a);
    if (s->unk_0A != b) {
        func_020366c0((struct UnkStruct_020366c0 *) s);
        func_020366e0((struct UnkStruct_020366e0 *) s, a);
    }

    s->unk_08 = a;
}

void func_0203665c(unsigned char *r0)
{
    unsigned char *r4 = r0;
    if (r4[0xc] != 0) {
        func_02035624(0x10);
        r4[0xc] = 0;
    }
    if (r4[0xd] != 0) {
        func_02035638(0x51);
        r4[0xd] = 0;
    }
    r4[0xe] = 0;
}

int func_02036648(void)
{
    return data_021c526c + 0x24c;
}

void func_02036584(struct UnkStruct_02036584 *self)
{
    int r5, r1, r2;
    unsigned int r0;

    r5 = func_020984e8();
    if (r5 != 0) {
        if (func_02099020(r5, 0x23) != 0 || func_02099020(r5, 1) != 0) {
            r5 = 1;
        } else {
            r5 = 0;
        }
    } else {
        r5 = 0;
    }

    r0 = func_020b65c4();
    r2 = (r0 == 0x1f) ? 1 : 0;
    r1 = 1;
    r0 = (unsigned char) (r0 + 0xe6);
    if (!(r0 <= 4) && (r2 == 0)) {
        r1 = 0;
    }

    if (r5 != 0 || r1 == 0) {
        return;
    }

    r5 = func_02036648();

    if (self->unk_0C == 0) {
        if (func_0203736c(r5, 0x16, 0x31, 0x32, 0x16, 0x32, 0) != 0) {
            func_02035684(0x10, 0xc8, 0);
            self->unk_0C = 1;
        }
    }

    if (self->unk_0D == 0) {
        if (func_0203736c(r5, 0x16, 0x32, 0, 0, 0, 0) != 0 || self->unk_0E != 0) {
            func_020356c4(0xf, 0x51, 0x7f, 0);
            self->unk_0D = 1;
        }
    }
}
