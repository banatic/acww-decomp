/* mabel_5: 5 functions, module ov049
 * mwccarm 1.2/base -O4,s
 * func_ov049_02262c80 @ 0x02262c80, 0x140 bytes, Thumb
 * func_ov049_02262c00 @ 0x02262c00, 0x80 bytes, Thumb
 * func_ov049_02262b34 @ 0x02262b34, 0xcc bytes, Thumb
 * func_ov049_02262b2c @ 0x02262b2c, 0x8 bytes, Thumb
 * func_ov049_02262b24 @ 0x02262b24, 0x8 bytes, Thumb
 */

#include "types.h"

typedef struct UnkStruct_02262b34 {
    u8 pad_00[0x5c];
    u32 unk_5C;
    u8 pad_60[4];
    u32 unk_64;
    u8 pad_68[0x26];
    u16 unk_8E;
    u8 pad_90[4];
    u16 unk_94;
    u8 pad_96[0x452];
    u32 unk_4E8;
    u8 pad_4EC[0x489];
    u8 unk_975;
} UnkStruct_02262b34;

extern void *func_020edf70(unsigned int size);
extern void *func_0203f130(void *);
extern void *func_0205467c(void *);
extern void func_0201b394(void *);
extern void *func_0201a430(void *);
extern int func_020169a8(void *);
extern int func_0201b324(void *);
extern void func_0201af14(void *);
extern void func_0201b370(void *);
extern void func_0201adec(void *);
extern void *func_0201a7ec(void *);
extern void func_0201a794(void *);
extern void *func_02032c64(void *);
extern void *func_02089c88(void *);
extern void *func_020f55cc(void *);
extern void func_02013c2c(void *);
extern void *func_02019eb0(void *);
extern void func_0201489c(void *);
extern void *func_02082f60(void *);
extern void *func_ov049_022620e8(void *);
extern char *func_02072dbc(void *);
extern unsigned char data_020d8c64;
extern unsigned char data_020da088;
extern unsigned char data_ov049_02263544;
extern int func_0202edc8(unsigned char *);
extern void func_0201c280(unsigned char *, unsigned char *);
extern void func_ov049_02262094(unsigned char *, unsigned char *);
extern void func_0202edfc(unsigned char *, int, int);
extern void func_0201c3f4(unsigned char *, int);
extern void func_0201af28(unsigned char *, int, int, int, int);
extern unsigned short data_020c80f8;
extern int data_020ccf94;
extern int func_0202ec58(UnkStruct_02262b34 *self);
extern int func_02073d90(int x);
extern short *func_0209d358(int a, int b);
extern int func_020a7278(void);
extern int func_020b65b8(void);
extern int func_02030864(int x);
extern int func_0202ea40(UnkStruct_02262b34 *self, void *buf, int n);
extern void func_ov049_02262a94(UnkStruct_02262b34 *self, int n);
extern int data_ov049_02263308;
extern int data_ov049_022632d8;

void *func_ov049_02262c80(void)
{
    unsigned char *obj = func_020edf70(0x978);
    if (obj) {
        func_0203f130(obj);
        *(void **) obj = (void *) &data_020d8c64;
        *(unsigned short *) (obj + 0xea) = 0xfff1;
        func_0205467c(obj + 0xec);
        func_0201b394(obj + 0x2a0);
        func_0201a430(obj + 0x2ac);
        func_020169a8(obj + 0x334);
        func_0201b324(obj + 0x350);
        func_0201af14(obj + 0x3a8);
        func_0201b370(obj + 0x3aa);
        func_0201adec(obj + 0x3b0);
        func_0201a7ec(obj + 0x418);
        func_0201a794(obj + 0x420);
        func_02032c64(obj + 0x49c);
        func_02089c88(obj + 0x4cc);
        func_020f55cc(obj + 0x514);
        func_02013c2c(obj + 0x558);
        func_02019eb0(obj + 0x564);
        func_0201489c(obj + 0x618);
        *(void **) obj = (void *) &data_020da088;
        func_02082f60(obj + 0x640);
        *(void **) obj = (void *) &data_ov049_02263544;
        func_ov049_022620e8(obj + 0x658);
        *(unsigned int *) (obj + 0x728) = 0;
        *(unsigned int *) (obj + 0x72c) = 0;
        *(unsigned short *) (obj + 0x738) = 0xfff1;
        func_02072dbc(obj + 0x73c);
    }
    return obj;
}

int func_ov049_02262c00(unsigned char *self)
{
    if (func_0202edc8(self) == 0) {
        return 0;
    }
    func_0201c280(self, self + 0x658);
    func_ov049_02262094(self + 0x658, self);
    func_0202edfc(self, 0x119a, 0x2000);
    func_0201c3f4(self, 0xf00);
    *(unsigned short *) (self + 0x972) = data_020c80f8;
    func_0201af28(self + 0x350, 2, 0x333, 0xcc, 0x133);
    return 1;
}

int func_ov049_02262b34(UnkStruct_02262b34 *self)
{
    u8 local[8];

    if (func_0202ec58(self) == 0) {
        return 0;
    }

    if (func_02073d90(data_020ccf94) != 0 || *func_0209d358(0, 0x4a) != 0) {
        if (func_020a7278() != 0) {
            self->unk_4E8 |= 2;
            self->unk_5C = 0xd000;
            self->unk_64 = 0x19000;
            self->unk_8E = 0;
            self->unk_94 = 0;
            func_ov049_02262a94(self, 0xa);
        } else {
            self->unk_4E8 |= 2;
            func_ov049_02262a94(self, 8);
        }
    } else {
        if (func_020b65b8() == 0) {
            func_ov049_02262a94(self, 0);
        } else {
            func_ov049_02262a94(self, 1);
        }
        func_02030864(0);
        if (func_0202ea40(self, local, 2) != 0) {
            self->unk_975 = 1;
        }
    }

    return 1;
}

int func_ov049_02262b2c(void)
{
    return (int) &data_ov049_02263308;
}

int func_ov049_02262b24(void)
{
    return (int) &data_ov049_022632d8;
}
