/* func_ov143_0229acf8 @ 0x0229acf8, 0xcc bytes, Thumb, module ov143
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov143_0229b1c019func_ov143_0229acf8Ev
 */

#include "cpp/ov143/Obj_ov143_0229b1c0.h"

typedef int (Obj_ov143_0229b1c0::*PMF)();

extern "C" int func_ov143_0229a91c(void *);
extern "C" int func_ov143_0229a914(void *);

int Obj_ov143_0229b1c0::func_ov143_0229acf8()
{
    static PMF table[8] = {&Obj_ov143_0229b1c0::func_ov143_0229ab68, &Obj_ov143_0229b1c0::func_ov143_0229ab40,
                           &Obj_ov143_0229b1c0::func_ov143_0229ab08, &Obj_ov143_0229b1c0::func_ov143_0229aad8,
                           &Obj_ov143_0229b1c0::func_ov143_0229aa70, &Obj_ov143_0229b1c0::func_ov143_0229aa4c,
                           &Obj_ov143_0229b1c0::func_ov143_0229aa18, &Obj_ov143_0229b1c0::func_ov143_0229a9f4};
    func_ov143_0229a91c(this);
    {
        int idx = state;
        (this->*table[idx])();
    }
    func_ov143_0229a914(this);
    return 1;
}
