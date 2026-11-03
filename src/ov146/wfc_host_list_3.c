/* wfc_host_list_3: 10 functions, module ov146
 * mwccarm 1.2/base -O4,s
 * func_ov146_0229af0c @ 0x0229af0c, 0x4 bytes, Thumb
 * func_ov146_0229af08 @ 0x0229af08, 0x4 bytes, Thumb
 * func_ov146_0229aef8 @ 0x0229aef8, 0x10 bytes, Thumb
 * func_ov146_0229ae90 @ 0x0229ae90, 0x66 bytes, Thumb
 * func_ov146_0229ae60 @ 0x0229ae60, 0x30 bytes, Thumb
 * func_ov146_0229ae28 @ 0x0229ae28, 0x38 bytes, Thumb
 * func_ov146_0229adf8 @ 0x0229adf8, 0x30 bytes, Thumb
 * func_ov146_0229adb8 @ 0x0229adb8, 0x3e bytes, Thumb
 * func_ov146_0229acfc @ 0x0229acfc, 0xbc bytes, Thumb
 * func_ov146_0229ace8 @ 0x0229ace8, 0x14 bytes, Thumb
 */

#include "types.h"

typedef struct UnkStruct_0229adb8 {
    unsigned char pad_00[0x94];
    int unk_94;
    unsigned char pad_98[0x0c];
    int unk_A4;
} UnkStruct_0229adb8;

extern void func_020ee470(void *parameter0);
extern void func_ov146_0229abe0(void);
extern void func_ov146_0229ab28(void *);
extern int func_ov146_02299f08(void *);
extern void func_ov146_02299dec(void *, int);
extern void func_ov146_0229aac8(void *receiver);
extern void func_ov002_02207f20(void *, int, int, int, int);
extern void func_02002708(int);
extern void func_ov146_02299660(void *, int);
extern void func_ov002_02208090(void *, int);
extern int func_ov002_02207f48(void *p, int x);
extern unsigned char *func_ov002_022080a0(void *p, unsigned char value);
extern void func_ov146_0229a724(void *p);
extern void func_ov146_0229a17c(void *p);
extern void *func_020ee45c(void *obj);
extern void func_ov092_02299324(void *a, int b, int c);
extern void func_ov002_02207f04(void *obj, int a, int b, int c, int d);
extern int func_ov002_02207f3c(void *, int);
extern void func_020027f0(int);
extern void func_ov002_02207e80(UnkStruct_0229adb8 *self, int a, int b, int c);
extern int func_ov002_02207f60(UnkStruct_0229adb8 *self);
extern void func_ov146_02299b58(UnkStruct_0229adb8 *self);
extern void func_ov002_0220b04c(u8 *);
extern void func_ov002_0220b06c(u8 *, int, int, int);
extern void func_0208aa70(u8 *);
extern void func_ov002_0220a580(u8 *);
extern void func_ov146_0229a0f8(u8 *);
extern void func_ov146_0229a400(int arg0);
extern void func_ov146_022997c8(int arg0);

void func_ov146_0229adb8(UnkStruct_0229adb8 *self);

int func_ov146_0229af0c(void)
{
    return 1;
}

int func_ov146_0229af08(void)
{
    return 1;
}

int func_ov146_0229aef8(void *arg0)
{
    func_020ee470((void *) arg0);
    return 1;
}

void func_ov146_0229ae90(void *r0)
{
    void *r4 = r0;
    int sp0;
    int sp4;

    func_ov146_0229abe0();
    func_ov146_0229ab28(r4);
    func_ov146_02299f08(r4);
    func_ov146_02299dec(r4, 0);
    *(int *) ((char *) r4 + 0xa8) = 0;
    func_ov146_0229aac8(r4);
    sp0 = 0x28;
    func_ov002_02207f20(r4, 0xa, 4, 0, sp0);
    func_02002708(6);
    func_02002708(4);
    func_ov146_0229adb8((UnkStruct_0229adb8 *) r4);
    func_ov146_02299660(r4, 1);
    func_ov002_02208090(r4, 1);
}

void func_ov146_0229ae60(void *p)
{
    if (func_ov002_02207f48(p, 0)) {
        func_ov002_022080a0(p, 2);
        func_ov146_0229a724(p);
    } else {
        func_ov146_0229a17c(p);
    }
    func_ov146_0229adb8((UnkStruct_0229adb8 *) p);
}

void func_ov146_0229ae28(void *obj)
{
    int zero = 0;

    func_ov092_02299324(func_020ee45c(obj), 0x44, 1);
    func_ov002_02207f04(obj, 10, zero, zero, 0x28);
    func_ov146_0229adb8((UnkStruct_0229adb8 *) obj);
    func_ov002_02208090(obj, 3);
}

void func_ov146_0229adf8(void *p)
{
    if (func_ov002_02207f3c(p, 0)) {
        func_020027f0(6);
        func_020027f0(4);
        func_ov002_022080a0(p, 5);
    } else {
        func_ov146_0229adb8((UnkStruct_0229adb8 *) p);
    }
}

void func_ov146_0229adb8(UnkStruct_0229adb8 *self)
{
    func_ov002_02207e80(self, 6, 0, 0);
    func_ov002_02207e80(self, 4, 0, 0x38 - self->unk_A4);
    self->unk_94 = func_ov002_02207f60(self);
    func_ov146_02299b58(self);
}

void func_ov146_0229acfc(u8 *self)
{
    int i;
    int j;

    *(u16 *) (self + 0xac) = 0;
    *(self + 0xb2) = 3;
    *(self + 0xb0) = 9;
    *(self + 0xb1) = 8;
    func_ov002_0220b04c(self + 0x1ee8);
    func_ov002_0220b06c(self + 0x1ee8, 0x7f, 0x90, 0x10);
    func_0208aa70(self + 0x1ee8);
    *(self + 0xb5) = 0;
    func_ov002_0220a580(self + 0x1fb4);
    for (i = 0; i < 7; i++) {
        *(self + i + 0xbc) = 0x21;
        *(self + i + 0xc3) = 0xff;
    }
    for (j = 0; j < 0x20; j++) {
        *(self + j + 0xea) = 0x20;
        *(self + j + 0x10a) = 0;
    }
    func_ov146_0229a0f8(self);
    *(self + 0xb6) = 0x21;
    *(self + 0xb7) = 0xa;
    *(self + 0xb8) = 0;
    *(self + 0xb9) = 0xa;
    *(self + 0xbb) = 0x20;
}

void func_ov146_0229ace8(int arg0)
{
    func_ov146_0229a400(arg0);
    func_ov146_022997c8(arg0);
}
