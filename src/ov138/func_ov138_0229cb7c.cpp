/* func_ov138_0229cb7c @ 0x0229cb7c, 0x26 bytes, Thumb, module ov138
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov138_0229d4e019func_ov138_0229cb7cEv
 */

#include "cpp/ov138/Obj_ov138_0229d4e0.h"

extern "C" int func_ov002_02209f64(void *);
extern "C" unsigned char *func_ov002_02208098(void *object, unsigned char value);

void Obj_ov138_0229d4e0::func_ov138_0229cb7c()
{
    void *self = (void *) this;
    if (func_ov002_02209f64((char *) self + 0x98) == 0) {
        func_ov002_02208098((void *) (self), *(unsigned char *) ((char *) self + 0x94));
        ((Obj_ov138_0229d4e0 *) self)->func_ov138_0229d16c();
    }
}
