/* func_ov096_022a1d98 @ 0x022a1d98, 0xf4 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov096_022a23e819func_ov096_022a1d98Ev
 */

#include "cpp/ov096/Obj_ov096_022a23e8.h"

typedef void (Obj_ov096_022a23e8::*PMF)();

int Obj_ov096_022a23e8::func_ov096_022a1d98()
{
    static PMF table[11] = {&Obj_ov096_022a23e8::func_ov096_022a18a0, &Obj_ov096_022a23e8::func_ov096_022a186c,
                            &Obj_ov096_022a23e8::func_ov096_022a1838, &Obj_ov096_022a23e8::func_ov096_022a17cc,
                            &Obj_ov096_022a23e8::func_ov096_022a1794, &Obj_ov096_022a23e8::func_ov096_022a1744,
                            &Obj_ov096_022a23e8::func_ov096_022a16e4, &Obj_ov096_022a23e8::func_ov096_022a1660,
                            &Obj_ov096_022a23e8::func_ov096_022a1610, &Obj_ov096_022a23e8::func_ov096_022a15d4,
                            &Obj_ov096_022a23e8::func_ov096_022a1554};

    func_ov096_022a13f0();
    (this->*table[state])();
    func_ov096_022a13b4();

    return 1;
}
