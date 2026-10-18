/* func_02020f9c @ 0x02020f9c, 0x17c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02020f9c {
    void *ptr;
    unsigned char flag;
};

#include "cpp/main/Base_02020f9c.h"

extern char data_021c1d34[14];
extern int data_020c8ea4;
extern "C" void MI_CpuCopy8(int *, char *, int);
extern "C" int func_02021118(Base_02020f9c *);
extern "C" int func_02021168(Base_02020f9c *);
extern "C" int func_020211dc(Base_02020f9c *);
extern "C" int func_0202114c(Base_02020f9c *, char *, int);
extern "C" int func_02022454(Base_02020f9c *);

extern int data_021c1cf8;
extern int (Base_02020f9c::*data_020d8fe0)();
extern int (Base_02020f9c::*data_020d8fe8)();
extern int (Base_02020f9c::*data_020d8ff8)();
extern int (Base_02020f9c::*data_020d9008)();
extern int (Base_02020f9c::*data_020d9020)();
extern int (Base_02020f9c::*data_020d9030)();
extern int (Base_02020f9c::*data_020d9040)();
extern int (Base_02020f9c::*data_020d9360)();
extern int (Base_02020f9c::*data_020d9368)();
extern int (Base_02020f9c::*data_020d93d0)();
extern int (Base_02020f9c::*data_020d9408)();
extern int (Base_02020f9c::*data_020d9440)();
extern int (Base_02020f9c::*data_020d9450)();
extern int (Base_02020f9c::*data_020d9468)();
extern int (Base_02020f9c::*data_021c20a4[14])();

extern "C" void func_02020f9c(Base_02020f9c *self, UnkStruct_02020f9c *out)
{
    if (!(data_021c1cf8 & 1)) {
        data_021c20a4[0] = data_020d9468;
        data_021c20a4[1] = data_020d9040;
        data_021c20a4[2] = data_020d9450;
        data_021c20a4[3] = data_020d9440;
        data_021c20a4[4] = data_020d9030;
        data_021c20a4[5] = data_020d9020;
        data_021c20a4[6] = data_020d9408;
        data_021c20a4[7] = data_020d9008;
        data_021c20a4[8] = data_020d93d0;
        data_021c20a4[9] = data_020d8ff8;
        data_021c20a4[10] = data_020d8fe8;
        data_021c20a4[11] = data_020d8fe0;
        data_021c20a4[12] = data_020d9368;
        data_021c20a4[13] = data_020d9360;
        data_021c1cf8 |= 1;
    }
    int result;
    int idx;

    MI_CpuCopy8(&data_020c8ea4, data_021c1d34, 14);
    func_02021118(self);
    result = func_02021168(self);
    if (result == 0) {
        result = func_020211dc(self);
    }
    while (result == 0) {
        idx = func_0202114c(self, data_021c1d34, 14);
        if (idx < 0) {
            goto special;
        }
        if (idx >= 14) {
            goto special;
        }
        result = (self->*data_021c20a4[idx])();
        if (result == 0) {
            data_021c1d34[idx] = 0;
        }
        continue;
    special:
        func_02022454(self);
        break;
    }

    out->ptr = &self->unk_104;
    out->flag = self->unk_122;
}
