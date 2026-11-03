/* wfc_host_list_4: 2 functions, module ov146
 * mwccarm 1.2/base -O4,s
 * func_ov146_0229af2c @ 0x0229af2c, 0xd8 bytes, Thumb, emits _ZN18Obj_ov146_0229b68019func_ov146_0229af2cEv
 * func_ov146_0229af10 @ 0x0229af10, 0x1c bytes, Thumb, emits _ZN18Obj_ov146_0229b68019func_ov146_0229af10Ev
 */

#include "cpp/ov146/Obj_ov146_0229b680.h"

typedef void (Obj_ov146_0229b680::*PMF)();

extern "C" void func_ov146_0229accc(void *p);
extern "C" void func_ov146_0229acc4(void *p);

void Obj_ov146_0229b680::func_ov146_0229af2c()
{
    static PMF tbl[10] = {&Obj_ov146_0229b680::func_ov146_0229a9b8, &Obj_ov146_0229b680::func_ov146_0229a984,
                          &Obj_ov146_0229b680::func_ov146_0229a950, &Obj_ov146_0229b680::func_ov146_0229a8ec,
                          &Obj_ov146_0229b680::func_ov146_0229a89c, &Obj_ov146_0229b680::func_ov146_0229a858,
                          &Obj_ov146_0229b680::func_ov146_0229a82c, &Obj_ov146_0229b680::func_ov146_0229a7f4,
                          &Obj_ov146_0229b680::func_ov146_0229a7a4, &Obj_ov146_0229b680::func_ov146_0229a778};
    (this->*tbl[subState])();
}

int Obj_ov146_0229b680::func_ov146_0229af10()
{
    void *p = (void *) this;
    func_ov146_0229accc(p);
    ((Obj_ov146_0229b680 *) p)->func_ov146_0229af2c();
    func_ov146_0229acc4(p);
    return 1;
}
