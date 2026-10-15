/* func_ov146_0229a82c @ 0x0229a82c, 0x2c bytes, Thumb, module ov146
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov146_0229b68019func_ov146_0229a82cEv
 */

#include "cpp/ov146/Obj_ov146_0229b680.h"

extern "C" int func_ov002_02209f64(void *);
extern "C" unsigned char *func_ov002_02208098(void *, unsigned char);

void Obj_ov146_0229b680::func_ov146_0229a82c()
{
    void *self = (void *) this;
    if (func_ov002_02209f64((char *) self + 0x15cc) != 0) {
        return;
    }
    func_ov002_02208098(self, ((unsigned char *) self)[0xb3]);
    ((Obj_ov146_0229b680 *) self)->func_ov146_0229af2c();
}
