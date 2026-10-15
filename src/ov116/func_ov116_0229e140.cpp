/* func_ov116_0229e140 @ 0x0229e140, 0x28 bytes, Thumb, module ov116
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov116_0229e8b819func_ov116_0229e140Ev
 */

#include "cpp/ov116/Obj_ov116_0229e8b8.h"

extern "C" int func_ov002_02209f64(void *);
extern "C" unsigned char *func_ov002_02208098(void *, unsigned char);

void Obj_ov116_0229e8b8::func_ov116_0229e140()
{
    void *self = (void *) this;
    if (func_ov002_02209f64((char *) self + 0x94) == 0) {
        func_ov002_02208098(self, *(unsigned char *) ((char *) self + 0x142c));
        ((Obj_ov116_0229e8b8 *) self)->func_ov116_0229e5e8();
    }
}
