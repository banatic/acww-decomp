/* room_object_animated: 7 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02211660 @ 0x02211660, 0x1c bytes, Thumb
 * func_ov004_0221163c @ 0x0221163c, 0x24 bytes, Thumb
 * func_ov004_02211618 @ 0x02211618, 0x24 bytes, Thumb
 * func_ov004_022115ec @ 0x022115ec, 0x2c bytes, Thumb
 * func_ov004_022115b4 @ 0x022115b4, 0x38 bytes, Thumb
 * func_ov004_022115b0 @ 0x022115b0, 0x4 bytes, Thumb
 * func_ov004_022115ac @ 0x022115ac, 0x4 bytes, Thumb
 */

#include "types.h"

typedef struct {
    int *unk_00;
    char pad_04[0xe8];
    int *unk_EC;
} UnkStruct_02211618;

typedef struct {
    unsigned int unk_00;
    unsigned char pad_04[0xe8];
    unsigned int unk_EC;
} UnkStruct_022115ec;

extern int func_ov004_0221152c(unsigned int size);
extern void *func_ov004_022110e4(void *);
extern char data_ov004_022526f8;
extern char data_ov004_022527a4;
extern void *func_ov004_02210cf0(void *);
extern void func_ov004_02211518(void *self);
extern int func_02062b14(void);
extern void func_ov004_0221041c(void *self, int a, int b, int c, u16 d);
extern int func_ov004_0220ffbc(void *self);

void *func_ov004_0221163c(void *this);

void func_ov004_02211660(void)
{
    void *conditionInput0;

    if ((conditionInput0 = (void *) (func_ov004_0221152c(0x848)))) {
        func_ov004_0221163c((void *) conditionInput0);
    }
}

void *func_ov004_0221163c(void *this)
{
    func_ov004_022110e4(this);
    *(void **) this = &data_ov004_022526f8;
    *(void **) ((char *) this + 0xec) = &data_ov004_022527a4;
    return this;
}

void *func_ov004_02211618(UnkStruct_02211618 *obj)
{
    obj->unk_00 = ((int *) &data_ov004_022526f8);
    obj->unk_EC = ((int *) &data_ov004_022527a4);
    func_ov004_02210cf0(obj);
    return obj;
}

UnkStruct_022115ec *func_ov004_022115ec(UnkStruct_022115ec *self)
{
    self->unk_00 = (unsigned int) ((unsigned int *) &data_ov004_022526f8);
    self->unk_EC = (unsigned int) ((unsigned int *) &data_ov004_022527a4);
    func_ov004_02210cf0(self);
    func_ov004_02211518(self);
    return self;
}

int func_ov004_022115b4(char *self)
{
    int *p = (int *) (self + 0x844);

    *p = func_02062b14();
    func_ov004_0221041c(self, 0, 0, 0, (u16) *p);
    func_ov004_0220ffbc(self);
    return 1;
}

int func_ov004_022115b0(void)
{
    return 1;
}

int func_ov004_022115ac(void)
{
    return 1;
}
