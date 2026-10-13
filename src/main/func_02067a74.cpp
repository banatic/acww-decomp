/* func_02067a74 @ 0x02067a74, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

class UnkStruct_02067a74 {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual int m();
};

struct UnkStruct_02067a74_2 {
    u8 pad_00[0x14a8];
    UnkStruct_02067a74 *sub;
    u8 pad_14AC[0x1c70 - 0x14ac];
    u8 obj;
};

extern "C" void func_020a8c1c(void *p);
extern "C" void func_02080af0(int arg1, void *arg2, int arg3);

extern "C" int func_02067a74(UnkStruct_02067a74_2 *self)
{
    int ret = self->sub->m();
    int result = 0;
    func_020a8c1c(&self->obj);
    if (ret != 0) {
        func_02080af0(ret, &self->obj, 1);
        result = 1;
    }
    return result;
}
