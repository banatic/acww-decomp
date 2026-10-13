/* func_ov111_022a0cf8 @ 0x022a0cf8, 0xa4 bytes, Thumb, module ov111
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov111_022a100819func_ov111_022a0cf8Ev
 */

#include "cpp/ov111/Obj_ov111_022a1008.h"

int Obj_ov111_022a1008::func_ov111_022a0cf8()
{
    static void (Obj_ov111_022a1008::*tbl[6])() = {
        &Obj_ov111_022a1008::func_ov111_022a0940, &Obj_ov111_022a1008::func_ov111_022a0910,
        &Obj_ov111_022a1008::func_ov111_022a08bc, &Obj_ov111_022a1008::func_ov111_022a088c,
        &Obj_ov111_022a1008::func_ov111_022a085c, &Obj_ov111_022a1008::func_ov111_022a082c};
    (this->*tbl[state])();
    return 1;
}
