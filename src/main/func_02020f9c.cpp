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

extern "C" void func_02020f9c(Base_02020f9c *self, UnkStruct_02020f9c *out)
{
    static int (Base_02020f9c::*table[14])() = {
        &Base_02020f9c::func_02022c2c, &Base_02020f9c::func_02022674, &Base_02020f9c::func_0202261c,
        &Base_02020f9c::func_020224c4, &Base_02020f9c::func_02022454, &Base_02020f9c::func_020222dc,
        &Base_02020f9c::func_0202213c, &Base_02020f9c::func_02022034, &Base_02020f9c::func_02021fb8,
        &Base_02020f9c::func_02021f1c, &Base_02020f9c::func_0202179c, &Base_02020f9c::func_020214e0,
        &Base_02020f9c::func_02021410, &Base_02020f9c::func_02021284};
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
        result = (self->*table[idx])();
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
