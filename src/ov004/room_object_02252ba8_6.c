/* room_object_02252ba8_6: 4 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_022154e8 @ 0x022154e8, 0x1c bytes, Thumb
 * func_ov004_022154b8 @ 0x022154b8, 0x30 bytes, Thumb
 * func_ov004_02215494 @ 0x02215494, 0x24 bytes, Thumb
 * func_ov004_02215468 @ 0x02215468, 0x2c bytes, Thumb
 */

#include "types.h"

typedef struct {
    int *unk_00;
    char pad_04[0xe8];
    int *unk_EC;
} UnkStruct_02215494;

typedef struct {
    unsigned int unk_00;
    unsigned char pad_04[0xe8];
    unsigned int unk_EC;
} UnkStruct_02215468;

extern int func_ov004_0221152c(unsigned int size);
extern void *func_ov004_022110e4(void *);
extern void *data_ov004_02252ba8;
extern void *data_ov004_02252c54;
extern void *func_ov004_02210cf0(void *);
extern void func_ov004_02211518(void *self);

void *func_ov004_022154b8(char *self);

void func_ov004_022154e8(void)
{
    char *conditionInput0;

    if ((conditionInput0 = (char *) (func_ov004_0221152c(0x864)))) {
        func_ov004_022154b8((char *) conditionInput0);
    }
}

void *func_ov004_022154b8(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_022110e4(self);
    *(void **) (self) = &data_ov004_02252ba8;
    *(void **) (self + 0xec) = &data_ov004_02252c54;
    *(u8 *) (self + 0x77c) = 0xff;
    return self;
}

void *func_ov004_02215494(UnkStruct_02215494 *obj)
{
    obj->unk_00 = ((int *) &data_ov004_02252ba8);
    obj->unk_EC = ((int *) &data_ov004_02252c54);
    func_ov004_02210cf0(obj);
    return obj;
}

UnkStruct_02215468 *func_ov004_02215468(UnkStruct_02215468 *self)
{
    self->unk_00 = (unsigned int) ((unsigned int *) &data_ov004_02252ba8);
    self->unk_EC = (unsigned int) ((unsigned int *) &data_ov004_02252c54);
    func_ov004_02210cf0(self);
    func_ov004_02211518(self);
    return self;
}
