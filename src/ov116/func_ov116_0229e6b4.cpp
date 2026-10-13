/* func_ov116_0229e6b4 @ 0x0229e6b4, 0x94 bytes, Thumb, module ov116
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov116_0229e8b819func_ov116_0229e6b4Ev
 */

#include "cpp/ov116/Obj_ov116_0229e8b8.h"

typedef Obj_ov116_0229e8b8 S;
typedef void (S::*PMF)();

extern "C" void func_ov116_0229e334(void *obj);
extern "C" void func_ov116_0229e328(void *obj);

int Obj_ov116_0229e8b8::func_ov116_0229e6b4()
{
    static PMF arr[4] = {&S::func_ov116_0229e47c, &S::func_ov116_0229e454, &S::func_ov116_0229e41c, &S::func_ov116_0229e3e4};
    func_ov116_0229e334(this);
    (this->*arr[state])();
    func_ov116_0229e328(this);
    return 1;
}
