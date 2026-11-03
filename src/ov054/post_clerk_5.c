/* post_clerk_5: 6 functions, module ov054
 * mwccarm 1.2/base -O4,s
 * func_ov054_0226285c @ 0x0226285c, 0x118 bytes, Thumb
 * func_ov054_022626e0 @ 0x022626e0, 0x17c bytes, Thumb
 * func_ov054_02262620 @ 0x02262620, 0xc0 bytes, Thumb
 * func_ov054_022625e0 @ 0x022625e0, 0x40 bytes, Thumb
 * func_ov054_022625cc @ 0x022625cc, 0x14 bytes, Thumb
 * func_ov054_022625b8 @ 0x022625b8, 0x14 bytes, Thumb
 */

#include "types.h"

typedef struct UnkStruct_0226285c {
    void *vtable;
    char pad_04[0xe6];
    unsigned short version;
    unsigned char sub_ec[0x1b4];
    unsigned char unk_2A0[0xc];
    unsigned char unk_2AC[0x88];
    unsigned char unk_334[0x1c];
    unsigned char unk_350[0x58];
    unsigned char unk_3A8[0x2];
    unsigned char unk_3AA[0x6];
    unsigned char unk_3B0[0x68];
    unsigned char unk_418[0x8];
    unsigned char unk_420[0x7c];
    unsigned char unk_49C[0x30];
    unsigned char unk_4CC[0x48];
    unsigned char unk_514[0x44];
    unsigned char unk_558[0xc];
    unsigned char unk_564[0xb4];
    unsigned char unk_618[0x28];
    unsigned char unk_640[0x18];
    unsigned char unk_658[0x1];
} UnkStruct_0226285c;

typedef struct UnkStruct_022626e0 {
    char pad_00[0x5c];
    u32 unk_5C;
    u32 unk_60;
    u32 unk_64;
    char pad_68[0xea - 0x68];
    u16 unk_EA;
    char pad_EC[0x350 - 0xec];
    char pad_350[0x658 - 0x350];
    char pad_658[0x808 - 0x658];
    u32 unk_808;
    u32 unk_80C;
    char pad_810[0x812 - 0x810];
    u16 unk_812;
} UnkStruct_022626e0;

typedef struct UnkStruct_022626e0_2 {
    u8 pad_00;
    u8 type;
    u16 unk_02;
    u16 unk_04;
    u16 arr0[3];
} UnkStruct_022626e0_2;

typedef struct {
    unsigned char pad_00[0x8e];
    short unk_8E;
    unsigned char pad_90[0x4e8 - 0x90];
    int unk_4E8;
    unsigned char pad_4EC[0x804 - 0x4ec];
    short unk_804;
    unsigned char pad_806[0x808 - 0x806];
    int unk_808;
} UnkStruct_02262620;

typedef struct {
    unsigned char pad_00[0x808];
    unsigned int idx;
} Struct_ov054_022625b8;

extern void *func_020edf70(int);
extern void *func_0203f130(void *arg0);
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
extern void *func_ov054_02261fb0(void *);
extern unsigned char data_020d8c64[];
extern unsigned char data_020da088[];
extern unsigned char data_ov054_02263094[];
extern int func_0202edc8(void *self);
extern void func_0201c280(void *self, void *p);
extern void func_ov054_02261f5c(void *p, void *self);
extern int func_ov054_02260474(void *self);
extern int func_0204bcdc(void *p);
extern int func_0204bc64(void *p);
extern void func_0209def4(void *p);
extern int func_020a12e8(void);
extern int func_02003348(int a, int b, void *c, void *d, void *e);
extern void func_0201af28(void *p, int a, int b, int c, int d);
extern void func_0201c400(void *self, void *p);
extern void func_0203edf4(void *self, int a);
extern u16 data_ov054_02262990[];
extern u32 data_ov054_022629e0[];
extern u16 data_020c80f8;
extern int func_0202ec58(void *arg0);
extern void *func_020984e8(void);
extern int func_020a7278(void);
extern void func_ov054_02262528(UnkStruct_02262620 *self, int mode);
extern int func_02099020(void *p, int k);
extern void func_020356c4(int a, int b, int c, int d);
extern int func_0202ec14(void *arg0);
extern void func_02035638(int);
extern int data_ov054_02262d28[];
extern unsigned int data_ov054_02262df8[];

UnkStruct_0226285c *func_ov054_0226285c(void)
{
    UnkStruct_0226285c *obj = (UnkStruct_0226285c *) func_020edf70(0x818);
    if (obj == (UnkStruct_0226285c *) 0) {
        goto done;
    }

    func_0203f130((void *) obj);
    obj->vtable = (void *) data_020d8c64;
    obj->version = 0xfff1;

    func_0205467c(&obj->sub_ec);
    func_0201b394(&obj->unk_2A0);
    func_0201a430(&obj->unk_2AC);
    func_020169a8(&obj->unk_334);
    func_0201b324(&obj->unk_350);
    func_0201af14(&obj->unk_3A8);
    func_0201b370(&obj->unk_3AA);
    func_0201adec(&obj->unk_3B0);
    func_0201a7ec(&obj->unk_418);
    func_0201a794(&obj->unk_420);
    func_02032c64(&obj->unk_49C);
    func_02089c88(&obj->unk_4CC);
    func_020f55cc(&obj->unk_514);
    func_02013c2c(&obj->unk_558);
    func_02019eb0(&obj->unk_564);
    func_0201489c(&obj->unk_618);

    obj->vtable = (void *) data_020da088;
    func_02082f60(&obj->unk_640);

    obj->vtable = (void *) data_ov054_02263094;
    func_ov054_02261fb0(&obj->unk_658);

done:
    return obj;
}

int func_ov054_022626e0(void *self)
{
    UnkStruct_022626e0_2 info;
    u32 vec3[3];
    int flag;
    int a;
    int b;
    unsigned int r5;

    if (func_0202edc8(self) == 0) {
        return 0;
    }

    func_0201c280(self, (char *) self + 0x658);
    func_ov054_02261f5c((char *) self + 0x658, self);

    if (func_ov054_02260474(self)) {
        if (func_0204bcdc((char *) self + 0xea)) {
            info.unk_04 = data_ov054_02262990[0];
            a = func_0204bc64((char *) self + 0xea);
            b = func_0204bc64(&info.unk_04);
            if (a == b) {
                flag = 1;
            } else {
                flag = 0;
            }
        } else {
            if (*(u16 *) ((char *) self + 0xea) == data_ov054_02262990[0]) {
                flag = 1;
            } else {
                flag = 0;
            }
        }

        if (flag) {
            ((UnkStruct_022626e0 *) self)->unk_808 = 0;
            ((UnkStruct_022626e0 *) self)->unk_80C = 1;
            ((UnkStruct_022626e0 *) self)->unk_5C = data_ov054_022629e0[3];
            ((UnkStruct_022626e0 *) self)->unk_60 = data_ov054_022629e0[4];
            ((UnkStruct_022626e0 *) self)->unk_64 = data_ov054_022629e0[5];
            info.arr0[0] = 0;
            info.arr0[1] = 0;
            info.arr0[2] = 0;
            vec3[0] = data_ov054_022629e0[0];
            vec3[1] = data_ov054_022629e0[1];
            vec3[2] = data_ov054_022629e0[2];
            func_02003348(0x7a, data_ov054_02262990[1], vec3, info.arr0, self);
        } else {
            ((UnkStruct_022626e0 *) self)->unk_808 = 1;
            ((UnkStruct_022626e0 *) self)->unk_80C = 0;
            ((UnkStruct_022626e0 *) self)->unk_5C = data_ov054_022629e0[0];
            ((UnkStruct_022626e0 *) self)->unk_60 = data_ov054_022629e0[1];
            ((UnkStruct_022626e0 *) self)->unk_64 = data_ov054_022629e0[2];
        }
    } else {
        func_0209def4(&info);
        r5 = info.type;
        ((UnkStruct_022626e0 *) self)->unk_808 = 0;
        if (func_020a12e8() == 0) {
            if (r5 >= 0x16 || r5 < 7) {
                ((UnkStruct_022626e0 *) self)->unk_808 = 1;
            }
        }
        func_0201af28((char *) self + 0x350, 2, 0x399, 0xcc, 0x133);
        info.unk_02 = data_ov054_02262990[((UnkStruct_022626e0 *) self)->unk_808];
        func_0201c400(self, &info.unk_02);
        *(u16 *) ((char *) self + 0xea) = data_ov054_02262990[((UnkStruct_022626e0 *) self)->unk_808];
    }

    func_0203edf4(self, 0x5000);
    ((UnkStruct_022626e0 *) self)->unk_812 = data_020c80f8;
    return 1;
}

int func_ov054_02262620(UnkStruct_02262620 *self)
{
    void *p;

    if (!func_0202ec58((void *) self)) {
        return 0;
    }

    p = func_020984e8();

    if (func_ov054_02260474(self)) {
        if (func_020a7278()) {
            func_ov054_02262528(self, 2);
        } else {
            func_ov054_02262528(self, 9);
        }
    } else {
        if (func_020a12e8() != 0 && func_02099020(p, 9) == 0) {
            func_ov054_02262528(self, 0);
        } else {
            func_ov054_02262528(self, 2);
        }
    }

    self->unk_804 = self->unk_8E;
    self->unk_4E8 |= 2;

    if (self->unk_808 == 0) {
        func_020356c4(0x11, 0x55, 0x7f, 0);
    } else if (self->unk_808 == 1) {
        if (func_ov054_02260474(self) == 0) {
            func_020356c4(0x11, 0x56, 0x7f, 0);
        }
    }

    return 1;
}

int func_ov054_022625e0(void *p)
{
    int r;
    if (!func_0202ec14((void *) p)) {
        return 0;
    }
    r = *(int *) ((char *) p + 0x808);
    if (r == 0) {
        func_02035638(0x55);
    } else if (r == 1) {
        if (!func_ov054_02260474(p)) {
            func_02035638(0x56);
        }
    }
    return 1;
}

int func_ov054_022625cc(void *obj)
{
    return data_ov054_02262d28[*(int *) ((char *) obj + 0x808)];
}

unsigned int func_ov054_022625b8(Struct_ov054_022625b8 *obj)
{
    return data_ov054_02262df8[obj->idx];
}
