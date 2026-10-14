/* func_ov121_0229b3e0 @ 0x0229b3e0, 0x2c bytes, Thumb, module ov121
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov121_0229c3a819func_ov121_0229b3e0Ev
 */

#include "cpp/ov121/Obj_ov121_0229c3a8.h"

extern "C" int func_ov002_02209f64(void *);
extern "C" int func_ov002_02208098(void *, unsigned char);

void Obj_ov121_0229c3a8::func_ov121_0229b3e0()
{
    void *self = (void *) this;
    if (!func_ov002_02209f64((char *) self + 0x3a8)) {
        func_ov002_02208098(self, *(unsigned char *) ((char *) self + 0xb4));
        ((Obj_ov121_0229c3a8 *) self)->func_ov121_0229bdc0();
    }
}
