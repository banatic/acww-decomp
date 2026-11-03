/* room_object_02250e5c: 8 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_022128a0 @ 0x022128a0, 0x1c bytes, Thumb
 * func_ov004_02212870 @ 0x02212870, 0x30 bytes, Thumb
 * func_ov004_0221284c @ 0x0221284c, 0x24 bytes, Thumb
 * func_ov004_02212820 @ 0x02212820, 0x2c bytes, Thumb
 * func_ov004_02212794 @ 0x02212794, 0x8c bytes, Thumb
 * func_ov004_0221277c @ 0x0221277c, 0x18 bytes, Thumb
 * func_ov004_02212778 @ 0x02212778, 0x4 bytes, Thumb
 * func_ov004_02212764 @ 0x02212764, 0x14 bytes, Thumb
 */

#include "types.h"

typedef struct {
    int *unk_00;
    char pad_04[0xe8];
    int *unk_EC;
} UnkStruct_0221284c;

typedef struct {
    unsigned int unk_00;
    unsigned char pad_04[0xe8];
    unsigned int unk_EC;
} UnkStruct_02212820;

extern int func_ov004_0221152c(unsigned int size);
extern void *const data_ov004_02250e5c[];
extern void *const data_ov004_02250f08[];
extern void *func_ov004_022110e4(void *p);
extern void *func_020b9e58(void *p);
extern void *func_ov004_02210cf0(void *);
extern void func_ov004_02211518(void *self);
extern void *func_ov004_0223d03c(void);
extern int func_ov004_0223d2ac(void *p);
extern void *func_ov004_0223d044(void *p);
extern int func_0203cb3c(void *p, u16 *q);
extern int func_0203cb34(void *p);
extern int func_020b9d3c(void *p, int a, void *b, int c, int d, int e);
extern int data_ov004_02253190;

void *func_ov004_02212870(char *self);

void func_ov004_022128a0(void)
{
    char *conditionInput0;

    if ((conditionInput0 = (char *) (func_ov004_0221152c(0x870)))) {
        func_ov004_02212870((char *) conditionInput0);
    }
}

void *func_ov004_02212870(char *self)
{
    func_ov004_022110e4(self);
    *(const void **) (self) = data_ov004_02250e5c;
    *(const void **) (self + 0xec) = data_ov004_02250f08;
    func_020b9e58(self + 0x848);
    return self;
}

void *func_ov004_0221284c(UnkStruct_0221284c *obj)
{
    obj->unk_00 = ((int *) data_ov004_02250e5c);
    obj->unk_EC = ((int *) data_ov004_02250f08);
    func_ov004_02210cf0(obj);
    return obj;
}

UnkStruct_02212820 *func_ov004_02212820(UnkStruct_02212820 *self)
{
    self->unk_00 = (unsigned int) ((unsigned int *) data_ov004_02250e5c);
    self->unk_EC = (unsigned int) ((unsigned int *) data_ov004_02250f08);
    func_ov004_02210cf0(self);
    func_ov004_02211518(self);
    return self;
}

int func_ov004_02212794(char *self)
{
    u16 t;
    int a;
    int r;

    *(u16 *) (self + 0x844) = (u16) func_ov004_0223d2ac(func_ov004_0223d03c());
    *(u8 *) (self + 0x846) = 0;
    t = (*(u16 *) (self + 0x844) < 0x44) ? (u16) (*(u16 *) (self + 0x844) + 0x1144) : (u16) 0x1144;
    func_0203cb3c(func_ov004_0223d044(func_ov004_0223d03c()), &t);
    a = *(int *) (self + 0x594);
    r = func_020b9d3c(self + 0x848, a, &data_ov004_02253190, func_0203cb34(func_ov004_0223d044(func_ov004_0223d03c())), 0, 0);
    if (r != 0) {
        return 1;
    }
    return 0;
}

int func_ov004_0221277c(u8 *self)
{
    self += 0x846;
    if (*self < 2) {
        *self = *self + 1;
    }
    return 1;
}

int func_ov004_02212778(void)
{
    return 1;
}

int func_ov004_02212764(char *self)
{
    // DECLS
    // ENDDECLS
    if (*(u8 *) (self + 0x846) >= 0x2) {
        return 0x1;
    }
    return 0x0;
}
