/* func_ov131_0229b24c @ 0x0229b24c, 0x28 bytes, Thumb, module ov131
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov131_0229b8f019func_ov131_0229b24cEv
 */

#include "cpp/ov131/Obj_ov131_0229b8f0.h"

extern "C" int func_ov002_02209f64(void *self);
extern "C" unsigned char *func_ov002_02208098(void *object, unsigned char value);

void Obj_ov131_0229b8f0::func_ov131_0229b24c()
{
    void *self = (void *) this;
    if (func_ov002_02209f64((char *) self + 0x94) == 0) {
        func_ov002_02208098((void *) (self), *(unsigned char *) ((char *) self + 0x1556));
        ((Obj_ov131_0229b8f0 *) self)->func_ov131_0229b644();
    }
}
