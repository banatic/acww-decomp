/* func_ov128_0229bedc @ 0x0229bedc, 0x30 bytes, Thumb, module ov128
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov128_0229cbc019func_ov128_0229bedcEv
 */

#include "cpp/ov128/Obj_ov128_0229cbc0.h"

extern "C" int func_ov002_02209f64(void *);
extern "C" void func_ov002_02208098(void *, unsigned char);

void Obj_ov128_0229cbc0::func_ov128_0229bedc()
{
    void *param = (void *) this;
    if (func_ov002_02209f64((char *) param + 0x110) == 0) {
        func_ov002_02208098(param, *(unsigned char *) ((char *) param + 0x2d6a));
        ((Obj_ov128_0229cbc0 *) param)->func_ov128_0229c618();
    }
}
