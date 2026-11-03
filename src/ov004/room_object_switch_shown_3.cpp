/* room_object_switch_shown_3: 2 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_022125b0 @ 0x022125b0, 0x70 bytes, Thumb
 * func_ov004_022125a0 @ 0x022125a0, 0x10 bytes, Thumb, emits _ZN18Obj_ov004_02250ad819func_ov004_022125a0Ev
 */

#include "types.h"
#include "cpp/ov004/Obj_ov004_02250ad8.h"

class UnkStruct_022125b0 {
  public:
    virtual void v00() = 0;
    virtual void v01() = 0;
    virtual void v02() = 0;
    virtual void v03() = 0;
    virtual void v04() = 0;
    virtual void v05() = 0;
    virtual void v06() = 0;
    virtual void v07() = 0;
    virtual void v08() = 0;
    virtual void v09() = 0;
    virtual void v10() = 0;
    virtual void v11() = 0;
    virtual void v12() = 0;
    virtual void v13() = 0;
    virtual void v14() = 0;
    virtual void v15() = 0;
    virtual void v16() = 0;
    virtual void v17() = 0;
    virtual void v18() = 0;
    virtual void v19() = 0;
    virtual void v20() = 0;
    virtual void v21() = 0;
    virtual void v22() = 0;
    virtual void v23() = 0;
    virtual void v24() = 0;
    virtual void v25() = 0;
    virtual void v26() = 0;
    virtual void v27() = 0;
    virtual void v28(int, int) = 0;
};

extern "C" {
void *func_ov004_0220fde0(void *self);
int func_0204bc50(void *p, int a);
int func_ov004_0220d2b8(void *p);
}

extern "C" int func_ov004_022125b0(char *self)
{
    volatile u16 v;
    int m;
    u16 t;

    v = (u16) func_0204bc50(func_ov004_0220fde0(self), 0);
    m = 0;
    t = v;
    if (t >= 0x4124 && t <= 0x4223) {
        m = 1;
    }
    if (m != 0) {
        *(u8 *) (self + 0x845) = 1;
    }
    if (func_ov004_0220d2b8(self + 0x740) != 0) {
        ((UnkStruct_022125b0 *) self)->v28(1, 0xff);
    } else {
        ((UnkStruct_022125b0 *) self)->v28(0, 0xff);
    }
    return 1;
}

int Obj_ov004_02250ad8::func_ov004_022125a0()
{
    func_ov004_0221244c();
    return 1;
}
