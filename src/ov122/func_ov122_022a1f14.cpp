/* func_ov122_022a1f14 @ 0x022a1f14, 0x2a bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov122_022a273819func_ov122_022a1f14Ev
 */

#include "cpp/ov122/Obj_ov122_022a2738.h"

extern "C" int func_ov122_022a1e90(void *);
extern "C" int func_ov122_022a1898(void *);
extern "C" int func_ov122_022a1864(void *);

int Obj_ov122_022a2738::func_ov122_022a1f14()
{
    void *arg0 = (void *) this;
    if (func_ov122_022a1e90(arg0)) {
        return 1;
    }
    func_ov122_022a1898(arg0);
    ((Obj_ov122_022a2738 *) arg0)->func_ov122_022a1f40();
    func_ov122_022a1864(arg0);
    return 1;
}
