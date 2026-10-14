/* func_ov126_022a0e98 @ 0x022a0e98, 0x2c bytes, Thumb, module ov126
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov126_022a20c819func_ov126_022a0e98Ev
 */

#include "cpp/ov126/Obj_ov126_022a20c8.h"

extern "C" int func_ov002_02208098(int, unsigned char);
extern "C" int func_ov002_02209f64(int);

int Obj_ov126_022a20c8::func_ov126_022a0e98()
{
    int r0 = (int) this;
    if (func_ov002_02209f64(r0 + 0x3f90) == 0) {
        func_ov002_02208098(r0, *(unsigned char *) (r0 + 0xae));
        ((Obj_ov126_022a20c8 *) r0)->func_ov126_022a1b4c();
    }
}
