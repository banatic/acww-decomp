/* obj_020d8c64: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020120e0 @ 0x020120e0, 0xc8 bytes, Thumb
 * func_02012014 @ 0x02012014, 0xcc bytes, Thumb
 */

#include "types.h"

struct UnkStruct_020120e0 {
    u8 pad_00[0x514];
    void *unk_514;
};

extern u8 data_020d8c64[];
extern u8 data_020d8414[];
extern void func_02014898(void *p);
extern void func_02019eac(void *p);
extern void func_02013c28(void *p);
extern void func_020f5914(void *p);
extern void *func_02089c70(void *p);
extern void *func_02032c50(void *p);
extern void func_0201a790(void *p);
extern void func_0201a7e8(void *p);
extern void func_0201ade4(void *p);
extern void func_0201b320(void *p);
extern int func_02016998(void *p);
extern void *func_0201a3f8(void *p);
extern void func_0201b390(void *p);
extern void *func_02054630(void *p);
extern void *func_0203f080(void *p);
extern void func_020edf54(void *);

void *func_020120e0(void *thisArg)
{
    struct UnkStruct_020120e0 *self = (struct UnkStruct_020120e0 *) thisArg;

    *(void **) self = data_020d8c64;

    func_02014898((u8 *) self + 0x618);
    func_02019eac((u8 *) self + 0x564);
    func_02013c28((u8 *) self + 0x558);
    self->unk_514 = data_020d8414;
    func_020f5914((u8 *) self + 0x514);
    func_02089c70((u8 *) self + 0x4cc);
    func_02032c50((u8 *) self + 0x49c);
    func_0201a790((u8 *) self + 0x420);
    func_0201a7e8((u8 *) self + 0x418);
    func_0201ade4((u8 *) self + 0x3b0);
    func_0201b320((u8 *) self + 0x350);
    func_02016998((u8 *) self + 0x334);
    func_0201a3f8((u8 *) self + 0x2ac);
    func_0201b390((u8 *) self + 0x2a0);
    func_02054630((u8 *) self + 0xec);
    func_0203f080(self);

    return self;
}

void *func_02012014(void *a0)
{
    unsigned char *self = (unsigned char *) a0;
    *(int *) self = (int) ((int *) data_020d8c64);
    func_02014898(self + 0x618);
    func_02019eac(self + 0x564);
    func_02013c28(self + 0x558);
    *(int *) (self + 0x514) = (int) ((int *) data_020d8414);
    func_020f5914(self + 0x514);
    func_02089c70(self + 0x4cc);
    func_02032c50(self + 0x49c);
    func_0201a790(self + 0x420);
    func_0201a7e8(self + 0x418);
    func_0201ade4(self + 0x3b0);
    func_0201b320(self + 0x350);
    func_02016998(self + 0x334);
    func_0201a3f8(self + 0x2ac);
    func_0201b390(self + 0x2a0);
    func_02054630(self + 0xec);
    func_0203f080(self);
    func_020edf54(self);
    return self;
}
