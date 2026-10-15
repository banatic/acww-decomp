/* func_ov143_0229a5a4 @ 0x0229a5a4, 0x26 bytes, Thumb, module ov143
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov143_0229b1c019func_ov143_0229a5a4Ev
 */

#include "cpp/ov143/Obj_ov143_0229b1c0.h"

extern "C" int func_ov002_02209f64(void *);
extern "C" unsigned char *func_ov002_02208098(void *, unsigned char);

void Obj_ov143_0229b1c0::func_ov143_0229a5a4()
{
    void *self = (void *) this;
    if (func_ov002_02209f64((char *) self + 0xac) == 0) {
        func_ov002_02208098(self, *(unsigned char *) ((char *) self + 0x9e));
        ((Obj_ov143_0229b1c0 *) self)->func_ov143_0229ac10();
    }
}
