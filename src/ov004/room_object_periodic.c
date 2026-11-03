/* room_object_periodic: 5 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02212050 @ 0x02212050, 0x1c bytes, Thumb
 * func_ov004_0221202c @ 0x0221202c, 0x24 bytes, Thumb
 * func_ov004_02212008 @ 0x02212008, 0x24 bytes, Thumb
 * func_ov004_02211fdc @ 0x02211fdc, 0x2c bytes, Thumb
 * func_ov004_02211ed4 @ 0x02211ed4, 0x108 bytes, Thumb
 */

#include "types.h"

typedef struct {
    int *unk_00;
    char pad_04[0xe8];
    int *unk_EC;
} UnkStruct_02212008;

typedef struct {
    unsigned int unk_00;
    unsigned char pad_04[0xe8];
    unsigned int unk_EC;
} UnkStruct_02211fdc;

extern int func_ov004_0221152c(unsigned int size);
extern void *func_ov004_022110e4(void *);
extern char data_ov004_02252a7c;
extern char data_ov004_02252b28;
extern void *func_ov004_02210cf0(void *);
extern void func_ov004_02211518(void *self);
extern void func_ov004_0221041c(void *self, int a, int b, int c, int d);
extern void *func_ov004_0220fde0(void *self);
extern int func_ov004_0223a760(void *p);
extern u16 func_020644cc(int a);
extern u16 func_ov004_0221062c(void *self, int k);

void *func_ov004_0221202c(void *this);

void func_ov004_02212050(void)
{
    void *conditionInput0;

    if ((conditionInput0 = (void *) (func_ov004_0221152c(0x850)))) {
        func_ov004_0221202c((void *) conditionInput0);
    }
}

void *func_ov004_0221202c(void *this)
{
    func_ov004_022110e4(this);
    *(void **) this = &data_ov004_02252a7c;
    *(void **) ((char *) this + 0xec) = &data_ov004_02252b28;
    return this;
}

void *func_ov004_02212008(UnkStruct_02212008 *obj)
{
    obj->unk_00 = ((int *) &data_ov004_02252a7c);
    obj->unk_EC = ((int *) &data_ov004_02252b28);
    func_ov004_02210cf0(obj);
    return obj;
}

UnkStruct_02211fdc *func_ov004_02211fdc(UnkStruct_02211fdc *self)
{
    self->unk_00 = (unsigned int) ((unsigned int *) &data_ov004_02252a7c);
    self->unk_EC = (unsigned int) ((unsigned int *) &data_ov004_02252b28);
    func_ov004_02210cf0(self);
    func_ov004_02211518(self);
    return self;
}

int func_ov004_02211ed4(char *self)
{
    int v;

    func_ov004_0221041c(self, 0, 1, 0x1000, 0);
    v = func_ov004_0223a760(func_ov004_0220fde0(self));
    switch (v) {
        case 0x3f9:
            *(u8 *) (self + 0x848) = 4;
            *(u16 *) (self + 0x844) = *(u8 *) (self + 0x848);
            break;
        case 0x3fb:
            *(u8 *) (self + 0x848) = 4;
            *(u16 *) (self + 0x844) = *(u8 *) (self + 0x848);
            break;
        case 0x3fa:
            *(u8 *) (self + 0x848) = 4;
            *(u16 *) (self + 0x844) = *(u8 *) (self + 0x848);
            break;
        case 0x3fc:
            *(u8 *) (self + 0x848) = 2;
            *(u16 *) (self + 0x844) = *(u8 *) (self + 0x848);
            break;
        default:
            *(u8 *) (self + 0x848) = 1;
            *(u16 *) (self + 0x844) = *(u8 *) (self + 0x848);
            break;
    }
    *(u8 *) (self + 0x849) = 0;
    *(u16 *) (self + 0x846) = 0;
    if (*(int *) (self + 0x76c) != 1) {
        if (v == 0x3fc) {
            *(u16 *) (self + 0x846) = func_020644cc(0x3c);
        } else if ((u16) (v + 0xfc07) <= 2) {
            *(u16 *) (self + 0x846) = func_020644cc(0xc8);
        } else {
            *(u16 *) (self + 0x846) = func_020644cc(func_ov004_0221062c(self, 0) * *(u16 *) (self + 0x844));
        }
    }
    return 1;
}
