/* mole_2: 4 functions, module ov077
 * mwccarm 1.2/base -O4,s
 * func_ov077_02279068 @ 0x02279068, 0x5c bytes, Thumb
 * func_ov077_02278fcc @ 0x02278fcc, 0x9c bytes, Thumb
 * func_ov077_02278f84 @ 0x02278f84, 0x48 bytes, Thumb
 * func_ov077_02278eb4 @ 0x02278eb4, 0xd0 bytes, Thumb
 */

#include "types.h"

typedef struct {
    u8 pad_00[0x8e];
    u16 unk_8E;
    u8 pad_90[0x94 - 0x90];
    u16 unk_94;
    u8 pad_96[0x190 - 0x96];
    u32 unk_190;
    u8 pad_194[0x724 - 0x194];
    u32 unk_724;
} UnkStruct_02278fcc;

typedef struct {
    char pad_00[0x8e];
    volatile u16 unk_8E;
    char pad_90[0x94 - 0x90];
    volatile u16 unk_94;
    char pad_96[0x190 - 0x96];
    unsigned int unk_190;
    char pad_194[0x724 - 0x194];
    int unk_724;
} UnkStruct_02278eb4;

extern int func_020912d4(int, void *, int, int);
extern int func_0200442c(void *, int, int, int);
extern void func_02035684(int, int, int);
extern int func_02096190(int);
extern u16 func_0201c314(void *a, int b);
extern int func_02016884(void *a, int b, void *c);
extern int func_02019de8(void *a);
extern void func_0209129c(int);
extern void func_ov077_02279358(void *a, int b);
extern unsigned short data_020c80f8;
extern int func_02019c20(void *p, int x, int v, char c, unsigned short a, unsigned short b);
extern void *func_0203e020(UnkStruct_02278eb4 *self);
extern int func_0208602c(void);
extern int func_020860c8(int object);
extern void func_02087e9c(unsigned char *p, int a);
extern void func_020ee470(UnkStruct_02278eb4 *self);

int func_ov077_02279068(unsigned char *self)
{
    *(unsigned int *) (self + 0x198) = 0x1000;
    *(unsigned int *) (self + 0x724) = func_020912d4(0x30, self + 0x5c, 0, 0);
    func_0200442c(self + 0x514, 0x7e6, 0x7f, 0);
    *(unsigned char *) (self + 0x510) = 1;
    func_02035684(0x17, 0xf, 0);
    return 1;
}

int func_ov077_02278fcc(void *self)
{
    UnkStruct_02278fcc *p = (UnkStruct_02278fcc *) self;
    u16 v;
    u32 w;
    signed short val;

    v = func_0201c314(self, func_02096190(4));
    p->unk_8E = v;
    p->unk_94 = v;

    w = p->unk_190;
    val = (signed short) ((w << 4) >> 16);
    if (val == 12) {
        func_0209129c(p->unk_724);
        p->unk_724 = -1;
    }

    if (func_02016884((char *) self + 0x334, 0xfd, (char *) self + 0x2a0) != 0 && func_02019de8((char *) self + 0x564) != 0) {
        if (p->unk_724 != -1) {
            func_0209129c(p->unk_724);
            p->unk_724 = -1;
        }
        func_ov077_02279358(self, 1);
        return 1;
    }
    return 1;
}

int func_ov077_02278f84(void *p)
{
    func_02019c20((char *) p + 0x564, 1, 0xfe, 1, data_020c80f8, 0);
    func_0200442c((char *) p + 0x514, 0x7e7, 0x7f, 0);
    return 1;
}

int func_ov077_02278eb4(UnkStruct_02278eb4 *self)
{
    u16 r;
    unsigned int v;
    short k;

    r = func_0201c314((void *) self, func_02096190(4));
    self->unk_8E = r;
    self->unk_94 = r;
    v = self->unk_190;
    k = (short) ((v << 4) >> 16);
    if (k == 2) {
        self->unk_724 = func_020912d4(0x30, (char *) self + 0x5c, 0, 0);
    }
    if (k == 0xc) {
        if (self->unk_724 != -1) {
            func_0209129c(self->unk_724);
            self->unk_724 = -1;
        }
    }
    if (func_02016884((char *) self + 0x334, 0xfe, (char *) self + 0x2a0) != 0 && func_02019de8((char *) self + 0x564) != 0) {
        func_02087e9c((unsigned char *) func_020860c8(((void) (func_0203e020(self)), func_0208602c())), 0);
        func_020ee470(self);
        if (self->unk_724 != -1) {
            func_0209129c(self->unk_724);
            self->unk_724 = -1;
        }
        return 1;
    }
    return 1;
}
