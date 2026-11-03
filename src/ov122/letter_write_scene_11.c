/* letter_write_scene_11: 23 functions, module ov122
 * mwccarm 1.2/base -O4,s
 * func_ov122_022a1f10 @ 0x022a1f10, 0x4 bytes, Thumb
 * func_ov122_022a1f0c @ 0x022a1f0c, 0x4 bytes, Thumb
 * func_ov122_022a1ef4 @ 0x022a1ef4, 0x16 bytes, Thumb
 * func_ov122_022a1e90 @ 0x022a1e90, 0x62 bytes, Thumb
 * func_ov122_022a1e40 @ 0x022a1e40, 0x4e bytes, Thumb
 * func_ov122_022a1e00 @ 0x022a1e00, 0x40 bytes, Thumb
 * func_ov122_022a1d60 @ 0x022a1d60, 0x9e bytes, Thumb
 * func_ov122_022a1d04 @ 0x022a1d04, 0x5a bytes, Thumb
 * func_ov122_022a1cc8 @ 0x022a1cc8, 0x3c bytes, Thumb
 * func_ov122_022a1c68 @ 0x022a1c68, 0x60 bytes, Thumb
 * func_ov122_022a1c24 @ 0x022a1c24, 0x44 bytes, Thumb
 * func_ov122_022a1bd4 @ 0x022a1bd4, 0x4e bytes, Thumb
 * func_ov122_022a1ba4 @ 0x022a1ba4, 0x2e bytes, Thumb
 * func_ov122_022a1b60 @ 0x022a1b60, 0x44 bytes, Thumb
 * func_ov122_022a1b50 @ 0x022a1b50, 0x10 bytes, Thumb
 * func_ov122_022a1b24 @ 0x022a1b24, 0x2c bytes, Thumb
 * func_ov122_022a1ac4 @ 0x022a1ac4, 0x60 bytes, Thumb
 * func_ov122_022a1a84 @ 0x022a1a84, 0x3e bytes, Thumb
 * func_ov122_022a1a58 @ 0x022a1a58, 0x2c bytes, Thumb
 * func_ov122_022a1a04 @ 0x022a1a04, 0x52 bytes, Thumb
 * func_ov122_022a1998 @ 0x022a1998, 0x6a bytes, Thumb
 * func_ov122_022a18f8 @ 0x022a18f8, 0xa0 bytes, Thumb
 * func_ov122_022a18c4 @ 0x022a18c4, 0x34 bytes, Thumb
 */

#include "types.h"

typedef struct {
    char pad_00[0x94];
    unsigned int unk_94;
} SelfType;

typedef struct {
    unsigned char pad_00[0x8c];
    unsigned char unk_8C;
    unsigned char pad_8D[7];
    int unk_94;
    unsigned char pad_98[29];
    unsigned char unk_B5;
} Object;

typedef struct {
    char pad_00[0x8c];
    unsigned char unk_8C;
    char pad_8D[11];
    unsigned int unk_98;
} UnkStruct_022a1ba4;

typedef struct {
    unsigned char pad_00[0x98];
    int unk_98;
} UnkStruct_022a1b60;

typedef struct {
    char pad_00[0x8c];
    char unk_8C;
    char pad_8D[11];
    int unk_98;
} S_022a1b24;

struct UnkStruct_022a1998 {
    char pad_00[0x94];
    int unk_94;
    int unk_98;
};

extern void func_ov122_0229f088(int);
extern void func_020ee470(int);
extern void func_0206f58c(void);
extern int func_0206f56c(void);
extern int func_020ee45c(void *a);
extern int func_0206fb9c(void);
extern void func_ov090_022993cc(int a, unsigned char b);
extern void func_0206fba8(int a);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);
extern void func_ov122_0229f454(void *, int);
extern void func_ov122_0229efc8(void *, int);
extern void func_ov122_0229f2d0(void *);
extern void func_ov122_0229effc(void *);
extern void func_ov122_022a1808(void);
extern void func_ov122_022a1770(void *);
extern void func_ov095_0229c420(void *, int);
extern void func_ov095_0229bf7c(void *, int);
extern void func_ov002_02207f20(void *, int, int, int, int);
extern void func_02002708(int);
extern void func_ov002_02207e80(void *, int, int, int);
extern void func_ov122_022a1764(void *);
extern void func_ov122_022a1738(void *);
extern void func_ov122_0229efd8(void *, int);
extern int func_ov002_02207f60(void *);
extern void func_ov002_02208090(void *, int);
extern int func_ov002_02207f48(SelfType *self, int arg);
extern void func_ov122_0229fedc(SelfType *self);
extern unsigned char *func_ov122_022a0018(SelfType *self);
extern void func_ov002_02207f04(void *a, int b, int c, int d, int e);
extern int func_ov002_02207f3c(void *p, int v);
extern void func_0200277c(int v);
extern void func_0200284c(int a, int b, int c);
extern int func_ov122_0229efe8(void *arg0, int arg1);
extern int func_ov122_0229f444(UnkStruct_022a1ba4 *);
extern void func_ov122_022a1718(UnkStruct_022a1ba4 *);
extern int func_0206fe60(void);
extern void func_ov122_022a0000(void *self);
extern void func_ov122_0229ffac(void *self);
extern void func_ov095_0229c208(void *p, unsigned int bank);
extern void func_020029e8(int a, int b);
extern void func_ov002_022097b8(void *);
extern void func_ov122_0229f0dc(void *, int);
extern void func_020027f0(int);
extern void *func_0206fcbc(void);
extern void func_ov095_0229c084(void *p, int v);
extern void func_0206e2ec(void *p, int v);
extern void func_0206e1d8(void *p, void *v);
extern void func_ov122_0229f468(void *self, int);
extern void *func_0208e95c(void *p, int v);
extern void func_ov002_02209984(void *p, int a, int b, int c);
extern void func_ov002_02208e38(void *p);
extern int func_02065f20(void *p);
extern void func_ov095_0229c050(void *p);
extern void func_ov095_0229c05c(void *);
extern void func_0206e2e4(void *);
extern void func_ov002_02209178(void *);
extern void func_ov002_0220af74(void *);

void func_ov122_022a1e00(void *param);

int func_ov122_022a1f10(void)
{
    return 1;
}

int func_ov122_022a1f0c(void)
{
    return 1;
}

int func_ov122_022a1ef4(int arg)
{
    func_ov122_0229f088(arg);
    func_020ee470(arg);
    return 1;
}

int func_ov122_022a1e90(void *param)
{
    func_0206f58c();
    if (func_0206f56c() == 0) {
        goto fail;
    }
    switch (*(unsigned char *) ((char *) param + 0x8d)) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 6:
        case 9:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
        case 16:
        case 17:
        case 18:
        case 19:
            func_ov122_022a1e00(param);
            return 1;
        default:
            goto fail;
    }
fail:
    return 0;
}

int func_ov122_022a1e40(void *self, int mode)
{
    int a, b;

    a = func_020ee45c(self);
    if (mode != -1 && mode != 8) {
        b = func_0206fb9c();
        func_ov090_022993cc(a, (unsigned char) mode);
        func_0206fba8(b);
        *((unsigned char *) self + 0x8c) = 2;
        func_ov002_022080a0((void *) (self), 1);
        return 1;
    } else {
        return 0;
    }
}

void func_ov122_022a1e00(void *param)
{
    func_ov090_022993cc(func_020ee45c(param), 7);
    func_ov122_0229f454(param, 0);
    func_ov122_0229efc8(param, 4);
    *((unsigned char *) param + 0x8c) = 0xd;
    func_ov002_022080a0((void *) (param), 1);
    func_ov122_0229f2d0(param);
    func_ov122_0229effc(param);
}

void func_ov122_022a1d60(void *self)
{
    func_ov122_022a1808();
    func_ov122_022a1770(self);
    func_ov095_0229c420((char *) self + 0xc0, 6);
    func_ov095_0229bf7c((char *) self + 0xc0, 6);
    func_ov002_02207f20(self, 0xb, 0, 0, 0x30);
    func_02002708(6);
    func_02002708(4);
    func_02002708(3);
    func_ov002_02207e80(self, 6, 0, 0);
    func_ov002_02207e80(self, 4, 0, ~0xf);
    func_ov002_02207e80(self, 3, 0, ~0xf);
    func_ov122_022a1764(self);
    func_ov122_022a1738(self);
    func_ov122_0229efd8(self, 1);
    *(int *) ((char *) self + 0x94) = func_ov002_02207f60(self);
    func_ov002_02208090(self, 1);
}

void func_ov122_022a1d04(SelfType *self)
{
    if (func_ov002_02207f48(self, 0)) {
        func_ov002_022080a0((void *) (self), 2);
        func_ov122_0229fedc(self);
        func_ov122_022a0018(self);
    }
    func_ov002_02207e80((void *) self, 6, 0, 0);
    func_ov002_02207e80((void *) self, 4, 0, ~0xf);
    func_ov002_02207e80((void *) self, 3, 0, ~0xf);
    self->unk_94 = func_ov002_02207f60((void *) self);
}

void func_ov122_022a1cc8(void *a)
{
    func_ov002_02207f04(a, 3, 0, 0, 0x30);
    func_ov002_02207e80(a, 4, 0, 0);
    func_ov002_02207e80(a, 3, 0, 0);
    func_ov002_02208090(a, 3);
}

void func_ov122_022a1c68(char *p)
{
    if (func_ov002_02207f3c(p, 0)) {
        func_0200277c(4);
        func_0200277c(3);
        func_0200284c(4, 0, 0);
        func_0200284c(3, 0, 0);
        func_ov002_022080a0((void *) (p), 5);
    } else {
        func_ov002_02207e80(p, 4, 0, 0);
        func_ov002_02207e80(p, 3, 0, 0);
        *(int *) (p + 0x98) = func_ov002_02207f60(p);
    }
}

void func_ov122_022a1c24(void *arg0)
{
    if (func_ov122_0229efe8(arg0, 0x20) == 0) {
        func_ov002_02207f04(arg0, 8, 0, 0, 0x30);
        func_ov002_02207e80(arg0, 6, 0, 0);
        ((unsigned char *) arg0)[0x8c] = 5;
    } else {
        func_ov122_0229f454(arg0, 0);
    }
}

void func_ov122_022a1bd4(Object *p)
{
    if (func_ov002_02207f3c((void *) p, 0) != 0) {
        func_0200277c(6);
        func_0200284c(6, 0, 0);
        func_ov122_0229efc8((void *) p, 1);
        p->unk_8C = p->unk_B5;
    } else {
        func_ov002_02207e80((void *) p, 6, 0, 0);
        p->unk_94 = func_ov002_02207f60((void *) p);
    }
}

void func_ov122_022a1ba4(UnkStruct_022a1ba4 *a)
{
    if (func_ov122_0229f444(a) == 0) {
        func_ov122_022a1718(a);
        func_ov122_0229efd8((void *) a, 2);
        a->unk_98 = 0xc0;
        a->unk_8C = 7;
    }
}

void func_ov122_022a1b60(UnkStruct_022a1b60 *self)
{
    if (self->unk_98 > 0x20) {
        self->unk_98 -= 0x20;
    } else {
        self->unk_98 = 0;
        if (((void) ((int) func_ov002_022080a0((void *) (self), 2)), func_0206fe60()) != 0) {
            func_ov122_022a0000(self);
        } else {
            func_ov122_0229ffac(self);
        }
    }
}

void func_ov122_022a1b50(void *param0)
{
    unsigned char *p0;
    unsigned int *p1;
    unsigned int val0;
    unsigned char val1;

    p0 = (unsigned char *) param0 + 0x8c;
    p1 = (unsigned int *) ((unsigned char *) param0 + 0x98);
    val0 = 0;
    val1 = 9;
    *p1 = val0;
    *p0 = val1;
}

void func_ov122_022a1b24(S_022a1b24 *param)
{
    if (param->unk_98 < 0xA0) {
        param->unk_98 += 0x20;
    } else {
        func_ov122_0229efc8(param, 2);
        param->unk_8C = 0x0A;
    }
}

void func_ov122_022a1ac4(char *p)
{
    func_ov095_0229c208(p + 0xc0, 6);
    func_020029e8(6, 1);
    func_ov002_02207f20(p, 8, 0, 0, 0x30);
    func_02002708(6);
    func_ov002_02207e80(p, 6, 0, 0);
    func_ov122_022a1738(p);
    func_ov122_0229efd8(p, 1);
    *(int *) (p + 0x94) = func_ov002_02207f60(p);
    *(unsigned char *) (p + 0x8c) = 0xb;
}

int func_ov122_022a1a84(void *p)
{
    int result;
    int zero = 0;
    if (func_ov002_02207f48((SelfType *) p, 0) != 0) {
        func_ov122_0229fedc((SelfType *) p);
        func_ov002_022080a0((void *) (p), 2);
        func_ov122_022a0018((SelfType *) p);
    }
    func_ov002_02207e80(p, 6, zero, zero);
    result = func_ov002_02207f60(p);
    *(int *) ((char *) p + 0x94) = result;
    return result;
}

void func_ov122_022a1a58(void *self)
{
    *((unsigned char *) self + 0xb7) = 0;
    func_ov002_022097b8((char *) self + 0x42b0);
    func_ov122_0229f0dc(self, 1);
    func_ov002_022080a0((void *) (self), 2);
}

void func_ov122_022a1a04(void *ptr)
{
    if (func_ov122_0229f444((UnkStruct_022a1ba4 *) ptr) == 0) {
        func_ov002_02207f04(ptr, 11, 0, 0, 0x30);
        func_ov002_02207e80(ptr, 6, 0, 0);
        func_ov002_02207e80(ptr, 4, 0, 0);
        func_ov002_02207e80(ptr, 3, 0, 0);
        func_ov002_02208090(ptr, 14);
    }
}

void func_ov122_022a1998(struct UnkStruct_022a1998 *param)
{
    if (func_ov002_02207f3c(param, 0)) {
        func_020027f0(6);
        func_020027f0(4);
        func_020027f0(3);
        func_ov002_022080a0((void *) (param), 5);
    } else {
        func_ov002_02207e80(param, 6, 0, 0);
        func_ov002_02207e80(param, 4, 0, 0);
        func_ov002_02207e80(param, 3, 0, 0);
        param->unk_94 = func_ov002_02207f60(param);
        param->unk_98 = param->unk_94;
    }
}

void func_ov122_022a18f8(char *self)
{
    *(void **) (self + 0xbc) = func_0206fcbc();
    func_ov095_0229c084(self + 0xc0, 1);
    func_0206e2ec(self + 0x3ce8, 3);
    func_0206e1d8(self + 0x3ce8, *(void **) (self + 0xbc));
    func_ov122_0229f468(self, 0x10);
    func_ov122_0229f454(self, 0x10);
    *(u16 *) (self + 0xa8) = 0;
    func_0208e95c(self + 0x4010, 1);
    func_ov002_02209984(self + 0x42b0, 6, 1, 0);
    func_ov002_02208e38(self + 0x42b0);
    *(u32 *) (self + 0xa4) = 0;
    if (func_02065f20(*(void **) (self + 0xbc)) != 0) {
        func_ov095_0229c050(self + 0xc0);
        func_ov122_0229efd8(self, 0x10);
    }
}

void func_ov122_022a18c4(void *self)
{
    func_ov095_0229c05c((char *) self + 0xc0);
    func_0206e2e4((char *) self + 0x3ce8);
    func_ov002_02209178((char *) self + 0x42b0);
    func_ov002_0220af74((char *) self + 0x4698);
}
