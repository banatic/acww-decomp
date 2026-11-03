/* cafe_guest_7: 6 functions, module ov068
 * mwccarm 1.2/base -O4,s
 * func_ov068_02274dc8 @ 0x02274dc8, 0x118 bytes, Thumb
 * func_ov068_02274b44 @ 0x02274b44, 0x284 bytes, Thumb
 * func_ov068_02274abc @ 0x02274abc, 0x88 bytes, Thumb
 * func_ov068_02274a94 @ 0x02274a94, 0x28 bytes, Thumb
 * func_ov068_02274a80 @ 0x02274a80, 0x14 bytes, Thumb
 * func_ov068_02274a6c @ 0x02274a6c, 0x14 bytes, Thumb
 */

#include "types.h"

typedef struct {
    char pad_00[0x5c];
    int unk_5C;
    char pad_60[4];
    int unk_64;
    char pad_68[0x8e - 0x68];
    u16 unk_8E;
    char pad_90[4];
    u16 unk_94;
    char pad_96[0x2a0 - 0x96];
    char unk_2A0[0x3b0 - 0x2a0];
    char unk_3B0[0x511 - 0x3b0];
    u8 unk_511;
    char pad_512[0x65c - 0x512];
    char unk_65C[0x730 - 0x65c];
    int unk_730;
} UnkStruct_02274b44;

typedef struct {
    int lo;
    int hi;
} TM;

typedef struct {
    char pad_00[0xec];
    char unk_EC[1];
    char pad_ED[0x148 - 0xec - 1];
    int unk_148;
    char pad_14C[0x334 - 0x148 - 4];
    char unk_334[1];
    char pad_335[0x4e8 - 0x334 - 1];
    int unk_4E8;
    char pad_4EC[0x730 - 0x4e8 - 4];
    int unk_730;
} UnkStruct_02274abc;

extern void *func_020edf70(unsigned int size);
extern void *func_0203f130(void *p);
extern void *func_0205467c(void *p);
extern void func_0201b394(void *p);
extern void *func_0201a430(void *p);
extern int func_020169a8(void *p);
extern int func_0201b324(void *p);
extern void func_0201af14(void *p);
extern void func_0201b370(void *p);
extern void func_0201adec(void *p);
extern void *func_0201a7ec(void *p);
extern void func_0201a794(void *p);
extern void *func_02032c64(void *p);
extern void *func_02089c88(void *p);
extern void *func_020f55cc(void *p);
extern void func_02013c2c(void *p);
extern void *func_02019eb0(void *p);
extern void func_0201489c(void *p);
extern void *func_02082f60(void *p);
extern void *func_ov068_02274714(void *p);
extern char data_020d8c64[];
extern char data_020da088[];
extern char data_ov068_02277e50[];
extern void *data_020ccf94;
extern u8 data_021f3b85;
extern u8 data_021ebcd3;
extern u8 data_021f395c;
extern u16 data_ov068_022767ec[];
extern char data_021fbee8[];
extern int data_020c814c;
extern int func_0202edc8(void *unused0);
extern void func_0201c280(UnkStruct_02274b44 *self, char *p);
extern void func_ov068_022746c0(char *p, UnkStruct_02274b44 *self);
extern void func_0209e474(TM *t);
extern int func_02073dd4(void *g, void *h);
extern int func_0209fa30(u8 *p);
extern int func_0209ded0(void);
extern int func_02003348(int a, int b, int c, int d, int e);
extern int func_02086eb0(u8 *p);
extern int func_020af028(u8 *p);
extern unsigned int func_02086ecc(u8 *p);
extern unsigned int func_02086ec4(u8 *p);
extern int func_02086ed4(u8 *p);
extern void func_0201c400(UnkStruct_02274b44 *self, u16 *p);
extern void func_0203edf4(UnkStruct_02274b44 *self, int a);
extern void func_0201b38c(char *p, int a);
extern void func_0201b388(char *p, int a);
extern void func_0201b384(char *p, int a);
extern void func_0201ad18(char *p, int a, int b, int c, char *d, int e, int f, int g);
extern void func_0201ad88(char *p, int a);
extern int func_0202ec58(void *unused0);
extern void func_021074dc(int, int);
extern void func_ov068_022749dc(void *, int);
extern void func_02016764(void *, void *, int, int, int, int, int, int);
extern void func_02054188(void *, int, int);
extern int func_0202ec14(void *);
extern void func_ov004_02246988(void);
extern int data_ov068_02277d10[];
extern unsigned int data_ov068_02277cc8[];

void *func_ov068_02274dc8(void)
{
    void *obj = func_020edf70(0x750);
    if (obj != 0) {
        char *base = (char *) obj;
        func_0203f130(obj);
        *(void **) obj = (void *) data_020d8c64;
        *(unsigned short *) (base + 0xea) = 0xfff1;
        func_0205467c(base + 0xec);
        func_0201b394(base + 0x2a0);
        func_0201a430(base + 0x2ac);
        func_020169a8(base + 0x334);
        func_0201b324(base + 0x350);
        func_0201af14(base + 0x3a8);
        func_0201b370(base + 0x3aa);
        func_0201adec(base + 0x3b0);
        func_0201a7ec(base + 0x418);
        func_0201a794(base + 0x420);
        func_02032c64(base + 0x49c);
        func_02089c88(base + 0x4cc);
        func_020f55cc(base + 0x514);
        func_02013c2c(base + 0x558);
        func_02019eb0(base + 0x564);
        func_0201489c(base + 0x618);
        *(void **) obj = (void *) data_020da088;
        func_02082f60(base + 0x640);
        *(void **) obj = (void *) data_ov068_02277e50;
        func_ov068_02274714(base + 0x65c);
    }
    return obj;
}

int func_ov068_02274b44(UnkStruct_02274b44 *self)
{
    u16 cmd;
    TM tm;
    u8 *pp;
    u8 hh;
    u8 mm;
    int mode;
    unsigned int t;

    if (func_0202edc8(self) == 0) {
        return 0;
    }
    func_0201c280(self, self->unk_65C);
    func_ov068_022746c0(self->unk_65C, self);
    self->unk_511 = 0;
    tm.lo = 0;
    tm.hi = 0;
    func_0209e474(&tm);
    hh = ((u8 *) &tm)[2];
    mm = ((u8 *) &tm)[1];
    self->unk_730 = 8;
    if (func_02073dd4(data_020ccf94, ((void **) data_020ccf94)[0x19]) != 0) {
        return 1;
    }
    if (func_0209fa30(&data_021f3b85) != 0) {
        return 1;
    }
    pp = &data_021ebcd3;
    mode = func_0209ded0();
    switch (mode) {
        case 6:
            if ((hh == 0x13 && mm >= 0x1e) || hh == 0x14 || hh == 0x15 || hh == 0x16 || (hh == 0x17 && mm <= 0x3b)) {
                self->unk_730 = 7;
                func_02003348(0x10, 0, 0, 0, 0);
            }
            break;
        case 0:
            if (hh == 0x15 && mm < 0x37) {
                self->unk_730 = 1;
            }
            break;
        default:
            if (hh == 0x15 && mm < 0x37) {
                self->unk_730 = 1;
            }
            if (hh == 0x17 && mm <= 0x3b) {
                if (func_02086eb0(pp) != 0) {
                    if (func_020af028(&data_021f395c) == 3) {
                        self->unk_730 = 2;
                    }
                }
            }
            break;
    }
    if (hh == 0xc || (hh == 0xd && mm < 0x1e)) {
        t = func_02086ecc(pp);
        switch (t) {
            case 2:
                self->unk_730 = 5;
                break;
            case 1:
                self->unk_730 = 4;
                break;
            case 3:
                self->unk_730 = 6;
                break;
            case 4:
                self->unk_730 = 3;
                break;
        }
    }
    if ((hh == 0xe && mm >= 0x1e) || (hh == 0xf && mm <= 0x3b)) {
        t = func_02086ec4(pp);
        switch (t) {
            case 2:
                self->unk_730 = 5;
                break;
            case 1:
                self->unk_730 = 4;
                break;
            case 3:
                self->unk_730 = 6;
                break;
            case 4:
                self->unk_730 = 3;
                break;
        }
    }
    if (hh == 6 && mm < 0x37) {
        if (func_02086ed4(pp) != 0) {
            self->unk_730 = 0;
        }
    }
    cmd = data_ov068_022767ec[self->unk_730];
    func_0201c400(self, &cmd);
    if (self->unk_730 == 7) {
        func_0203edf4(self, 0x5000);
        self->unk_5C = 0xf000;
        self->unk_64 = 0x13000;
        self->unk_8E = 0;
        self->unk_94 = 0;
        func_0201b38c(self->unk_2A0, 0x102);
        func_0201b388(self->unk_2A0, 0x102);
        func_0201b384(self->unk_2A0, 0x102);
        func_0201ad18(self->unk_3B0, 0, 0, 0, data_021fbee8, 4, data_020c814c, 1);
    } else {
        func_0201b38c(self->unk_2A0, 0x1e);
        func_0201b388(self->unk_2A0, 0x1e);
        func_0201b384(self->unk_2A0, 0x1e);
        func_0201ad88(self->unk_3B0, 0);
    }
    return 1;
}

int func_ov068_02274abc(UnkStruct_02274abc *self)
{
    if (func_0202ec58(self) == 0) {
        return 0;
    }
    if (self->unk_730 == 7) {
        func_021074dc(self->unk_148, 3);
    }
    func_ov068_022749dc(self, 0);
    self->unk_4E8 |= 2;
    if (self->unk_730 == 3) {
        func_02016764((void *) self->unk_334, (void *) self, 0x142, 0, 0, 0x1000, 0, 1);
        func_02054188(&self->unk_EC, 0xc, 0xe);
    }
    return 1;
}

int func_ov068_02274a94(void *arg)
{
    if (func_0202ec14(arg) == 0) {
        return 0;
    }
    if (*(unsigned int *) ((char *) arg + 0x730) == 7) {
        func_ov004_02246988();
    }
    return 1;
}

int func_ov068_02274a80(void *ptr)
{
    return data_ov068_02277d10[*(int *) ((char *) ptr + 0x730)];
}

unsigned int func_ov068_02274a6c(unsigned int *arg)
{
    return data_ov068_02277cc8[arg[0x1CC]];
}
