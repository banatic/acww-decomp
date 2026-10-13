/* func_020120e0 @ 0x020120e0, 0xc8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern u8 data_020d8c64[];
extern u8 data_020d8414[];

extern void func_02014898(void *p);
extern void func_02019eac(void *p);
extern void func_02013c28(void *p);
extern void func_020f5914(void *p);
extern void func_02089c70(void *p);
extern void func_02032c50(void *p);
extern void func_0201a790(void *p);
extern void func_0201a7e8(void *p);
extern void func_0201ade4(void *p);
extern void func_0201b320(void *p);
extern void func_02016998(void *p);
extern void func_0201a3f8(void *p);
extern void func_0201b390(void *p);
extern void func_02054630(void *p);
extern void func_0203f080(void *p);

struct UnkStruct_020120e0 {
    u8 pad_00[0x514];
    void *unk_514;
};

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
