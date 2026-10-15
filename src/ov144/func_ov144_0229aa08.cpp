/* func_ov144_0229aa08 @ 0x0229aa08, 0x26 bytes, Thumb, module ov144
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov144_0229b3f819func_ov144_0229aa08Ev
 */

#include "cpp/ov144/Obj_ov144_0229b3f8.h"

extern "C" int func_ov002_02209f64(void *ptr);
extern "C" unsigned char *func_ov002_02208098(void *ptr, unsigned char byte);

void Obj_ov144_0229b3f8::func_ov144_0229aa08()
{
    unsigned char *ptr = (unsigned char *) this;
    unsigned char *p = ptr;

    if (func_ov002_02209f64(ptr + 0xc4) == 0) {
        p += 0xbe;
        func_ov002_02208098(ptr, *p);
        ((Obj_ov144_0229b3f8 *) ptr)->func_ov144_0229b02c();
    }
}
