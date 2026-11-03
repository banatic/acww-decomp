/* room_object_02252374_4: 4 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02214110 @ 0x02214110, 0x1c bytes, Thumb
 * func_ov004_022140c0 @ 0x022140c0, 0x50 bytes, Thumb
 * func_ov004_0221409c @ 0x0221409c, 0x24 bytes, Thumb
 * func_ov004_02214070 @ 0x02214070, 0x2c bytes, Thumb
 */

#include "types.h"

typedef struct {
    int *unk_00;
    char pad_04[0xe8];
    int *unk_EC;
} UnkStruct_0221409c;

typedef struct {
    unsigned int unk_00;
    unsigned char pad_04[0xe8];
    unsigned int unk_EC;
} UnkStruct_02214070;

extern int func_ov004_0221152c(unsigned int size);
extern void *func_020b9e58(void *);
extern void *func_ov004_022110e4(void *);
extern void *data_ov004_02252374;
extern void *data_ov004_02252420;
extern void *func_ov004_02210cf0(void *);
extern void func_ov004_02211518(void *self);

void *func_ov004_022140c0(char *self);

void func_ov004_02214110(void)
{
    char *conditionInput0;

    if ((conditionInput0 = (char *) (func_ov004_0221152c(0x878)))) {
        func_ov004_022140c0((char *) conditionInput0);
    }
}

void *func_ov004_022140c0(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_022110e4(self);
    *(void **) (self) = &data_ov004_02252374;
    *(void **) (self + 0xec) = &data_ov004_02252420;
    func_020b9e58(self + 0x848);
    *(void **) (self + 0x844) = 0x0;
    *(u8 *) (self + 0x871) = 0x0;
    *(u8 *) (self + 0x870) = *(u8 *) (self + 0x871);
    return self;
}

void *func_ov004_0221409c(UnkStruct_0221409c *obj)
{
    obj->unk_00 = ((int *) &data_ov004_02252374);
    obj->unk_EC = ((int *) &data_ov004_02252420);
    func_ov004_02210cf0(obj);
    return obj;
}

UnkStruct_02214070 *func_ov004_02214070(UnkStruct_02214070 *self)
{
    self->unk_00 = (unsigned int) ((unsigned int *) &data_ov004_02252374);
    self->unk_EC = (unsigned int) ((unsigned int *) &data_ov004_02252420);
    func_ov004_02210cf0(self);
    func_ov004_02211518(self);
    return self;
}
