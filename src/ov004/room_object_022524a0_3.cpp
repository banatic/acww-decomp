/* room_object_022524a0_3: 2 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_022143b8 @ 0x022143b8, 0x2c bytes, Thumb
 * func_ov004_022143a8 @ 0x022143a8, 0x10 bytes, Thumb, emits _ZN18Obj_ov004_022524a019func_ov004_022143a8Ev
 */

#include "cpp/ov004/Obj_ov004_022524a0.h"

class UnkStruct_022143b8 {
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
    virtual void v28(int a, int b);
};

extern "C" void func_ov004_0221041c(UnkStruct_022143b8 *self, int a, int b, int c, int d);

extern "C" int func_ov004_022143b8(UnkStruct_022143b8 *self)
{
    func_ov004_0221041c(self, 0, 1, 0x1000, 0);
    self->v28(0, 0xff);
    return 1;
}

int Obj_ov004_022524a0::func_ov004_022143a8()
{
    func_ov004_022141f0();
    return 1;
}
