/* clock_setter_hands: 16 functions, module ov134
 * mwccarm 1.2/base -O4,s
 * func_ov134_0229b168 @ 0x0229b168, 0xb8 bytes, Thumb
 * func_ov134_0229b108 @ 0x0229b108, 0x60 bytes, Thumb
 * func_ov134_0229b034 @ 0x0229b034, 0xd4 bytes, Thumb
 * func_ov134_0229b014 @ 0x0229b014, 0x1e bytes, Thumb
 * func_ov134_0229afec @ 0x0229afec, 0x26 bytes, Thumb
 * func_ov134_0229afc0 @ 0x0229afc0, 0x2c bytes, Thumb
 * func_ov134_0229af74 @ 0x0229af74, 0x4c bytes, Thumb
 * func_ov134_0229af60 @ 0x0229af60, 0x14 bytes, Thumb
 * func_ov134_0229af14 @ 0x0229af14, 0x4c bytes, Thumb
 * func_ov134_0229af00 @ 0x0229af00, 0x14 bytes, Thumb
 * func_ov134_0229aed4 @ 0x0229aed4, 0x2c bytes, Thumb
 * func_ov134_0229ae9c @ 0x0229ae9c, 0x38 bytes, Thumb
 * func_ov134_0229ae78 @ 0x0229ae78, 0x24 bytes, Thumb
 * func_ov134_0229accc @ 0x0229accc, 0x1ac bytes, Thumb
 * func_ov134_0229ac84 @ 0x0229ac84, 0x48 bytes, Thumb
 * func_ov134_0229ac38 @ 0x0229ac38, 0x4c bytes, Thumb
 */

#include "types.h"

typedef struct UnkStruct_0229b108 {
    u8 pad_00[0x92];
    u16 unk_92;
    u16 unk_94;
    u16 unk_96;
    u8 pad_98[0x9e - 0x96 - 2];
    u8 unk_9E;
} UnkStruct_0229b108;

typedef struct {
    unsigned char pad_00[0x84];
    int unk_84;
    int unk_88;
} UnkStruct_0229b034;

struct UnkStruct_0229afec {
    unsigned char pad_00[0x92];
    unsigned short unk_92;
};

struct UnkStruct_0229afc0 {
    char pad_00[0x94];
    unsigned short unk_94;
};

typedef struct {
    char pad_00[0xb9];
    unsigned char b9;
    unsigned char ba;
} UnkStruct_0229af60;

typedef struct UnkStruct_0229af14 {
    unsigned char pad_00[0x84];
    int unk_84;
    unsigned char pad_88[0x92 - 0x84 - 4];
    unsigned short unk_92;
    unsigned short unk_94;
} UnkStruct_0229af14;

extern void func_ov134_0229a868(void *self, int value);
extern void MI_CpuCopy8(void *dst, const void *src, int size);
extern void func_ov134_022995a0(void *self, int value);
extern void func_0200467c(int a);
extern void func_ov134_0229a8e8(void *);
extern int func_ov134_022995c0(void *, int);
extern unsigned char func_ov134_0229b884(void *, int);
extern void func_02004658(int);
extern int _s32_div_f(int, int);
extern int func_020e8ed8(int, int);
extern void func_ov134_0229a96c(char *self, int idx, int val);
extern void func_ov134_0229b890(char *self, int idx);
extern void func_ov134_0229b908(char *self);
extern void func_ov134_022995b0(char *self, int val);
extern void func_0209e234(char *dst, int amt);
extern void func_0209e0c0(char *dst, int amt);
extern int func_0209e3ac(char *a, char *b, int len);
extern int func_0209e350(char *a, char *b);
extern void func_0209e100(char *p, int len);
extern void func_0209e268(char *p, int len);
extern void func_02004644(int a, int b);

void func_ov134_0229afec(struct UnkStruct_0229afec *self, int a, int b);
void func_ov134_0229afc0(struct UnkStruct_0229afc0 *self, int p1, int p2);
void func_ov134_0229af60(UnkStruct_0229af60 *self);
int func_ov134_0229af00(int unused, int b, int c);
int func_ov134_0229aed4(int r0, int r1, int r2, int r3);
int func_ov134_0229ae9c(int unused, int a, int b);
int func_ov134_0229ae78(int unused, int x, int y, int r);
void func_ov134_0229accc(char *self, int amt);
int func_ov134_0229ac38(void *obj);

int func_ov134_0229b168(void *self, int a2, int a3)
{
    int flag;
    int v;
    int v1;
    int v2;

    if (func_ov134_0229ae78((int) self, a2, a3, 0x28) == 0) {
        return 0;
    }

    v = func_ov134_0229af00((int) self, a2, a3);
    v1 = func_ov134_0229ae9c((int) self, v, (u16) (*(u16 *) ((char *) self + 0x92)));

    flag = 0;
    if (v1 >= -0x800 && v1 < 0x800) {
        *((u8 *) self + 0x9e) = 0;
        flag = 1;
        *(u16 *) ((char *) self + 0x96) = *(u16 *) ((char *) self + 0x92);
    } else {
        v2 = func_ov134_0229ae9c((int) self, v, (u16) (*(u16 *) ((char *) self + 0x94)));
        if (v2 >= -0x800 && v2 < 0x800) {
            flag = 1;
            *((u8 *) self + 0x9e) = 1;
            *(u16 *) ((char *) self + 0x96) = *(u16 *) ((char *) self + 0x94);
        }
    }

    if (flag) {
        func_ov134_0229a868(self, 6);
        MI_CpuCopy8((char *) self + 0xb8, (char *) self + 0xc0, 8);
        func_ov134_022995a0(self, 0x30);
        return 1;
    }
    return 0;
}

void func_ov134_0229b108(UnkStruct_0229b108 *self, int a, int b)
{
    u16 v;
    int d;

    switch (self->unk_9E) {
        case 0:
            func_ov134_0229afec((struct UnkStruct_0229afec *) self, a, b);
            v = self->unk_92;
            break;
        case 1:
            func_ov134_0229afc0((struct UnkStruct_0229afc0 *) self, a, b);
            v = self->unk_94;
            break;
        default:
            return;
    }

    d = func_ov134_0229ae9c((int) self, (u16) self->unk_96, (u16) v);
    if (d < -1000 || d > 1000) {
        func_0200467c(0x1a);
        self->unk_96 = v;
    }
}

int func_ov134_0229b034(void *p)
{
    UnkStruct_0229b034 *sp;
    int a;

    func_ov134_0229a8e8(p);
    if (func_ov134_022995c0(p, 0x40) != 0 && func_ov134_022995c0(p, 0x10) != 0) {
        sp = (UnkStruct_0229b034 *) p;
        a = func_ov134_0229b884(p, 4);
        a += 0x3c * func_ov134_0229b884(p, 3);
        sp->unk_88 = a;
        while (sp->unk_88 > sp->unk_84) {
            sp->unk_88 -= 0x2d0;
        }
        func_02004658(0x54);
        return 1;
    }
    if (func_ov134_022995c0(p, 0x80) != 0 && func_ov134_022995c0(p, 0x20) != 0) {
        sp = (UnkStruct_0229b034 *) p;
        a = func_ov134_0229b884(p, 4);
        a += 0x3c * func_ov134_0229b884(p, 3);
        sp->unk_88 = a;
        while (sp->unk_88 < sp->unk_84) {
            sp->unk_88 += 0x2d0;
        }
        func_02004658(0x54);
        return 1;
    }
    return 0;
}

int func_ov134_0229b014(int param)
{
    int result;
    if (func_ov134_0229ac38((void *) param) != 0) {
        func_ov134_0229af60((UnkStruct_0229af60 *) param);
        result = 1;
    } else {
        result = 0;
    }
    return result;
}

void func_ov134_0229afec(struct UnkStruct_0229afec *self, int a, int b)
{
    int result = func_ov134_0229aed4((int) self, a, b, (unsigned short) self->unk_92);
    if (result != 0) {
        func_ov134_0229accc((char *) self, (result * 60) >> 16);
    }
}

void func_ov134_0229afc0(struct UnkStruct_0229afc0 *self, int p1, int p2)
{
    int ret;

    ret = func_ov134_0229aed4((int) self, p1, p2, self->unk_94);
    if (ret != 0) {
        func_ov134_0229accc((char *) self, (ret * 0x2d0) >> 16);
    }
}

void func_ov134_0229af74(void *self, unsigned int a, int b)
{
    *(int *) ((char *) self + 0x84) = b + 0x3c * a;
    if (a >= 12) {
        a = (unsigned char) (a - 12);
    }
    *(unsigned short *) ((char *) self + 0x94) = (unsigned short) _s32_div_f((b + 0x3c * a) << 16, 0x2d0);
    *(unsigned short *) ((char *) self + 0x92) = (unsigned short) (b * 0x444);
}

void func_ov134_0229af60(UnkStruct_0229af60 *self)
{
    func_ov134_0229af74(self, (unsigned char) self->ba, (unsigned char) self->b9);
}

void func_ov134_0229af14(UnkStruct_0229af14 *param)
{
    int r4 = param->unk_84;
    while (r4 < 0) {
        r4 += 720;
    }
    while (r4 >= 720) {
        r4 -= 720;
    }
    param->unk_94 = (unsigned short) ((r4 << 16) / 720);
    param->unk_92 = (unsigned short) (0x444 * (r4 % 60));
}

int func_ov134_0229af00(int unused, int b, int c)
{
    return func_020e8ed8((b - 0x38) << 12, (-(c - 0x34)) << 12);
}

int func_ov134_0229aed4(int r0, int r1, int r2, int r3)
{
    int r5 = r0;
    int r4 = r3;
    int result;

    if (r1 == 0x38 && r2 == 0x34) {
        result = 0;
    } else {
        result = func_ov134_0229ae9c(r5, func_ov134_0229af00(r5, r1, r2), r4);
    }

    return result;
}

int func_ov134_0229ae9c(int unused, int a, int b)
{
    int diff1;
    int diff2;

    diff1 = a - b;
    diff2 = b - a;
    while (diff1 < 0) {
        diff1 += 0x10000;
    }
    while (diff1 >= 0x10000) {
        diff1 -= 0x10000;
    }
    while (diff2 < 0) {
        diff2 += 0x10000;
    }
    while (diff2 >= 0x10000) {
        diff2 -= 0x10000;
    }
    if (diff1 > diff2) {
        diff1 = -diff2;
    }
    return diff1;
}

int func_ov134_0229ae78(int unused, int x, int y, int r)
{
    if ((x - 0x38) * (x - 0x38) + (y - 0x34) * (y - 0x34) >= r * r) {
        return 0;
    } else {
        return 1;
    }
}

void func_ov134_0229accc(char *self, int amt)
{
    unsigned char arr[6];
    int i;
    int len;
    int flag;
    char *p;

    if (amt == 0) {
        return;
    }

    i = 0;
    do {
        arr[i] = func_ov134_0229b884((void *) self, i);
        i++;
    } while (i <= 4);

    arr[5] = 0;

    if (amt > 0) {
        func_0209e234(self + 0xc0, amt);
    } else {
        func_0209e0c0(self + 0xc0, -amt);
    }

    flag = 1;

    if (func_ov134_022995c0((void *) self, 0x40) != 0) {
        if (func_0209e3ac(self + 0xd0, self + 0xc0, 0x3f) == -1) {
            len = func_0209e350(self + 0xd0, self + 0xc0);
            flag = 0;
            MI_CpuCopy8((void *) (self + 0xd0), (const void *) (self + 0xb8), 8);
            func_ov134_022995b0(self, 0x10);
            p = self + 0xc0;
            while (len >= 0x2d0) {
                func_0209e100(p, 0xc);
                len -= 0x2d0;
            }
        } else {
            func_ov134_022995a0((void *) self, 0x10);
        }
    }

    if (func_ov134_022995c0((void *) self, 0x80) != 0) {
        if (func_0209e3ac(self + 0xc8, self + 0xc0, 0x3f) == 1) {
            len = func_0209e350(self + 0xc0, self + 0xc8);
            flag = 0;
            MI_CpuCopy8((void *) (self + 0xc8), (const void *) (self + 0xb8), 8);
            func_ov134_022995b0(self, 0x20);
            p = self + 0xc0;
            while (len >= 0x2d0) {
                func_0209e268(p, 0xc);
                len -= 0x2d0;
            }
        } else {
            func_ov134_022995a0((void *) self, 0x20);
        }
    }

    if (flag) {
        MI_CpuCopy8((void *) (self + 0xc0), (const void *) (self + 0xb8), 8);
        func_ov134_0229af60((UnkStruct_0229af60 *) self);
    } else {
        func_ov134_0229af74((void *) self, (unsigned char) self[0xc2], (unsigned char) self[0xc1]);
    }

    i = 0;
    do {
        if (func_ov134_0229b884((void *) self, i) != arr[i]) {
            (self + i)[0x98] = 0x0a;
            func_ov134_0229a96c(self, i, 5);
            func_ov134_0229b890(self, i);
            if (i >= 0 && i <= 2) {
                arr[5] = 1;
            }
        }
        i++;
    } while (i <= 4);

    if (arr[5] != 0) {
        self[0x9d] = 0x0a;
        func_ov134_0229a96c(self, 5, 5);
        func_ov134_0229b908(self);
    }
}

int func_ov134_0229ac84(int unused, int *cur, int target, int max_step, int min_step)
{
    int diff;
    int step;
    int value;

    value = *cur;
    diff = value > target ? value - target : target - value;
    if (diff < min_step) {
        *cur = target;
        return 1;
    }
    step = diff >> 1;
    if (step > max_step) {
        step = max_step;
    } else if (step < min_step) {
        step = min_step;
    }
    if (value > target) {
        *cur -= step;
    } else {
        *cur += step;
    }
    return 0;
}

int func_ov134_0229ac38(void *obj)
{
    int a, b, ret;
    a = *(int *) ((char *) obj + 0x88);
    b = *(int *) ((char *) obj + 0x84);
    if (b == a) {
        ret = 1;
    } else {
        ret = func_ov134_0229ac84((int) obj, (int *) ((char *) obj + 0x84), a, 0x30, 3);
        func_ov134_0229af14((UnkStruct_0229af14 *) obj);
    }
    if (ret == 1) {
        func_02004644(0x54, 1);
        func_0200467c(0x2e);
    }
    return ret;
}
