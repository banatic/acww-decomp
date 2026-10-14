/* func_ov119_0229c730 @ 0x0229c730, 0x2a bytes, Thumb, module ov119
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov119_0229cea019func_ov119_0229c730Ev
 */

#include "cpp/ov119/Obj_ov119_0229cea0.h"

extern "C" int func_ov119_0229c648(void);
extern "C" int func_ov119_0229c2e4(int);
extern "C" int func_ov119_0229c2dc(int);

int Obj_ov119_0229cea0::func_ov119_0229c730()
{
    int r0 = (int) this;
    int r4 = r0;
    if (func_ov119_0229c648() != 0) {
        return 1;
    }
    func_ov119_0229c2e4(r4);
    ((Obj_ov119_0229cea0 *) r4)->func_ov119_0229c75c();
    func_ov119_0229c2dc(r4);
    return 1;
}
