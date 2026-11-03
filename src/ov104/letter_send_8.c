/* letter_send_8: 20 functions, module ov104
 * mwccarm 1.2/base -O4,s
 * func_ov104_0229f03c @ 0x0229f03c, 0x4 bytes, Thumb
 * func_ov104_0229f038 @ 0x0229f038, 0x4 bytes, Thumb
 * func_ov104_0229eef8 @ 0x0229eef8, 0x140 bytes, Thumb
 * func_ov104_0229eee4 @ 0x0229eee4, 0x14 bytes, Thumb
 * func_ov104_0229eec8 @ 0x0229eec8, 0x1c bytes, Thumb
 * func_ov104_0229ee54 @ 0x0229ee54, 0x74 bytes, Thumb
 * func_ov104_0229edf4 @ 0x0229edf4, 0x60 bytes, Thumb
 * func_ov104_0229edcc @ 0x0229edcc, 0x28 bytes, Thumb
 * func_ov104_0229ed6c @ 0x0229ed6c, 0x60 bytes, Thumb
 * func_ov104_0229ed1c @ 0x0229ed1c, 0x50 bytes, Thumb
 * func_ov104_0229ecc0 @ 0x0229ecc0, 0x5c bytes, Thumb
 * func_ov104_0229ec4c @ 0x0229ec4c, 0x74 bytes, Thumb
 * func_ov104_0229ec0c @ 0x0229ec0c, 0x3e bytes, Thumb
 * func_ov104_0229ebe0 @ 0x0229ebe0, 0x2a bytes, Thumb
 * func_ov104_0229eba8 @ 0x0229eba8, 0x36 bytes, Thumb
 * func_ov104_0229eb88 @ 0x0229eb88, 0x20 bytes, Thumb
 * func_ov104_0229eb68 @ 0x0229eb68, 0x20 bytes, Thumb
 * func_ov104_0229eb48 @ 0x0229eb48, 0x20 bytes, Thumb
 * func_ov104_0229eaa8 @ 0x0229eaa8, 0xa0 bytes, Thumb
 * func_ov104_0229ea5c @ 0x0229ea5c, 0x4c bytes, Thumb
 */

#include "types.h"

typedef struct {
    u8 pad_00[0xb0];
    u16 flag;
    u8 pad_B2[0x2d02];
    u8 sub[1];
} UnkStruct_0229eef8;

typedef struct {
    unsigned char pad_00[0xB9];
    unsigned char unk_B9;
    unsigned char pad_BA[0x2A14 - 0xB9 - 1];
    char unk_2A14[1];
    unsigned char pad_2A15[0x2D3C - 0x2A14 - 1];
    char unk_2D3C[1];
} UnkStruct_0229ec4c;

typedef struct {
    unsigned char pad_00[0x9C];
    int value;
} UnkStruct_0229eb48;

extern void func_ov104_0229cb04(UnkStruct_0229eef8 *self);
extern void func_0206fc4c(int a);
extern void func_ov104_0229caa0(UnkStruct_0229eef8 *self, int a);
extern void func_0206f990(int a);
extern int func_0206f8e0(void);
extern int func_0206f860(void);
extern void func_0209aa80(void);
extern void func_0209788c(void);
extern void func_020ee470(UnkStruct_0229eef8 *self);
extern int func_020978bc(void *p, int a);
extern int func_020984e8(void);
extern int func_02099020(int a, int b);
extern int func_ov104_0229c648(UnkStruct_0229eef8 *self, void *p);
extern int func_ov104_0229c944(UnkStruct_0229eef8 *self, void *p);
extern int func_ov104_0229c870(UnkStruct_0229eef8 *self, void *p, int a);
extern int func_ov104_0229c7e8(UnkStruct_0229eef8 *self, void *p);
extern int func_ov104_0229c6a0(UnkStruct_0229eef8 *self, void *p);
extern int func_02097b24(void);
extern void func_ov104_0229c3dc(int);
extern int func_ov002_022080a8(int);
extern void func_ov104_0229e98c(void);
extern void func_ov104_0229e978(void *p);
extern void func_ov002_02208090(void *p, int n);
extern void func_ov104_0229e8f8(void *);
extern void func_02002708(int);
extern void func_ov104_0229d830(void *);
extern void func_ov104_0229c354(void *, int);
extern void func_ov094_0229ad20(void *);
extern void func_ov094_0229b2b0(void *);
extern void func_ov094_0229b29c(void *, void *);
extern void func_ov002_02207f20(void *, int, int, int, int);
extern int func_ov002_02207f48(void *p, int v);
extern void func_ov104_0229e924(void *self);
extern void func_ov002_02207e90(void *p, int v);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);
extern void func_ov104_0229dd00(void *arg);
extern int func_ov002_02207d24(void *p, int v);
extern void func_ov104_0229d378(void *p);
extern int func_ov104_0229c364(void *p, int v);
extern void *func_020ee45c(void *p);
extern void func_ov092_02299324(void *p, int a, int b);
extern void func_ov002_02207f04(void *p, int a, int b, int c, int d);
extern void func_020027f0(int a);
extern void func_ov104_0229c344(void *, int);
extern int func_ov002_02207f3c(void *, int);
extern int func_ov104_0229d8f8(void *ptr, unsigned char b);
extern void func_020664a8(int arg);
extern void func_0206e230(void *ptr, int a, int b, int c, int d);
extern void func_ov002_0220b53c(void *ptr, int arg);
extern int func_0206fe60(void);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov002_02207e80(int, int, int, int);
extern int func_ov002_02207f60(int);
extern int func_ov002_02207f54(UnkStruct_0229eb48 *obj);
extern void func_ov094_0229af40(void *ptr, int arg);
extern void func_ov094_0229bbd8(void *ptr, int arg);
extern void func_ov094_0229a2b0(void *ptr, int arg);
extern void func_ov002_02209e18(void *ptr);
extern void func_ov002_02209984(void *ptr, int arg1, int arg2, int arg3);
extern void func_0206e2ec(void *ptr, int arg);
extern void func_02066650(void *ptr);
extern void func_ov104_0229cb38(void *ptr);
extern void func_ov104_0229da90(void *);
extern void func_ov094_0229a038(void *);
extern void func_ov094_0229af18(void *);
extern void func_ov002_02209178(void *);
extern void func_0206e2e4(void *);
extern void func_ov002_0220af74(void *);

void func_ov104_0229ecc0(void *self);
void func_ov104_0229ec4c(UnkStruct_0229ec4c *param);
void func_ov104_0229eb88(int r0);
void func_ov104_0229eb68(int param);
void func_ov104_0229eb48(UnkStruct_0229eb48 *self);

int func_ov104_0229f03c(void)
{
    return 1;
}

int func_ov104_0229f038(void)
{
    return 1;
}

int func_ov104_0229eef8(UnkStruct_0229eef8 *self)
{
    int r;

    r = func_ov104_0229c364((void *) self, 0x400);
    if (r != 0) {
        func_ov104_0229cb04(self);
        func_0206fc4c(0);
        goto tail;
    }

    r = func_ov104_0229c364((void *) self, 0x800);
    if (r != 0) {
        r = func_ov104_0229c364((void *) self, 0x1000);
        if (r != 0) {
            return 1;
        }

        if (self->flag & 4) {
            func_0206fc4c(0);
        } else {
            func_0206fc4c(1);
        }
        func_ov104_0229caa0(self, 1);
        func_0206f990(self->flag);
        goto tail;
    } else {
        int r4;
        int r9;
        int r10;
        int z;

        func_0206fc4c(1);
        r4 = 0;
        r9 = func_020978bc(self->sub, 0xa);
        if (r9 <= 0) {
            r4 = 4;
        }

        r10 = func_02099020(func_020984e8(), 1);
        if (r10 != 0) {
            r4 |= func_ov104_0229c648(self, self->sub);
        }
        r4 |= func_ov104_0229c944(self, self->sub);
        r4 |= func_ov104_0229c870(self, self->sub, 0);

        if (r4 & 4) {
            func_0206fc4c(0);
        } else if (r4 & 0x10) {
            func_02097b24();
            r4 |= func_ov104_0229c7e8(self, self->sub);
            if (r4 & 0x20) {
                r4 |= func_ov104_0229c6a0(self, self->sub);
            }
        }

        func_ov104_0229caa0(self, 0);
        z = ((void) (func_0206f990(r4)), func_0206f8e0());
        if (z == 1 || func_0206f860() != 0) {
            func_0209aa80();
        }
    }

tail:
    func_0209788c();
    func_020ee470(self);
    return 1;
}

int func_ov104_0229eee4(int arg)
{
    func_ov104_0229c3dc(arg);
    return func_ov002_022080a8(arg);
}

void func_ov104_0229eec8(void *p)
{
    func_ov104_0229e98c();
    func_ov104_0229e978(p);
    func_ov002_02208090(p, 1);
}

void func_ov104_0229ee54(void *self)
{
    func_ov104_0229e8f8(self);
    func_ov094_0229ad20((char *) self + 0x2f8);
    func_ov094_0229b2b0((char *) self + 0xd58);
    func_ov094_0229b29c((char *) self + 0xd58, (char *) self + 0x2db4);
    func_ov104_0229d830(self);
    func_ov002_02207f20(self, 8, 0, 0, 0x30);
    func_02002708(6);
    func_ov002_02208090(self, 2);
    func_ov104_0229c354(self, 1);
    func_ov104_0229c354(self, 2);
    func_ov104_0229eb68((int) self);
}

void func_ov104_0229edf4(char *p)
{
    int cond = func_ov002_02207f48(p, 0);
    func_ov104_0229eb68((int) p);
    if (cond) {
        func_ov104_0229e924(p);
        func_ov002_02207f20(p, 2, 0, 2, 0x30);
        func_ov002_02207e90(p, 0xc0);
        func_02002708(4);
        func_ov104_0229c354(p, 0x200);
        func_ov104_0229eb48((UnkStruct_0229eb48 *) p);
        func_ov002_02208090(p, 3);
    }
}

void func_ov104_0229edcc(void *arg)
{
    if (func_ov002_02207f48(arg, 0)) {
        func_ov002_022080a0((void *) (arg), 2);
        func_ov104_0229dd00(arg);
    }
    func_ov104_0229eb48((UnkStruct_0229eb48 *) arg);
}

void func_ov104_0229ed6c(char *p)
{
    func_ov002_02207d24(p + 0x23b8, 1);
    func_ov104_0229d378(p);
    if (!func_ov104_0229c364(p, 0x100)) {
        func_ov092_02299324(func_020ee45c(p), 0x44, 1);
    }
    func_ov002_02207f04(p, 2, 0, 2, 0x30);
    func_ov002_02207e90(p, 0xc0);
    func_ov002_02208090(p, 5);
}

void func_ov104_0229ed1c(int arg)
{
    if (func_ov002_02207f3c((void *) arg, 0)) {
        func_020027f0(4);
        func_ov104_0229c344((void *) arg, 0x200);
        func_ov002_02207f04((void *) arg, 8, 0, 0, 0x30);
        func_ov002_02208090((void *) arg, 6);
        func_ov104_0229ecc0((void *) arg);
    } else {
        func_ov104_0229eb48((UnkStruct_0229eb48 *) arg);
    }
}

void func_ov104_0229ecc0(void *self)
{
    if (func_ov002_02207f3c(self, 0) != 0) {
        func_020027f0(6);
        func_ov104_0229c344(self, 2);
        if (func_ov104_0229c364(self, 0x100) != 0) {
            func_ov002_02208090(self, 7);
            func_ov104_0229ec4c((UnkStruct_0229ec4c *) self);
        } else {
            func_ov104_0229c344(self, 1);
            func_ov002_022080a0((void *) (self), 5);
        }
    } else {
        func_ov104_0229eb68((int) self);
    }
}

void func_ov104_0229ec4c(UnkStruct_0229ec4c *param)
{
    int a;
    a = func_ov104_0229d8f8(param, param->unk_B9);
    func_020664a8(a);
    func_0206e230(param->unk_2A14, a, 3, 4, 1);
    func_ov002_02207f20(param, 3, 0, 0, 0x30);
    func_02002708(3);
    func_02002708(4);
    func_ov104_0229eb88((int) param);
    func_ov002_02208090(param, 8);
    func_ov002_0220b53c(param->unk_2D3C, 0x88);
    func_ov104_0229c354(param, 0x80);
}

void func_ov104_0229ec0c(int arg)
{
    if (func_ov002_02207f48((void *) arg, 0)) {
        func_ov002_022080a0((void *) (arg), 2);
        if (func_0206fe60()) {
            func_ov002_02208098((void *) (arg), 5);
        } else {
            func_ov002_02208098((void *) (arg), 9);
        }
    } else {
        func_ov104_0229eb88(arg);
    }
}

void func_ov104_0229ebe0(void *r0)
{
    func_ov002_02207f04(r0, 3, 0, 0, 0x30);
    func_ov104_0229eb88((int) r0);
    func_ov002_02208090(r0, 0xa);
}

void func_ov104_0229eba8(void *param)
{
    if (func_ov002_02207f3c(param, 0)) {
        func_020027f0(3);
        func_020027f0(4);
        func_ov104_0229c344(param, 0x80);
        func_ov104_0229eec8(param);
    } else {
        func_ov104_0229eb88((int) param);
    }
}

void func_ov104_0229eb88(int r0)
{
    func_ov002_02207e80(r0, 3, 0, 0);
    func_ov002_02207e80(r0, 4, 0, 0);
}

void func_ov104_0229eb68(int param)
{
    int *p;
    int result;

    func_ov002_02207e80(param, 6, 0, ~0xf);
    result = func_ov002_02207f60(param);
    p = (int *) (param + 0x98);
    *p = result;
}

void func_ov104_0229eb48(UnkStruct_0229eb48 *self)
{
    func_ov002_02207e80((int) self, 4, 0, ~0xf);
    self->value = func_ov002_02207f54(self);
}

void func_ov104_0229eaa8(unsigned char *p)
{
    int i;

    *(int *) (p + 0x94) = 0;
    func_ov094_0229af40(p + 0x2f8, 2);
    func_ov094_0229bbd8(p + 0xd58, 1);
    func_ov094_0229a2b0(p + 0xd80, 6);
    *(unsigned char *) (p + 0xb6) = 0x21;
    func_ov002_02209e18(p + 0x2488);
    *(unsigned char *) (p + 0xb4) = 0;
    *(unsigned char *) (p + 0xb8) = 0x0b;
    func_ov002_02209984(p + 0x2504, 3, 0, 0);
    func_0206e2ec(p + 0x2a14, 3);
    for (i = 0; i < 10; i++) {
        func_02066650(p + 0x2db4 + i * 0x100);
    }
    func_ov104_0229cb38(p);
    *(unsigned char *) (p + 0xbf) = 0;
}

void func_ov104_0229ea5c(char *arg)
{
    func_ov104_0229da90(arg);
    func_ov094_0229a038(arg + 0xd80);
    func_ov094_0229af18(arg + 0x2f8);
    func_ov002_02209178(arg + 0x2504);
    func_0206e2e4(arg + 0x2a14);
    func_ov002_0220af74(arg + 0x41b4);
}
