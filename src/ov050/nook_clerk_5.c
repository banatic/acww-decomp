/* nook_clerk_5: 7 functions, module ov050
 * mwccarm 1.2/base -O4,s
 * func_ov050_02264f5c @ 0x02264f5c, 0x134 bytes, Thumb
 * func_ov050_02264e28 @ 0x02264e28, 0x134 bytes, Thumb
 * func_ov050_02264cf4 @ 0x02264cf4, 0x134 bytes, Thumb
 * func_ov050_02264b7c @ 0x02264b7c, 0x178 bytes, Thumb
 * func_ov050_02264974 @ 0x02264974, 0x208 bytes, Thumb
 * func_ov050_0226491c @ 0x0226491c, 0x58 bytes, Thumb
 * func_ov050_022648c4 @ 0x022648c4, 0x58 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_02264b7c {
    u8 pad_00[0x8];
    u32 mode;
    u8 pad_0C[0x50];
    u32 unk_5C;
    u32 unk_60;
    u32 unk_64;
    u8 pad_68[0x6c8];
    u16 unk_730;
    u8 pad_732[0xe];
    u8 unk_740;
};

typedef struct {
    char pad_00[0x8e];
    short unk_8E;
    char pad_90[0x94 - 0x90];
    short unk_94;
    char pad_96[0x4e8 - 0x96];
    int unk_4E8;
    char pad_4EC[0x658 - 0x4ec];
    char unk_658[0x72c - 0x658];
    u8 unk_72C;
} UnkStruct_02264974;

typedef struct {
    int a;
} UnkStruct_02264974_2;

typedef struct {
    u32 pad_00;
    u32 pad_04;
    u32 unk_08;
} UnkStruct_0226491c;

typedef struct {
    u32 pad_00;
    u32 pad_04;
    u32 unk_08;
} UnkStruct_022648c4;

extern void *func_020edf70(unsigned int);
extern void *func_0203f130(void *argument0);
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
extern void *func_ov050_022636c8(void *);
extern unsigned char data_020d8c64[];
extern unsigned char data_020da088[];
extern unsigned char data_ov050_02265a60[];
extern int func_0202edc8(void *unused0);
extern void func_0201c280(void *a, void *b);
extern void func_ov050_02263648(void *a, void *b);
extern int func_ov050_022604bc(void *a);
extern void func_0202edfc(void *a, int b, int c);
extern void func_0201c3f4(void *a, int b);
extern void func_0201af28(void *a, int b, int c, int d, int e);
extern int func_02073d90(int arg);
extern void *func_0209d358(int a, int b);
extern u16 data_020c80f8;
extern int data_020ccf94;
extern int func_0202ec58(void *argument0);
extern int func_020a7278(void);
extern int func_0208602c(void);
extern int func_020860d0(int);
extern void *func_02087f08(void *record);
extern int func_0209dffc(const unsigned char *timestamp);
extern void func_02087ef0(int);
extern void func_ov050_02264834(UnkStruct_02264974 *, int);
extern int func_020984e8(void);
extern int func_02099640(int);
extern int func_02099020(int, int);
extern void *func_0209ad9c(int, int);
extern int func_0209b4d4(void *argument0);
extern int func_02030864(int);
extern void func_ov050_02263640(void *, int);
extern int func_02087ec0(int);
extern void func_020367e4(void *);
extern unsigned int func_0209bd44(int);
extern unsigned int func_0209bba0(int);
extern unsigned int func_0209bc40(int);
extern int func_ov050_022604e0(UnkStruct_02264974 *);
extern int func_ov050_022604f8(UnkStruct_02264974 *);
extern int func_ov050_02260510(UnkStruct_02264974 *);
extern int func_020b65b8(void);
extern int func_0202ea40(UnkStruct_02264974 *, UnkStruct_02264974_2 *, int);
extern char *data_021c526c;
extern int data_ov050_02265848[5];
extern int data_ov050_0226585c[5];

void *func_ov050_02264f5c(void)
{
    void *self;
    self = func_020edf70(0x744);
    if (self != 0) {
        func_0203f130(self);
        *(void **) self = (void *) data_020d8c64;
        *(unsigned short *) ((char *) self + 0xea) = 0xfff1;
        func_0205467c((char *) self + 0xec);
        func_0201b394((char *) self + 0x2a0);
        func_0201a430((char *) self + 0x2ac);
        func_020169a8((char *) self + 0x334);
        func_0201b324((char *) self + 0x350);
        func_0201af14((char *) self + 0x3a8);
        func_0201b370((char *) self + 0x3aa);
        func_0201adec((char *) self + 0x3b0);
        func_0201a7ec((char *) self + 0x418);
        func_0201a794((char *) self + 0x420);
        func_02032c64((char *) self + 0x49c);
        func_02089c88((char *) self + 0x4cc);
        func_020f55cc((char *) self + 0x514);
        func_02013c2c((char *) self + 0x558);
        func_02019eb0((char *) self + 0x564);
        func_0201489c((char *) self + 0x618);
        *(void **) self = (void *) data_020da088;
        func_02082f60((char *) self + 0x640);
        *(void **) self = (void *) data_ov050_02265a60;
        func_ov050_022636c8((char *) self + 0x658);
        *(unsigned short *) ((char *) self + 0x732) = 0xfff1;
        *(unsigned int *) ((char *) self + 0x734) = 0;
        *(unsigned int *) ((char *) self + 0x738) = 0;
    }
    return self;
}

void *func_ov050_02264e28(void)
{
    void *p;
    p = func_020edf70(0x744);
    if (p == 0) {
        goto skip;
    }
    func_0203f130(p);
    *(void **) p = (void *) ((unsigned char *) data_020d8c64);
    *(unsigned short *) ((char *) p + 0xEA) = 0xFFF1;
    func_0205467c((char *) p + 0xEC);
    func_0201b394((char *) p + 0x2A0);
    func_0201a430((char *) p + 0x2AC);
    func_020169a8((char *) p + 0x334);
    func_0201b324((char *) p + 0x350);
    func_0201af14((char *) p + 0x3A8);
    func_0201b370((char *) p + 0x3AA);
    func_0201adec((char *) p + 0x3B0);
    func_0201a7ec((char *) p + 0x418);
    func_0201a794((char *) p + 0x420);
    func_02032c64((char *) p + 0x49C);
    func_02089c88((char *) p + 0x4CC);
    func_020f55cc((char *) p + 0x514);
    func_02013c2c((char *) p + 0x558);
    func_02019eb0((char *) p + 0x564);
    func_0201489c((char *) p + 0x618);
    *(void **) p = (void *) ((unsigned char *) data_020da088);
    func_02082f60((char *) p + 0x640);
    *(void **) p = (void *) ((unsigned char *) data_ov050_02265a60);
    func_ov050_022636c8((char *) p + 0x658);
    *(unsigned short *) ((char *) p + 0x732) = 0xFFF1;
    *(unsigned int *) ((char *) p + 0x734) = 0;
    *(unsigned int *) ((char *) p + 0x738) = 0;
skip:
    return p;
}

void *func_ov050_02264cf4(void)
{
    char *obj;
    obj = (char *) func_020edf70((unsigned long) 0x744);
    if (obj) {
        func_0203f130(obj);
        *(void **) obj = (void *) ((char *) data_020d8c64);
        *(unsigned short *) (obj + 0xea) = 0xfff1U;
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
        *(void **) obj = (void *) ((char *) data_020da088);
        func_02082f60(obj + 0x640);
        *(void **) obj = (void *) ((char *) data_ov050_02265a60);
        func_ov050_022636c8(obj + 0x658);
        *(unsigned short *) (obj + 0x732) = 0xfff1U;
        *(unsigned long *) (obj + 0x734) = 0;
        *(unsigned long *) (obj + 0x738) = 0;
    }
    return obj;
}

int func_ov050_02264b7c(struct UnkStruct_02264b7c *self)
{
    if (!func_0202edc8(self)) {
        return 0;
    }

    func_0201c280(self, (char *) self + 0x658);
    func_ov050_02263648((char *) self + 0x658, self);

    if (func_ov050_022604bc(self)) {
        func_0202edfc(self, 0xccd, 0x2000);
        func_0201c3f4(self, 0xb00);
    }

    self->unk_730 = data_020c80f8;
    func_0201af28((char *) self + 0x350, 2, 0x400, 0x133, 0x199);

    if (func_02073d90(data_020ccf94) == 0 && *(s16 *) func_0209d358(0, 0x4a) == 0) {
        goto skip_switch;
    }

    switch (self->mode) {
        case 0xd00f:
            self->unk_5C = 0xf000;
            self->unk_60 = 0;
            self->unk_64 = 0x11000;
            break;
        case 0xd010:
            self->unk_5C = 0xf000;
            self->unk_60 = 0;
            self->unk_64 = 0x13000;
            break;
        case 0xd019:
            self->unk_5C = 0xf000;
            self->unk_60 = 0;
            self->unk_64 = 0x19000;
            break;
        case 0xd01a:
            self->unk_5C = 0x13000;
            self->unk_60 = 0;
            self->unk_64 = 0x17000;
            break;
        case 0xd01b:
            self->unk_5C = 0xf000;
            self->unk_60 = 0;
            self->unk_64 = 0x15000;
            break;
        case 0xd01c:
            self->unk_5C = 0x11000;
            self->unk_60 = 0;
            self->unk_64 = 0x13000;
            break;
        default:
            break;
    }

skip_switch:
    self->unk_740 = 0;
    return 1;
}

int func_ov050_02264974(UnkStruct_02264974 *p)
{
    UnkStruct_02264974_2 t;
    int h;
    int a;
    int b;
    int c;

    if (func_0202ec58((void *) p) == 0) {
        return 0;
    }
    if (func_02073d90((int) ((*(void * *) &data_020ccf94))) != 0 || *(short *) func_0209d358(0, 0x4a) != 0) {
        p->unk_4E8 |= 2;
        if (func_020a7278() != 0) {
            if (func_0209dffc(func_02087f08((void *) func_020860d0(func_0208602c()))) != 0) {
                func_02087ef0(func_020860d0(func_0208602c()));
            }
            p->unk_8E = 0;
            p->unk_94 = 0;
            func_ov050_02264834(p, 0xd);
        } else {
            func_ov050_02264834(p, 8);
        }
        return 1;
    }

    if (func_0209dffc(func_02087f08((void *) func_020860d0(func_0208602c()))) != 0) {
        func_02087ef0(func_020860d0(func_0208602c()));
    }
    h = func_020860d0(func_0208602c());
    a = func_020984e8();
    b = func_02099640(a);
    if (func_02099020(a, 1) != 0) {

        c = func_0209b4d4((void *) func_0209ad9c(b, 0));
        func_02030864(1);
        func_ov050_02263640(p->unk_658, 5);
        func_02087ef0(h);
        if (func_02087ec0(h) != 0) {
            func_020367e4(data_021c526c + 0x2a0);
        }
        if (func_0209bd44(c) != 0 && (func_0209bba0(c) >= 1 || func_0209bc40(c) >= 0xc)) {
            func_ov050_02264834(p, 1);
        } else {
            func_ov050_02264834(p, 0);
        }
        return 1;
    }

    if (func_ov050_022604e0(p) != 0 && func_020b65b8() == 0x1d) {
        func_02087ef0(h);
        func_ov050_02264834(p, 0);
    } else if (func_ov050_022604f8(p) != 0 && func_020b65b8() == 0x1d) {
        func_ov050_02264834(p, 0xa);
    } else if (func_ov050_02260510(p) != 0 && func_020b65b8() == 0) {
        func_02087ef0(h);
        func_ov050_02264834(p, 0);
    } else {
        if (func_020b65b8() != 0x1e) {
            func_02087ef0(h);
        }
        func_ov050_02264834(p, 1);
    }
    func_02030864(0);
    if (func_ov050_02260510(p) != 0) {
        if (func_02087ec0(h) != 0) {
            func_020367e4(data_021c526c + 0x2a0);
        }
        if (func_0202ea40(p, &t, 3) != 0) {
            p->unk_72C = 1;
        }
    }
    return 1;
}

int func_ov050_0226491c(UnkStruct_0226491c *self)
{
    int result = 0;
    if (func_ov050_022604bc(self)) {
        result = 4;
    } else {
        switch (self->unk_08 - 0xd019) {
            case 0:
                result = 0;
                break;
            case 1:
                result = 1;
                break;
            case 2:
                result = 2;
                break;
            case 3:
                result = 3;
                break;
        }
    }
    return data_ov050_02265848[result];
}

int func_ov050_022648c4(UnkStruct_022648c4 *self)
{
    int result = 0;
    if (func_ov050_022604bc(self)) {
        result = 4;
    } else {
        switch (self->unk_08 - 0xd019) {
            case 0:
                result = 0;
                break;
            case 1:
                result = 1;
                break;
            case 2:
                result = 2;
                break;
            case 3:
                result = 3;
                break;
        }
    }
    return data_ov050_0226585c[result];
}
