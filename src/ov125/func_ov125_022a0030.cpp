/* func_ov125_022a0030 @ 0x022a0030, 0x30 bytes, Thumb, module ov125
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov125_022a0ab819func_ov125_022a0030Ev
 */

#include "cpp/ov125/Obj_ov125_022a0ab8.h"

extern "C" int func_ov002_02209f64(void *);
extern "C" int func_ov002_02208098(void *, unsigned char);

void Obj_ov125_022a0ab8::func_ov125_022a0030()
{
    void *self = (void *) this;
    if (func_ov002_02209f64((char *) self + 0x644) == 0) {
        func_ov002_02208098(self, *(unsigned char *) ((char *) self + 0x87f));
        ((Obj_ov125_022a0ab8 *) self)->func_ov125_022a0714();
    }
}
