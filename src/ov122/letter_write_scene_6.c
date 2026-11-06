/* letter_write_scene_6: 30 functions, module ov122
 * mwccarm 1.2/base -O4,s
 * func_ov122_022a02a0 @ 0x022a02a0, 0x28 bytes, Thumb
 * func_ov122_022a024c @ 0x022a024c, 0x54 bytes, Thumb
 * func_ov122_022a0204 @ 0x022a0204, 0x48 bytes, Thumb
 * func_ov122_022a0168 @ 0x022a0168, 0x9c bytes, Thumb
 * func_ov122_022a00fc @ 0x022a00fc, 0x6c bytes, Thumb
 * func_ov122_022a0098 @ 0x022a0098, 0x64 bytes, Thumb
 * func_ov122_022a006c @ 0x022a006c, 0x2c bytes, Thumb
 * func_ov122_022a0054 @ 0x022a0054, 0x16 bytes, Thumb
 * func_ov122_022a0038 @ 0x022a0038, 0x1c bytes, Thumb
 * func_ov122_022a0018 @ 0x022a0018, 0x20 bytes, Thumb
 * func_ov122_022a0000 @ 0x022a0000, 0x16 bytes, Thumb
 * func_ov122_0229ffac @ 0x0229ffac, 0x54 bytes, Thumb
 * func_ov122_0229ff94 @ 0x0229ff94, 0x16 bytes, Thumb
 * func_ov122_0229ff2c @ 0x0229ff2c, 0x68 bytes, Thumb
 * func_ov122_0229fedc @ 0x0229fedc, 0x50 bytes, Thumb
 * func_ov122_0229fea4 @ 0x0229fea4, 0x38 bytes, Thumb
 * func_ov122_0229fe28 @ 0x0229fe28, 0x7c bytes, Thumb
 * func_ov122_0229fd88 @ 0x0229fd88, 0xa0 bytes, Thumb
 * func_ov122_0229fd34 @ 0x0229fd34, 0x54 bytes, Thumb
 * func_ov122_0229fcfc @ 0x0229fcfc, 0x38 bytes, Thumb
 * func_ov122_0229fc9c @ 0x0229fc9c, 0x60 bytes, Thumb
 * func_ov122_0229fc30 @ 0x0229fc30, 0x6c bytes, Thumb
 * func_ov122_0229fc2c @ 0x0229fc2c, 0x2 bytes, Thumb
 * func_ov122_0229fb54 @ 0x0229fb54, 0xd8 bytes, Thumb
 * func_ov122_0229fae8 @ 0x0229fae8, 0x6a bytes, Thumb
 * func_ov122_0229fa90 @ 0x0229fa90, 0x58 bytes, Thumb
 * func_ov122_0229fa34 @ 0x0229fa34, 0x5c bytes, Thumb
 * func_ov122_0229f9e8 @ 0x0229f9e8, 0x4c bytes, Thumb
 * func_ov122_0229f9a8 @ 0x0229f9a8, 0x40 bytes, Thumb
 * func_ov122_0229f980 @ 0x0229f980, 0x26 bytes, Thumb
 */

#include "types.h"

typedef struct {
    unsigned char pad_00[0x8d];
    unsigned char byte_b0;
    unsigned char pad_8E[0x26];
    unsigned char unk_B4;
} UnkStruct_022a0204;

struct SomeUnk;

struct GlobalInfo {
    unsigned char pad_00[2];
    unsigned short flags;
};

typedef struct {
    char pad_00[0x9c];
    int unk_9C;
    char pad_A0[10];
    char unk_AA;
} UnkStruct_0229fea4;

typedef struct {
    char pad_00[0xa0];
    int unk_A0;
    char pad_A4[0xaa - 0xa4];
    unsigned char unk_AA;
    char pad_AB[0xb2 - 0xab];
    unsigned char unk_B2;
    char pad_B3[0x3ce8 - 0xb3];
    char unk_3CE8;
} UnkStruct_0229fd88;

typedef struct {
    char pad_00[0x9C];
    int unk_9C;
    int unk_A0;
    char pad_A4[6];
    char unk_AA;
} UnkStruct_0229fcfc;

struct UnkStruct_0229fb54 {
    unsigned char pad_00[0x9c];
    int unk_9C;
    int unk_A0;
    unsigned char pad_A4[6];
    unsigned char unk_AA;
    unsigned char pad_AB[1];
    unsigned char unk_AC;
    unsigned char pad_AD[1];
    unsigned char unk_AE;
    unsigned char pad_AF[4];
    unsigned char unk_B3;
    unsigned char pad_B4[8];
    unsigned char *unk_BC;
};

struct UnkStruct_0229fae8 {
    char pad_00[0x9c];
    int unk_9C;
    int unk_A0;
};

typedef struct {
    u8 pad_00[0x9c];
    u32 unk_9C;                   // 0x9c
    u32 unk_A0;                   // 0xa0
    u8 pad_A4[0xaa - 0xa4];       // 0xa4 .. 0xa9
    u8 unk_AA;                    // 0xaa
    u8 pad_AB[1];                 // 0xab
    u8 unk_AC;                    // 0xac
    u8 pad_AD[0xbc - 0xad];       // 0xad .. 0xbb
    u8 *unk_BC;                   // 0xbc
    u8 pad_C0[0x3ce8 - 0xc0];     // up to 0x3ce7
    char unk_3CE8;                // 0x3ce8
    u8 pad_3CE9[0x41e0 - 0x3ce9]; // up to 0x41df
    char unk_41E0;                // 0x41e0
} UnkStruct_0229fa90;

typedef struct {
    char pad_00[0x9c];
    int unk_9C;
    int unk_A0;
    char pad_A4[0x8];
    unsigned char unk_AC;
    char pad_AD[0xf];
    void *unk_BC;
} UnkStruct_0229f9e8;

struct UnkStruct_0229f9a8 {
    char pad_00[0xAA];
    unsigned char unk_AA;
};

struct UnkStruct_0229f980;

struct UnkStruct_0229f980 {
    char pad_00[0xac];
    unsigned char unk_AC;
};

extern int func_ov095_0229bf48(void *);
extern int func_ov002_0220b8ac(void *, int);
extern unsigned short data_021fbe40[];
extern int func_ov095_02299a00(void *arg);
extern int func_ov095_0229c448(void *arg, int val, int mode);
extern void func_ov095_0229c8e4(void *arg, int val);
extern void func_ov122_0229f194(void *arg);
extern int func_ov122_022a0be4(void *self, int mode);
extern void func_ov095_0229bf3c(void *ptr);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
int func_ov122_0229efe8(struct SomeUnk *, int);
void func_ov122_0229efc8(struct SomeUnk *, int);
void func_ov122_0229f394(struct SomeUnk *);
int func_ov095_0229cda4(void *, int);
void func_ov002_0220a2b4(void *);
void func_ov002_0220a314(void *);
void func_ov122_0229f250(struct SomeUnk *);
extern int func_ov095_0229cf64(void *ptr, int val);
extern void func_ov122_0229f1b4(void *ptr);
extern void func_ov122_0229f2d0(int);
extern void func_ov122_022a0df8(int);
extern int func_0206fe60(void);
extern void func_ov002_02207fc0(char *p);
extern void func_ov122_0229f2f4(char *p);
extern int func_ov002_0220a768(char *p, int n);
extern int func_ov002_0220a72c(char *p, int n);
extern void func_ov002_0220a0b4(char *p, int a, int b);
extern int func_ov002_02208ad4(char *);
extern int func_ov002_02208ae4(char *);
extern int func_ov002_02208ad8(char *, unsigned char);
extern void func_ov002_0220a374(char *, int);
extern void func_ov122_0229efd8(void *p, int n);
extern void func_ov122_0229f590(void *p, int n);
extern void func_ov122_0229f940(void *p);
extern void func_ov122_022a14c0(void *p);
extern void func_ov095_0229cd30(void *p);
extern unsigned char func_ov095_0229bb34(char *a, char *b, int c, int d, u8 e, u8 *f);
extern int func_0206e224(char *a);
extern int func_0206de70(void *);
extern int *func_0206de7c(void *arg);
extern int func_02051d08(void *p, int n);
extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;
extern int func_0206de38(void *ptr, unsigned char b);
extern unsigned short *func_ov122_0229f634(struct UnkStruct_0229f980 *obj);

unsigned char *func_ov122_022a0018(void *p);
u8 func_ov122_0229fe28(int a, int b, u8 *out);
unsigned char func_ov122_0229fd34(void *p, int n, int *v);
void func_ov122_0229fcfc(UnkStruct_0229fcfc *self);
int func_ov122_0229fc9c(char *p, int *out);
void func_ov122_0229fae8(struct UnkStruct_0229fae8 *self, int b, int c, int d);
void func_ov122_0229fa90(UnkStruct_0229fa90 *self);

int func_ov122_022a02a0(void *self)
{
    int result;
    func_ov095_0229bf48((char *) self + 0xC0);
    result = func_ov002_0220b8ac((char *) self + 0x4864, 1);
    if (result) {
        return (int) func_ov122_022a0018(self);
    } else {
        return result;
    }
}

int func_ov122_022a024c(void *p)
{
    if (!(data_021fbe40[1] & 1)) {
        return 0;
    } else {
        int result = func_ov095_02299a00((char *) p + 0xC0);
        if (result == -1) {
            return 0;
        }
        func_ov095_0229c448((char *) p + 0xC0, result, 9);
        func_ov095_0229c8e4((char *) p + 0xC0, result);
        func_ov122_0229f194(p);
        return 1;
    }
}

int func_ov122_022a0204(UnkStruct_022a0204 *self)
{
    if (!((*(unsigned short *) data_021fbe40) & 2)) {
        return 0;
    }
    func_ov122_022a0be4(self, 0x100);
    func_ov095_0229bf3c((char *) self + 0xc0);
    self->unk_B4 = self->byte_b0;
    func_ov002_02208098((void *) (self), 0xb);
    return 1;
}

int func_ov122_022a0168(struct SomeUnk *self)
{
    if (((*(struct {
             unsigned short pad;
             unsigned short flag;
         } *) data_021fbe40)
             .flag &
         0x800) == 0) {
        return 0;
    }

    if (func_ov122_0229efe8(self, 0x100) != 0) {
        func_ov122_0229efc8(self, 0x100);
    } else {
        func_ov122_0229efd8((void *) self, 0x100);
        func_ov122_0229f394(self);
    }

    if (func_ov095_0229cda4((char *) self + 0xc0, -1) != 0) {
        if (func_ov122_0229efe8(self, 0x100) != 0) {
            func_ov002_0220a2b4((char *) self + 0x4058);
            func_ov002_02208098((void *) (self), 0xc);
        } else {
            func_ov002_0220a314((char *) self + 0x4058);
            func_ov002_02208098((void *) (self), 6);
        }
        func_ov122_0229f250(self);
    } else {
        func_ov122_0229f250(self);
    }
    return 1;
}

int func_ov122_022a00fc(void *self)
{
    if (!((*(struct GlobalInfo *) data_021fbe40).flags & 0x100)) {
        return 0;
    }
    if (func_ov095_0229cf64((char *) self + 0xc0, 12) != 0) {
        return 0;
    }
    func_ov122_022a0be4(self, 281);
    func_ov095_0229c8e4((char *) self + 0xc0, 266);
    func_ov122_0229f1b4(self);
    ((unsigned char *) self)[0xb4] = ((unsigned char *) self)[0x8d];
    func_ov002_02208098((void *) (self), 15);
    return 1;
}

int func_ov122_022a0098(unsigned char *self)
{
    if ((data_021fbe40[1] & 0x200) == 0) {
        return 0;
    }
    if (func_ov095_0229cf64(self + 0xc0, 0xb) != 0) {
        return 0;
    }
    func_ov122_022a0be4(self, 0x118);
    func_ov095_0229c8e4(self + 0xc0, 0x109);
    self[0xb4] = self[0x8d];
    func_ov002_02208098((void *) (self), 0xe);
    return 1;
}

int func_ov122_022a006c(int param)
{
    if ((data_021fbe40[1] & 8) == 0) {
        return 0;
    }
    func_ov122_0229f2d0(param);
    func_ov122_022a0df8(param);
    return 1;
}

unsigned char *func_ov122_022a0054(void *p)
{
    func_ov122_0229f2d0((int) p);
    return func_ov002_02208098((void *) (p), 0);
}

unsigned char *func_ov122_022a0038(void *param)
{
    func_ov002_02207fc0((char *) param);
    func_ov122_0229f2f4((char *) param);
    return func_ov002_02208098((void *) (param), 6);
}

unsigned char *func_ov122_022a0018(void *p)
{
    if (func_0206fe60()) {
        return func_ov122_022a0054(p);
    } else {
        return func_ov122_022a0038(p);
    }
}

void func_ov122_022a0000(int arg)
{
    func_ov122_0229f2d0(arg);
    func_ov002_02208098((void *) (arg), 4);
}

void func_ov122_0229ffac(char *p)
{
    int a, b;
    func_ov002_02207fc0(p);
    func_ov122_0229f2f4(p);
    a = func_ov002_0220a768(p + 0x4698, 4);
    b = func_ov002_0220a72c(p + 0x4698, 4);
    func_ov002_0220a0b4(p + 0x4058, a, b);
    p[0xb6] = 1;
    func_ov002_02208098((void *) (p), 0x13);
}

void func_ov122_0229ff94(int param)
{
    func_ov122_0229f2d0((int) ((void *) param));
    func_ov002_02208098((void *) (param), 5);
}

void func_ov122_0229ff2c(char *self)
{
    int a, b;

    func_ov002_02207fc0(self);
    func_ov122_0229f2f4(self);

    *((unsigned char *) self + 0xb6) = func_ov002_02208ad4(self + 0x42b0) - 1;

    a = func_ov002_02208ae4(self + 0x42b0);
    b = func_ov002_02208ad8(self + 0x42b0, *((unsigned char *) self + 0xb6));

    func_ov002_0220a0b4(self + 0x4058, a, b);
    func_ov002_0220a374(self + 0x4058, 7);
    func_ov002_02208098((void *) (self), 0x14);
}

void func_ov122_0229fedc(void *self)
{
    func_ov122_0229efd8(self, 4);
    *(int *) ((char *) self + 0x9c) = 0x30;
    *(int *) ((char *) self + 0xa0) = 0x40;
    *(unsigned char *) ((char *) self + 0xaa) = 2;
    func_ov122_0229efd8(self, 0x1000);
    func_ov122_0229f590(self, 0);
    func_ov122_0229f940(self);
    func_ov095_0229cd30((char *) self + 0xc0);
    func_ov122_022a14c0(self);
}

void func_ov122_0229fea4(UnkStruct_0229fea4 *self)
{
    int result = (int) func_ov122_0229fe28((int) self, self->unk_9C, (u8 *) (&self->unk_AA));
    func_ov122_0229efd8(self, 0x1000);
    func_ov122_0229f590(self, result);
    func_ov122_0229fa90((UnkStruct_0229fa90 *) self);
}

u8 func_ov122_0229fe28(int a, int b, u8 *out)
{
    u8 arg5;
    u8 *p;
    u8 local;
    u8 bval;
    int v;
    int threshold;

    arg5 = (u8) (b - 0x30);
    p = &local;
    func_ov095_0229bb34((char *) a + 0xc0, (char *) a + 0x41e0, 0x28, 0xa0, arg5, p);

    bval = *(u8 *) (*(char **) ((char *) a + 0xbc) + 0xf8);
    v = func_0206e224((char *) a + 0x3ce8) + bval;
    threshold = (bval + v) >> 1;

    if (local < threshold) {
        *out = 0;
        if ((int) local > (int) bval) {
            local = bval;
        }
    } else {
        *out = 1;
        if (local < v) {
            local = 0;
        } else {
            local = (u8) (local - v);
        }
    }

    return local;
}

void func_ov122_0229fd88(UnkStruct_0229fd88 *self, int flag)
{
    int n, result, ret;

    self->unk_AA = 2;
    func_ov122_0229efd8((void *) self, 0x1000);

    if (self->unk_A0 < 0x40) {
        self->unk_A0 = 0x40;
    }
    if (self->unk_A0 >= 0x80) {
        self->unk_A0 = 0x7f;
    }

    n = (self->unk_A0 - 0x40) >> 4;
    result = func_0206de70((void *) &self->unk_3CE8);

    if (n > result) {
        n = result;
    } else {
        flag = 0;
    }

    self->unk_A0 = (n << 4) + 0x40;

    if (flag != 0) {
        if ((self->unk_A0 - self->unk_B2) < 8) {
            func_ov122_0229fcfc((UnkStruct_0229fcfc *) self);
            return;
        }
    }

    ret = (int) func_ov122_0229fd34((void *) self, n, (int *) ((void *) ((char *) self + 0x9c)));
    func_ov122_0229f590((void *) self, ret);
}

unsigned char func_ov122_0229fd34(void *p, int n, int *v)
{
    int x = func_0206de7c((char *) p + 0x3ce8)[n];
    unsigned char temp;
    int r = (int) func_ov095_0229bb34((char *) ((char *) p + 0xc0),
                                      (char *) ((char *) (*(void **) ((char *) p + 0xbc)) + 0x58 + x * 2), 0x28, 0xa0,
                                      (unsigned char) ((unsigned char) (*v - 0x30)), (u8 *) (&temp));
    *v = r + 0x30;
    return (unsigned char) (temp + x);
}

void func_ov122_0229fcfc(UnkStruct_0229fcfc *self)
{
    int ret;

    self->unk_AA = 3;
    func_ov122_0229efd8((void *) self, 0x1000);
    self->unk_A0 = 0x88;
    ret = func_ov122_0229fc9c((char *) self, &self->unk_9C);
    func_ov122_0229f590((void *) self, ret);
}

int func_ov122_0229fc9c(char *p, int *out)
{
    unsigned char local;
    unsigned char a;
    int b, c;

    a = (unsigned char) (*out - 0x30);
    b = func_02051d08(*(char **) (p + 0xbc) + 0xd8, 0x10);
    c = 0xa0 - b;
    if (c > a) {
        local = 0;
        *out = c + 0x30;
    } else {
        unsigned char d = (unsigned char) (a - c);
        int e = (int) func_ov095_0229bb34((char *) (p + 0xc0), (char *) (*(char **) (p + 0xbc) + 0xd8), 0x10, 0xa0, d,
                                          (u8 *) (&local));
        *out = c + (e + 0x30);
    }
    return local;
}

int func_ov122_0229fc30(void *self)
{
    int a;
    int b;

    a = data_021f6c58;
    b = data_021f6c54;
    if (b < 0) {
        return 0;
    }
    if (b > 0x4f) {
        b = 0x4f;
    }
    b += ((unsigned char *) self)[0xb3];
    if (a < 0x20 || a >= 0xe0) {
        return 0;
    }
    if (a < 0x30) {
        a = 0x30;
    }
    func_ov122_0229fae8((struct UnkStruct_0229fae8 *) self, a, b, 1);
    func_ov122_0229efd8(self, 8);
    ((unsigned char *) self)[0xad] = ((unsigned char *) self)[0xac];
    ((unsigned char *) self)[0xae] = ((unsigned char *) self)[0xac];
    return 1;
}

void func_ov122_0229fc2c(void *receiver) {}

int func_ov122_0229fb54(struct UnkStruct_0229fb54 *p)
{
    int a;
    int b;
    unsigned char old;
    unsigned char mode;

    a = data_021f6c58;
    b = data_021f6c54;
    old = p->unk_AC;
    if (a < 0x30) {
        a = 0x30;
    }
    b += p->unk_B3;
    mode = p->unk_AA;

    switch (mode) {
        case 0:
        case 1:
            p->unk_9C = a;
            func_ov122_0229fea4((UnkStruct_0229fea4 *) p);
            if (p->unk_AA == mode) {
                break;
            }
            p->unk_AA = mode;
            func_ov122_0229efd8((void *) p, 0x1000);
            if (mode == 0) {
                func_ov122_0229f590((void *) p, p->unk_BC[0xf8]);
            } else {
                func_ov122_0229f590((void *) p, 0);
            }
            func_ov122_0229fa90((UnkStruct_0229fa90 *) p);
            break;
        case 2:
            p->unk_9C = a;
            p->unk_A0 = b;
            func_ov122_0229fd88((UnkStruct_0229fd88 *) p, 0);
            break;
        case 3:
            p->unk_9C = a;
            func_ov122_0229fcfc((UnkStruct_0229fcfc *) p);
            break;
    }

    p->unk_AE = p->unk_AC;
    return p->unk_AC != old ? 1 : 0;
}

void func_ov122_0229fae8(struct UnkStruct_0229fae8 *self, int b, int c, int d)
{
    if (!func_ov122_0229efe8((struct SomeUnk *) self, 0x10) && c < 0x3c) {
        self->unk_9C = b;
        func_ov122_0229fea4((UnkStruct_0229fea4 *) self);
    } else if (c < 0x84) {
        if (c < 0x40) {
            c = 0x40;
        } else if (c >= 0x80) {
            c = 0x7f;
        }
        self->unk_9C = b;
        self->unk_A0 = c;
        func_ov122_0229fd88((UnkStruct_0229fd88 *) self, d);
    } else {
        self->unk_9C = b;
        func_ov122_0229fcfc((UnkStruct_0229fcfc *) self);
    }
    func_ov122_0229f394((struct SomeUnk *) self);
}

void func_ov122_0229fa90(UnkStruct_0229fa90 *self)
{
    int a;
    int ret1;
    int ret2;
    u8 b;

    a = self->unk_AC;
    b = self->unk_AA;

    if (b == 1) {
        ret1 = func_0206e224(&self->unk_3CE8);
        a += (self->unk_BC[0xf8] + ret1);
    }

    ret2 = func_02051d08((void *) (&self->unk_41E0), a);
    self->unk_9C = (u8) (ret2 + 0x30);
    self->unk_A0 = 0x28;
}

void func_ov122_0229fa34(char *self)
{
    int idx;
    unsigned char b;
    unsigned int *arr;
    unsigned int val;
    char *base;
    unsigned short *p;
    int diff;
    int res;

    idx = func_0206de38(self + 0x3ce8, *(unsigned char *) (self + 0xac));
    *(unsigned int *) (self + 0xa0) = (idx << 4) + 0x40;
    arr = (unsigned int *) func_0206de7c(self + 0x3ce8);
    val = arr[idx];
    base = *(char **) (self + 0xbc);
    p = (unsigned short *) (base + 0x58 + val * 2);
    b = *(unsigned char *) (self + 0xac);
    diff = (int) (b - val);
    res = func_02051d08((void *) p, diff);
    *(unsigned int *) (self + 0x9c) = (unsigned char) (res + 0x30);
}

int func_ov122_0229f9e8(UnkStruct_0229f9e8 *p)
{
    int ret1;
    int ret2;

    ret1 = func_02051d08((char *) p->unk_BC + 0xd8, p->unk_AC);
    p->unk_9C = (unsigned char) (ret1 + 0x30);
    ret2 = func_02051d08((char *) p->unk_BC + 0xd8, 0x10);
    p->unk_9C = p->unk_9C + (0xA0 - ret2);
    p->unk_A0 = 0x88;
    return 0x88;
}

void func_ov122_0229f9a8(struct UnkStruct_0229f9a8 *self)
{
    switch (self->unk_AA) {
        case 0:
        case 1:
            func_ov122_0229fa90((UnkStruct_0229fa90 *) self);
            break;
        case 2:
            func_ov122_0229fa34((char *) self);
            break;
        case 3:
            func_ov122_0229f9e8((UnkStruct_0229f9e8 *) self);
            break;
    }
    func_ov122_0229f394((struct SomeUnk *) self);
}

unsigned short func_ov122_0229f980(struct UnkStruct_0229f980 *obj)
{
    if (obj->unk_AC == 0) {
        return 0;
    }
    return func_ov122_0229f634(obj)[obj->unk_AC - 1];
}
