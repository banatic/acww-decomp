/* func_ov145_0229a430 @ 0x0229a430, 0x26 bytes, Thumb, module ov145
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov145_0229ae0019func_ov145_0229a430Ev
 */

#include "cpp/ov145/Obj_ov145_0229ae00.h"

extern "C" int func_ov002_02209f64(void *);
extern "C" unsigned char *func_ov002_02208098(void *object, unsigned char value);

void Obj_ov145_0229ae00::func_ov145_0229a430()
{
    void *self = (void *) this;
    if (func_ov002_02209f64((char *) self + 0xc8) == 0) {
        func_ov002_02208098((void *) (self), *(unsigned char *) ((char *) self + 0xc3));
        ((Obj_ov145_0229ae00 *) self)->func_ov145_0229aa64();
    }
}
