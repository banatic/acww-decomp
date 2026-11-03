/* boar_talk_2: 7 functions, module ov073
 * mwccarm 1.2/base -O4,s
 * func_ov073_02278ecc @ 0x02278ecc, 0x80 bytes, Thumb
 * func_ov073_02278eb4 @ 0x02278eb4, 0x18 bytes, Thumb
 * func_ov073_02278e9c @ 0x02278e9c, 0x18 bytes, Thumb
 * func_ov073_02278e7c @ 0x02278e7c, 0x20 bytes, Thumb
 * func_ov073_02278e58 @ 0x02278e58, 0x24 bytes, Thumb
 * func_ov073_02278e44 @ 0x02278e44, 0x14 bytes, Thumb
 * func_ov073_02278d94 @ 0x02278d94, 0xb0 bytes, Thumb
 */

#include "types.h"

typedef struct UnkStruct_02278ecc {
    char pad_00[0x40];
    int unk_40;
    char pad_44[0xc0 - 0x44];
    int unk_C0;
    int unk_C4;
} UnkStruct_02278ecc;

typedef struct {
    unsigned int unk_00;
    unsigned int unk_04;
} Pair;

struct ObjStruct {
    char pad_00[0xb8];
    Pair sub;
};

typedef struct {
    unsigned char pad_00[0xc4];
    int unk_C4;
} St;

typedef struct {
    unsigned short unk_00;
    unsigned short unk_02;
    unsigned char b[4];
} UnkStruct_02278d94;

extern int func_0206fc6c(void);
extern int func_0206f83c(void);
extern int func_020874c4(void *p);
extern void func_02015fb0(UnkStruct_02278ecc *self, int a, int b, int c, int d, int e);
extern void func_0206844c(int h, u8 *p, int k);
extern int data_021f3b0c;
extern int data_ov073_02279a10;
extern void *func_0202eb70(void *arg);
extern void *func_0202eb20(void *);
extern char data_ov073_02279a70[];
extern void func_020edb3c(void *self);
extern void func_0201612c(void *);
extern Pair __ptmf_null;
extern int func_02099fe8(void);
extern unsigned char func_02099f1c(void *, int (*cb)(unsigned short *));
extern int func_0209a000(unsigned short *, int);

void func_ov073_02278ecc(UnkStruct_02278ecc *self)
{
    u8 code;
    int h;
    int n;

    h = self->unk_40;
    code = 0x11;
    if (func_0206fc6c() != 0) {
        n = func_0206f83c() * 10;
        self->unk_C4 = func_0206f83c();
        self->unk_C0 = func_020874c4(&data_021f3b0c) * n;
        func_02015fb0(self, n, 1, 3, 0, 0);
        func_02015fb0(self, self->unk_C0, 2, 0xa, 0, 0);
        code = 0x13;
    }
    func_0206844c(h, &code, (int) &data_ov073_02279a10);
}

void *func_ov073_02278eb4(void *arg)
{
    func_0202eb70(arg);
    *(void **) arg = ((char *) data_ov073_02279a70);
    return arg;
}

void *func_ov073_02278e9c(void *p)
{
    *((void **) p) = (void *) ((int *) data_ov073_02279a70);
    func_0202eb20(p);
    return p;
}

void *func_ov073_02278e7c(void *self)
{
    *(void **) self = data_ov073_02279a70;
    func_0202eb20(self);
    func_020edb3c(self);
    return self;
}

void func_ov073_02278e58(struct ObjStruct *obj)
{
    func_0201612c(obj);
    obj->sub = __ptmf_null;
}

int func_ov073_02278e44(unsigned short *p)
{
    if (*p == 0xfff1) {
        return 1;
    }
    return 0;
}

int func_ov073_02278d94(St *self)
{
    int count = 0;
    int i;
    int r7 = func_02099fe8();
    int r6;
    UnkStruct_02278d94 local;

    for (i = 0; i < 10; i++) {
        if (self->unk_C4 >= 10) {
            self->unk_C4 -= 10;
            count++;
        }
    }

    r6 = count;
    if (self->unk_C4 != 0) {
        r6 = count + 1;
    }

    func_02099f1c(local.b, func_ov073_02278e44);

    if (r7 < 0 || local.b[2] < r6) {
        return 0;
    }

    while (count > 0) {
        local.unk_00 = 0x153a;
        func_0209a000(&local.unk_00, 0);
        count--;
    }

    if (self->unk_C4 > 0) {
        self->unk_C4--;
        local.unk_02 = self->unk_C4 + 0x1531;
        func_0209a000(&local.unk_02, 0);
    }

    return 1;
}
