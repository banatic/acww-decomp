/* func_ov009_022650d0 @ 0x022650d0, 0x74 bytes, Thumb, module ov009
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct Vec {
    int a;
    int b;
};
struct UnkStruct_022650d0 {
    u8 pad[4];
};

class UnkStruct_022650d0_2 {
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
    virtual void v26();
    virtual void v27();
    virtual void v28();
    virtual void v29();
    virtual void v30();
    virtual void v31();
    virtual void v32();
    virtual void v33();
    virtual void v34();
    virtual void v35();
    virtual void v36();
    virtual void v37();
    virtual void v38();
    virtual void v39();
    virtual void v40();
    virtual void v41();
    virtual void v42();
    virtual void v43();
    virtual void v44();
    virtual Vec v45();
    u8 pad[0x235 - 4];
    u8 flags;
    u8 pad_236[2];
    UnkStruct_022650d0 sub;
};

extern "C" u16 *func_ov009_02262fcc(UnkStruct_022650d0_2 *self);
extern "C" void func_ov009_02262f2c(UnkStruct_022650d0 *dst, const Vec *v, u16 x);
extern "C" void func_02003420(UnkStruct_022650d0_2 *self, void *p);

extern "C" void func_ov009_022650d0(UnkStruct_022650d0_2 *self, void *arg)
{
    const Vec &v = self->v45();
    func_ov009_02262f2c(&self->sub, &v, *func_ov009_02262fcc(self));
    if (self->flags & 2) {
        self->flags |= 8;
    } else {
        self->flags &= ~8;
    }
    self->flags &= ~2;
    self->flags &= ~4;
    func_02003420(self, arg);
}
