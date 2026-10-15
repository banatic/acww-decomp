/* func_ov122_022a0ad0 @ 0x022a0ad0, 0x2c bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov122_022a273819func_ov122_022a0ad0Ev
 */

#include "cpp/ov122/Obj_ov122_022a2738.h"

extern "C" int func_ov002_02209f64(void *);
extern "C" unsigned char *func_ov002_02208098(void *object, unsigned char value);

void Obj_ov122_022a2738::func_ov122_022a0ad0()
{
    void *self = (void *) this;
    if (func_ov002_02209f64((char *) self + 0x4058) == 0) {
        func_ov002_02208098((void *) (self), *(unsigned char *) ((char *) self + 0xb4));
        ((Obj_ov122_022a2738 *) self)->func_ov122_022a1f40();
    }
}
