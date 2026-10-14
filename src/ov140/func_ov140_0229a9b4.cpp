/* func_ov140_0229a9b4 @ 0x0229a9b4, 0x30 bytes, Thumb, module ov140
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov140_0229b40419func_ov140_0229a9b4Ev
 */

#include "cpp/ov140/Obj_ov140_0229b404.h"

extern "C" int func_ov002_02209f64(void *);
extern "C" int func_ov002_02208098(void *, unsigned char);

void Obj_ov140_0229b404::func_ov140_0229a9b4()
{
    void *self = (void *) this;
    if (func_ov002_02209f64((char *) self + 0x128c) == 0) {
        func_ov002_02208098(self, *(unsigned char *) ((char *) self + 0x8ae));
        ((Obj_ov140_0229b404 *) self)->func_ov140_0229aedc();
    }
}
