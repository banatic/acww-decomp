/* func_ov088_02278a8c @ 0x02278a8c, 0x50 bytes, Thumb, module ov088
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02278a8c_2 {
    virtual void f0() {}
    virtual void f1() {}
    virtual void Method() {}
};

struct UnkStruct_02278a8c {
    u8 pad_00[0x658];
    UnkStruct_02278a8c_2 sub;
};

extern "C" int func_0201c2a4(void *obj, int x);
extern "C" void func_02016108(UnkStruct_02278a8c_2 *sub, int x);
extern "C" void func_ov088_02279784(UnkStruct_02278a8c *obj, int x);

extern "C" void func_ov088_02278a8c(UnkStruct_02278a8c *obj, int mode)
{
    switch (mode) {
        case 0:
            func_ov088_02279784(obj, 0);
            break;
        case 3:
            obj->sub.Method();
            {
                int ret = func_0201c2a4(obj, 4);
                func_02016108(&obj->sub, ret);
            }
            func_ov088_02279784(obj, 4);
            break;
        case 8:
            func_ov088_02279784(obj, 2);
            break;
    }
}
