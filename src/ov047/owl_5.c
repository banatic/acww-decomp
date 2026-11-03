/* owl_5: 6 functions, module ov047
 * mwccarm 1.2/base -O4,s
 * func_ov047_02262700 @ 0x02262700, 0x118 bytes, Thumb
 * func_ov047_022626b4 @ 0x022626b4, 0x4c bytes, Thumb
 * func_ov047_022625c8 @ 0x022625c8, 0xec bytes, Thumb
 * func_ov047_02262594 @ 0x02262594, 0x34 bytes, Thumb
 * func_ov047_0226258c @ 0x0226258c, 0x8 bytes, Thumb
 * func_ov047_02262584 @ 0x02262584, 0x8 bytes, Thumb
 */

#include "types.h"

typedef struct {
    u8 pad_00[0x5c];
    u32 unk_5C;
    u8 pad_60[4];
    u32 unk_64;
    u8 pad_68[0x8e - 0x68];
    s16 unk_8E;
    u8 pad_90[4];
    s16 unk_94;
    u8 pad_96[0x4e8 - 0x96];
    u32 flags;
    u8 pad_4EC[0x72c - 0x4ec];
    u8 unk_72C;
    u8 pad_72D[1];
    u16 unk_72E;
    u8 pad_730[4];
    u16 unk_734;
    u8 pad_736[2];
    u16 unk_738;
} UnkStruct_022625c8;

extern void *func_020edf70(unsigned int size);
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
extern void *__arm func_020f55cc(void *);
extern void func_02013c2c(void *);
extern void *func_02019eb0(void *);
extern void func_0201489c(void *);
extern void *func_02082f60(void *);
extern void *func_ov047_02261990(void *);
extern unsigned char data_020d8c64[];
extern unsigned char data_020da088[];
extern unsigned char data_ov047_02262ca4[];
extern int func_0202edc8(void *p);
extern void func_0201c280(void *a, void *b);
extern void func_ov047_022618cc(void *a, void *b);
extern unsigned short data_020c80f8;
extern unsigned int data_020ccf94;
extern int func_0202ec58(void *);
extern int func_02073d90(unsigned int);
extern short *func_0209d358(int, int);
extern int func_020a7278(void);
extern int func_0209dcac(void);
extern int func_0202ea40(void *, int *, int);
extern void func_ov047_022624f4(void *, int);
extern int func_0202ec14(void *);
extern void func_0209129c(unsigned int);
extern int data_ov047_02262bf0;
extern int data_ov047_02262bc0;

void *func_ov047_02262700(void)
{
    void *self = func_020edf70(0x740);
    if (self) {
        func_0203f130(self);
        *(void **) self = (void *) data_020d8c64;
        *(unsigned short *) ((char *) self + 0xEA) = 0xfff1;
        func_0205467c((char *) self + 0xEC);
        func_0201b394((char *) self + 0x2A0);
        func_0201a430((char *) self + 0x2AC);
        func_020169a8((char *) self + 0x334);
        func_0201b324((char *) self + 0x350);
        func_0201af14((char *) self + 0x3A8);
        func_0201b370((char *) self + 0x3AA);
        func_0201adec((char *) self + 0x3B0);
        func_0201a7ec((char *) self + 0x418);
        func_0201a794((char *) self + 0x420);
        func_02032c64((char *) self + 0x49C);
        func_02089c88((char *) self + 0x4CC);
        func_020f55cc((char *) self + 0x514);
        func_02013c2c((char *) self + 0x558);
        func_02019eb0((char *) self + 0x564);
        func_0201489c((char *) self + 0x618);
        *(void **) self = (void *) data_020da088;
        func_02082f60((char *) self + 0x640);
        *(void **) self = (void *) data_ov047_02262ca4;
        func_ov047_02261990((char *) self + 0x658);
    }
    return self;
}

int func_ov047_022626b4(void *arg)
{
    if (func_0202edc8(arg) == 0) {
        return 0;
    }
    func_0201c280(arg, (char *) arg + 0x658);
    func_ov047_022618cc((char *) arg + 0x658, arg);
    *((unsigned short *) ((char *) arg + 0x730)) = data_020c80f8;
    *((int *) ((char *) arg + 0x73c)) = -1;
    return 1;
}

int func_ov047_022625c8(UnkStruct_022625c8 *self)
{
    int local[2];

    if (func_0202ec58(self) == 0) {
        return 0;
    }

    self->unk_72C = 0;
    self->unk_734 = self->unk_8E;
    self->unk_72E = 0xff;
    self->flags |= 2;
    self->unk_738 = 0;

    if (func_02073d90(data_020ccf94) != 0 || func_0209d358(0, 0x4a)[0] != 0) {
        self->flags |= 2;

        if (func_020a7278() != 0) {
            self->unk_5C = 0xf000;
            self->unk_64 = 0x15000;
            self->unk_8E = 0;
            self->unk_94 = 0;
            func_ov047_022624f4(self, 0);
        } else {
            func_ov047_022624f4(self, 6);
        }
        return 1;
    } else {
        if (func_0209dcac() == 2 || func_0209dcac() == 3 || func_0202ea40(self, local, 1) != 0) {
            func_ov047_022624f4(self, 0);
        } else {
            func_ov047_022624f4(self, 2);
        }
        return 1;
    }
}

int func_ov047_02262594(void *param)
{
    if (func_0202ec14(param) == 0) {
        return 0;
    }
    if (*(unsigned int *) ((char *) param + 0x73c) != -1) {
        func_0209129c(*(unsigned int *) ((char *) param + 0x73c));
        *(unsigned int *) ((char *) param + 0x73c) = -1;
    }
    return 1;
}

int func_ov047_0226258c(void)
{
    return (int) &data_ov047_02262bf0;
}

int func_ov047_02262584(void)
{
    return (int) &data_ov047_02262bc0;
}
