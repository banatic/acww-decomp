/* tune_editor_states: 18 functions, module ov143
 * mwccarm 1.2/base -O4,s
 * func_ov143_0229a570 @ 0x0229a570, 0x32 bytes, Thumb
 * func_ov143_0229a54c @ 0x0229a54c, 0x24 bytes, Thumb
 * func_ov143_0229a4e0 @ 0x0229a4e0, 0x6c bytes, Thumb
 * func_ov143_0229a438 @ 0x0229a438, 0xa8 bytes, Thumb
 * func_ov143_0229a404 @ 0x0229a404, 0x34 bytes, Thumb
 * func_ov143_0229a3e0 @ 0x0229a3e0, 0x24 bytes, Thumb
 * func_ov143_0229a374 @ 0x0229a374, 0x6c bytes, Thumb
 * func_ov143_0229a334 @ 0x0229a334, 0x40 bytes, Thumb
 * func_ov143_0229a31c @ 0x0229a31c, 0x16 bytes, Thumb
 * func_ov143_0229a300 @ 0x0229a300, 0x1c bytes, Thumb
 * func_ov143_0229a2e0 @ 0x0229a2e0, 0x20 bytes, Thumb
 * func_ov143_0229a2c8 @ 0x0229a2c8, 0x16 bytes, Thumb
 * func_ov143_0229a2a4 @ 0x0229a2a4, 0x24 bytes, Thumb
 * func_ov143_0229a284 @ 0x0229a284, 0x20 bytes, Thumb
 * func_ov143_0229a230 @ 0x0229a230, 0x54 bytes, Thumb
 * func_ov143_0229a200 @ 0x0229a200, 0x30 bytes, Thumb
 * func_ov143_0229a1a4 @ 0x0229a1a4, 0x5c bytes, Thumb
 * func_ov143_0229a16c @ 0x0229a16c, 0x38 bytes, Thumb
 */

#include "types.h"

typedef struct UnkSelf {
    unsigned char pad[0xa4];
    unsigned char unk_A4;
} UnkSelf;

typedef struct {
    char pad_00[0xA0];
    unsigned char *arr;
    char pad_A4[0x6C];
    char data[1];
} UnkStruct_0229a404;

typedef struct Func_ov143_0229a1a4_s {
    u8 pad_00[0x9C];
    u16 unk_9C;
    u8 pad_9E[2];
    void *unk_A0;
} Func_ov143_0229a1a4_t;

typedef struct Func_ov143_0229a16c_s {
    unsigned char pad_00[0x9C];
    short unk_9C;
} Func_ov143_0229a16c_t;

extern int func_0208e484(void *);
extern int func_ov143_02299e18(void *, unsigned char);
extern unsigned char *func_ov002_02208098(void *, unsigned char value);
extern void func_ov143_02299f48(void *);
extern void func_ov143_02299f84(void *self);
extern int func_ov002_02208054(void *self, int kind);
extern int func_ov002_0220a784(void *field, int kind);
extern unsigned char data_021fbdd8;
extern unsigned char data_021fbddc;
extern int func_ov002_02208014(void *receiver);
extern char *func_ov002_02208008(UnkSelf *self);
extern int func_ov002_02207fe4(UnkSelf *self);
extern int func_ov002_02207fd8(UnkSelf *self);
extern void func_ov143_02299fd0(UnkSelf *self);
extern void func_ov143_02299f6c(UnkSelf *self);
extern struct {
    unsigned char pad[2];
    unsigned short flags;
} data_021fbe40;
extern void func_ov143_02299a9c(UnkStruct_0229a404 *);
extern void *func_ov002_0220a720(void *, int);
extern void func_0200467c(int command);
extern int func_ov002_0220a700(void *ptr);
extern int func_0208e4bc(void *ptr);
extern int func_ov002_0220a6e0(void *ptr);
extern int func_ov002_0220a768(void *ptr, int);
extern int func_ov002_0220a72c(void *ptr, int);
extern void func_ov002_0220a0b4(void *ptr, int, int);
extern void func_ov143_0229a014(void *ptr);
extern unsigned char *func_ov002_022080a0(void *ptr, unsigned char value);
extern int data_020df2a0;
extern int func_ov143_02299650(char *param, int x);
extern void func_ov143_02299b04(char *param);
extern void func_ov143_02299630(char *param, int x);
extern void func_ov143_0229a134(void *);
extern void func_ov002_02207fc0(void *);
extern int func_0206fe60(void);
extern void func_0206fc4c(int);
extern void func_ov002_02208090(void *, int);
extern void func_0206ea84(void *, void *);
extern void func_0206ea28(void);
extern void func_0207a500(void *);
extern unsigned char data_021e5a2c[];
extern unsigned char data_021f3b68[];
extern void *data_020ccf94;
extern int func_02073d90(void *);
extern void func_02073820(void *);
extern void func_020737f0(void *, void *, int);
extern void func_02073770(void *, int, int);
extern int func_02073d80(void *);
extern void MI_CpuCopy8(void *, void *, int);
extern int func_0206fc6c(void);
extern int func_02074fec(int);

void func_ov143_0229a404(UnkStruct_0229a404 *obj);
void func_ov143_0229a3e0(void *arg);
void func_ov143_0229a2c8(void *p);
void func_ov143_0229a2a4(void *self);
void func_ov143_0229a1a4(Func_ov143_0229a1a4_t *self);

void func_ov143_0229a570(void *self)
{
    if (func_0208e484((char *) self + 0xac)) {
        if (!func_ov143_02299e18(self, *(unsigned char *) ((char *) self + 0xa4))) {
            func_ov002_02208098(self, 2);
            func_ov143_02299f48(self);
        }
    }
}

void func_ov143_0229a54c(char *self)
{
    if (!func_0208e484(self + 0xac)) {
        return;
    }
    func_ov143_02299f84(self);
    func_ov002_02208098(self, *(unsigned char *) (self + 0x9e));
}

void func_ov143_0229a4e0(void *self)
{
    unsigned int flag;

    if (func_ov002_02208054(self, 1)) {
        func_ov143_0229a2a4(self);
        return;
    }

    flag = (data_021fbdd8 && data_021fbddc) ? 1 : 0;
    if (flag == 0) {
        return;
    }

    if (func_ov002_0220a784((char *) self + 0x110, 3)) {
        func_ov143_0229a404((UnkStruct_0229a404 *) self);
    } else if (func_ov002_0220a784((char *) self + 0x110, 4)) {
        func_ov143_0229a3e0(self);
    }
}

void func_ov143_0229a438(UnkSelf *self)
{
    unsigned char old;
    unsigned short flags;

    if (func_ov002_02208014(self) != 0) {
        func_ov143_0229a2c8((void *) self);
        return;
    }

    old = self->unk_A4;
    func_ov002_02208008(self);

    if (func_ov002_02207fe4(self) != 0) {
        self->unk_A4 = 0x14;
    } else if (func_ov002_02207fd8(self) != 0) {
        self->unk_A4 = 0x15;
    }

    if (old != self->unk_A4) {
        func_ov143_02299fd0(self);
        return;
    }

    flags = data_021fbe40.flags;

    if ((flags & 1) != 0) {
        func_ov143_02299f6c(self);
        return;
    }

    if ((flags & 2) != 0) {
        func_ov143_0229a014((void *) self);
        func_ov143_0229a3e0((void *) self);
        return;
    }

    if ((flags & 8) != 0) {
        func_ov143_0229a014((void *) self);
        func_ov143_0229a404((UnkStruct_0229a404 *) self);
    }
}

void func_ov143_0229a404(UnkStruct_0229a404 *obj)
{
    int i;

    func_ov143_02299a9c(obj);
    func_ov002_0220a720(obj->data, 3);
    func_0200467c(0x5a);

    for (i = 0; i < 16; i++) {
        obj->arr[i] = 0xf;
    }
}

void func_ov143_0229a3e0(void *arg)
{
    func_ov143_02299a9c((UnkStruct_0229a404 *) ((int) (arg)));
    func_0200467c(0x2a);
    func_ov002_0220a720((char *) arg + 0x110, 4);
}

void func_ov143_0229a374(char *self)
{
    if (func_ov002_0220a700(self + 0x110)) {
        int a, b, c;
        if (func_0208e4bc(self + 0xac) == 0) {
            return;
        }
        a = func_ov002_0220a6e0(self + 0x110);
        b = func_ov002_0220a768(self + 0x110, -1);
        c = func_ov002_0220a72c(self + 0x110, -1);
        func_ov002_0220a0b4(self + 0xac, a + (b - 6), a + c);
    } else {
        func_ov143_0229a014(self);
        func_ov002_022080a0(self, 1);
    }
}

void func_ov143_0229a334(char *param)
{
    int g = data_020df2a0;
    if (g == -1 || g >= 16) {
        if (func_ov143_02299650(param, 8) != 0) {
            return;
        }
        func_ov143_02299b04(param);
        return;
    } else {
        func_ov143_02299630(param, 8);
        param += 0x9a;
        *(unsigned short *) param = (unsigned short) g;
    }
}

void func_ov143_0229a31c(void *param)
{
    func_ov143_0229a014(param);
    func_ov002_02208098(param, 0);
}

void func_ov143_0229a300(void *arg0)
{
    func_ov143_0229a134(arg0);
    func_ov002_02207fc0(arg0);
    func_ov002_02208098(arg0, 2);
}

void func_ov143_0229a2e0(int param)
{
    int r4 = param;
    if (func_0206fe60() != 0) {
        func_ov143_0229a31c((void *) r4);
    } else {
        func_ov143_0229a300((void *) r4);
    }
}

void func_ov143_0229a2c8(void *p)
{
    func_ov143_0229a014(p);
    func_ov002_02208098(p, 7);
}

void func_ov143_0229a2a4(void *self)
{
    char *p = (char *) self + 0xa4;
    *p = 0x15;
    func_ov143_0229a134(self);
    func_ov002_02207fc0(self);
    func_ov002_02208098(self, 8);
}

void func_ov143_0229a284(int r0)
{
    int r4 = r0;
    if (func_0206fe60() != 0) {
        func_ov143_0229a2c8((void *) r4);
    } else {
        func_ov143_0229a2a4((void *) r4);
    }
}

void func_ov143_0229a230(void *arg0)
{
    func_0206fc4c(1);
    func_ov002_0220a720((char *) arg0 + 0x110, 1);
    func_ov002_02208090(arg0, 2);
    func_ov002_02208098(arg0, 9);
    func_0206ea84((void *) data_021f3b68, *(void **) ((char *) arg0 + 0xa0));
    func_0206ea28();
    func_0207a500((void *) data_021e5a2c);
    func_ov143_0229a1a4((Func_ov143_0229a1a4_t *) arg0);
}

void func_ov143_0229a200(void *self)
{
    func_0206fc4c(0);
    func_ov002_0220a720((char *) self + 0x110, 2);
    func_ov002_02208090(self, 2);
    func_ov002_02208098(self, 9);
}

void func_ov143_0229a1a4(Func_ov143_0229a1a4_t *self)
{
    u8 buf[0x11];
    void *obj;

    if (func_02073d90(data_020ccf94) != 0) {
        buf[0] = 0xC;
        MI_CpuCopy8(self->unk_A0, buf + 1, 0x10);
        obj = data_020ccf94;
        func_02073820(obj);
        func_020737f0(obj, buf, 0x11);
        func_02073770(obj, 0x16, 4);
        self->unk_9C = (u16) func_02073d80(obj);
    }
}

int func_ov143_0229a16c(Func_ov143_0229a16c_t *self)
{
    if (func_0206fc6c() == 0) {
        return 1;
    }
    if (func_02073d90(data_020ccf94) != 0) {
        if (func_02074fec(self->unk_9C) == 0) {
            return 0;
        }
    }
    return 1;
}
