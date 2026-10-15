/* func_ov103_0229d2d0 @ 0x0229d2d0, 0x28 bytes, Thumb, module ov103
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov103_0229e2e019func_ov103_0229d2d0Ev
 */

#include "cpp/ov103/Obj_ov103_0229e2e0.h"

extern "C" int func_0208e484(void *);
extern "C" unsigned char *func_ov002_02208098(void *, unsigned char value);

void Obj_ov103_0229e2e0::func_ov103_0229d2d0()
{
    void *arg0 = (void *) this;
    if (func_0208e484((char *) arg0 + 0x2274)) {
        ((Obj_ov103_0229e2e0 *) arg0)->func_ov103_0229c680();
        func_ov002_02208098(arg0, 5);
    }
}
