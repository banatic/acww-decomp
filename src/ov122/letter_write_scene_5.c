/* letter_write_scene_5: 14 functions, module ov122
 * mwccarm 1.2/base -O4,s
 * func_ov122_0229f958 @ 0x0229f958, 0x28 bytes, Thumb
 * func_ov122_0229f940 @ 0x0229f940, 0x18 bytes, Thumb
 * func_ov122_0229f89c @ 0x0229f89c, 0xa2 bytes, Thumb
 * func_ov122_0229f684 @ 0x0229f684, 0x218 bytes, Thumb
 * func_ov122_0229f634 @ 0x0229f634, 0x4e bytes, Thumb
 * func_ov122_0229f5f8 @ 0x0229f5f8, 0x3c bytes, Thumb
 * func_ov122_0229f5c8 @ 0x0229f5c8, 0x2e bytes, Thumb
 * func_ov122_0229f5a0 @ 0x0229f5a0, 0x26 bytes, Thumb
 * func_ov122_0229f590 @ 0x0229f590, 0xe bytes, Thumb
 * func_ov122_0229f540 @ 0x0229f540, 0x50 bytes, Thumb
 * func_ov122_0229f4e0 @ 0x0229f4e0, 0x60 bytes, Thumb
 * func_ov122_0229f488 @ 0x0229f488, 0x58 bytes, Thumb
 * func_ov122_0229f468 @ 0x0229f468, 0x20 bytes, Thumb
 * func_ov122_0229f454 @ 0x0229f454, 0x14 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_0229f940 {
    char pad_00[0xad];
    unsigned char unk_AD;
    unsigned char unk_AE;
};

struct UnkStruct_0229f89c {
    u8 pad_00[0xaa];
    u8 mode;
    u8 pad_AB[2];
    u8 unk_AD;
    u8 unk_AE;
    u8 pad_AF[13];
    u8 *ptr;
    u8 unk_C0;
};

typedef struct {
    char pad_00[0x44];
    char unk_44;
    char pad1[0x58 - 0x45];
    char unk_58;
    char pad2[0xd8 - 0x59];
    char unk_D8;
    char pad3[0xf8 - 0xd9];
    unsigned char unk_F8;
} UnkStruct_0229f684;

typedef struct {
    char pad_00[0x9c];
    int unk_9C;
    int unk_A0;
    char pad1[0xaa - 0xa4];
    unsigned char unk_AA;
    char pad2[1];
    unsigned char unk_AC;
    char pad3[0xbc - 0xad];
    UnkStruct_0229f684 *unk_BC;
    char pad_C0[0x3ce8 - 0xc0];
    char unk_3CE8;
} UnkStruct_0229f684_2;

struct UnkStruct_0229f634 {
    char pad_00[0xf8];
    unsigned char unk_F8;
};

struct UnkStruct_0229f634_2 {
    char pad_00[0xaa];
    unsigned char kind;
    char pad_AB[0xbc - 0xab];
    struct UnkStruct_0229f634 *sub;
};

extern int func_ov122_0229efe8(void *p, int n);
extern void func_ov122_0229efc8(void *, int);
extern int func_ov095_0229bbc0(void *dst, int a, int b, int c, int d);
extern int func_0206de70(void *);
extern int func_ov002_022088bc(void *);
extern int func_ov002_022088cc(void *);
extern int func_ov002_022088ac(void *);
extern int func_ov002_0220889c(void *);
extern unsigned char func_ov122_0229fe28(UnkStruct_0229f684_2 *, int, void *);
extern unsigned char func_ov122_0229fc9c(UnkStruct_0229f684_2 *, void *);
extern unsigned char func_ov122_0229fd34(UnkStruct_0229f684_2 *, int, void *);
extern int func_02051c8c_unk(void *, int);
extern void func_ov122_0229efd8(UnkStruct_0229f684_2 *, int);
extern int func_ov002_0220a58c(void *p, unsigned char a, unsigned char b);
extern unsigned char data_021f6c54;
extern unsigned char data_021f6c58;
extern void func_ov002_0220a4c8(void *receiver);
extern unsigned short data_021fbe40;

int func_ov122_0229f5f8(unsigned char *self);
int func_ov122_0229f5c8(void *param);
void func_ov122_0229f590(void *arg0, unsigned char arg1);
void func_ov122_0229f468(int p0, int p1);

int func_ov122_0229f958(unsigned char *p)
{
    if ((func_ov122_0229efe8(p, 8) == 0) || (p[0xad] == p[0xae])) {
        return 0;
    }
    return 1;
}

void func_ov122_0229f940(struct UnkStruct_0229f940 *self)
{
    self->unk_AD = 0;
    self->unk_AE = 0;
    func_ov122_0229efc8(self, 8);
}

void func_ov122_0229f89c(struct UnkStruct_0229f89c *self)
{
    unsigned int a, b, hi, lo;
    int c, d;
    u8 r;

    b = self->unk_AE;
    a = self->unk_AD;
    if (a > b) {
        lo = b;
        hi = a;
    } else {
        lo = a;
        hi = b;
    }

    c = func_ov122_0229f5f8((unsigned char *) self);
    d = func_ov122_0229f5c8(self);

    switch (self->mode) {
        case 0: {
            u8 *p = self->ptr;
            p[0xf8] = p[0xf8] - (hi - lo);
            break;
        }
        case 1: {
            u8 *p = self->ptr;
            u8 v = p[0xf8];
            lo += v;
            hi += v;
            break;
        }
        default:
            break;
    }

    r = (u8) func_ov095_0229bbc0(&self->unk_C0, c, lo, hi, d);

    if (self->mode == 1) {
        r = (u8) (r - self->ptr[0xf8]);
    }

    func_ov122_0229f590(self, r);
    func_ov122_0229f940((struct UnkStruct_0229f940 *) self);
}

int func_ov122_0229f684(UnkStruct_0229f684_2 *self, void *pad, int force)
{
    unsigned char mode;
    int val;
    int n;
    int start;
    int limit;
    int max;
    unsigned char cur;

    if (pad == 0) {
        return 0;
    }

    mode = self->unk_AA;
    cur = self->unk_AC;
    limit = func_0206de70(&self->unk_3CE8);

    switch (mode) {
        case 0:
        case 1:
            n = -1;
            start = n;
            if (func_ov002_022088bc(pad)) {
                n = 0;
            }
            break;
        case 2:
            n = (self->unk_A0 - 0x40) >> 4;
            start = n;
            if (func_ov002_022088cc(pad)) {
                n--;
            } else if (func_ov002_022088bc(pad)) {
                n++;
                if (n > limit) {
                    n = 4;
                }
            }
            break;
        case 3:
            n = 4;
            start = n;
            if (func_ov002_022088cc(pad)) {
                n--;
            }
            break;
        default:
            n = 0;
            start = n;
            break;
    }

    val = self->unk_9C;
    if (func_ov122_0229efe8((void *) self, 0x10) && n == -1) {
        n = 0;
    }

    if (n != start) {
        if (n == -1) {
            cur = func_ov122_0229fe28(self, val, &mode);
        } else if (n >= 4) {
            mode = 3;
            cur = func_ov122_0229fc9c(self, &val);
        } else {
            mode = 2;
            cur = func_ov122_0229fd34(self, n, &val);
        }
    }

    if (func_ov002_022088ac(pad)) {
        if (cur != 0) {
            cur = cur - 1;
        } else if (mode == 1) {
            cur = self->unk_BC->unk_F8;
            mode = 0;
        }
    } else if (func_ov002_0220889c(pad)) {
        switch (mode) {
            case 0:
                max = self->unk_BC->unk_F8;
                break;
            case 1:
                max = func_02051c8c_unk(&self->unk_BC->unk_44, 0xa) - self->unk_BC->unk_F8;
                break;
            case 2:
                max = func_02051c8c_unk(&self->unk_BC->unk_58, 0x40);
                break;
            case 3:
                max = func_02051c8c_unk(&self->unk_BC->unk_D8, 0x10);
                break;
        }
        if (cur + 1 <= max) {
            cur = cur + 1;
        } else if (mode == 0) {
            cur = 0;
            mode = 1;
        }
    }

    if (mode != self->unk_AA && force == 0) {
        return 0;
    }
    if (mode == self->unk_AA && cur == self->unk_AC) {
        return 0;
    }

    self->unk_AA = mode;
    func_ov122_0229efd8(self, 0x1000);
    func_ov122_0229f590((void *) self, cur);
    return 1;
}

void *func_ov122_0229f634(struct UnkStruct_0229f634_2 *obj)
{
    switch (obj->kind) {
        case 0:
            return (char *) obj->sub + 0x44;
        case 1:
            return (char *) obj->sub + 0x44 + 2 * obj->sub->unk_F8;
        case 2:
            return (char *) obj->sub + 0x58;
        case 3:
            return (char *) obj->sub + 0xd8;
        default:
            return 0;
    }
}

int func_ov122_0229f5f8(unsigned char *self)
{
    switch (self[0xAA]) {
        case 0:
        case 1:
            return *(int *) (self + 0xBC) + 0x44;
        case 2:
            return *(int *) (self + 0xBC) + 0x58;
        case 3:
            return *(int *) (self + 0xBC) + 0xD8;
        default:
            return 0;
    }
}

int func_ov122_0229f5c8(void *param)
{
    unsigned char v = *(unsigned char *) ((char *) param + 0xaa);
    switch (v) {
        case 0:
        case 1:
            return 10;
        case 2:
            return 0x40;
        case 3:
            return 0x10;
    }
    return 0;
}

unsigned char func_ov122_0229f5a0(unsigned char *self)
{
    if (self[0xAA] == 1) {
        return (unsigned char) (self[0xAC] + (*(unsigned char **) (self + 0xBC))[0xF8]);
    }
    return self[0xAC];
}

void func_ov122_0229f590(void *arg0, unsigned char arg1)
{
    unsigned char *p1;
    unsigned char *p2;

    p1 = (unsigned char *) arg0 + 0xac;
    *p1 = arg1;
    p2 = (unsigned char *) arg0 + 0xab;
    *p2 = 0x10;
}

int func_ov122_0229f540(char *self)
{
    if (func_ov002_0220a58c(self + 0x4010, data_021f6c58, data_021f6c54)) {
        *(unsigned char *) (self + 0xb0) = data_021f6c54;
        *(unsigned char *) (self + 0xb1) = *(unsigned char *) (self + 0xb2);
        *(unsigned char *) (self + 0xaf) = *(unsigned char *) (self + 0xb2);
        return 1;
    }
    return 0;
}

void func_ov122_0229f4e0(char *p)
{
    int v0, v1, diff, r5;

    v0 = *(unsigned char *) (p + 0xb1);
    v1 = (data_021f6c54 - *(unsigned char *) (p + 0xb0)) >> 1;
    r5 = v0 + (v1 << 2);
    if (r5 < 0) {
        r5 = 0;
    }
    if (r5 > 0x58) {
        r5 = 0x58;
    }
    func_ov122_0229f468((int) p, r5);
    diff = *(unsigned char *) (p + 0xaf) - r5;
    if (diff >= 4 || diff <= -4) {
        func_ov002_0220a4c8(p + 0x4010);
        *(unsigned char *) (p + 0xaf) = r5;
    }
}

void func_ov122_0229f488(unsigned char *self)
{
    int value;
    unsigned char *p = self;
    unsigned char b = p[0xb2];

    value = b;
    if (data_021fbe40 & 0x40) {
        value = b - 4;
    } else if (data_021fbe40 & 0x80) {
        value = b + 4;
    }
    if (value < 0) {
        value = 0;
    }
    if (value > 0x58) {
        value = 0x58;
    }
    if (value != b) {
        func_ov002_0220a4c8((void *) (p + 0x4010));
    }
    func_ov122_0229f468((int) p, value);
}

void func_ov122_0229f468(int p0, int p1)
{
    *(unsigned char *) ((char *) (((int) (p0) + (178))) + (0)) = p1;
    *(unsigned char *) ((char *) (((int) (p0) + (179))) + (0)) = *(unsigned char *) ((char *) (((int) (p0) + (178))) + (0));
    func_ov122_0229efd8((UnkStruct_0229f684_2 *) p0, 2048);
}

void func_ov122_0229f454(void *param, unsigned char value)
{
    ((unsigned char *) param)[0xB3] = value;
    func_ov122_0229efd8((UnkStruct_0229f684_2 *) param, 0x800);
}
