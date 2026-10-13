/* func_ov068_02272a7c @ 0x02272a7c, 0x158 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov068_0227775019func_ov068_02272a7cEi
 */

#include "cpp/ov068/Obj_ov068_02277750.h"

typedef int (Obj_ov068_02277750::*PMF2)();

int Obj_ov068_02277750::func_ov068_02272a7c(int state)
{
    static PMF2 tbl[17] = {&Obj_ov068_02277750::func_ov068_02272900, &Obj_ov068_02277750::func_ov068_022728c4,
                           &Obj_ov068_02277750::func_ov068_02272874, &Obj_ov068_02277750::func_ov068_022727d0,
                           &Obj_ov068_02277750::func_ov068_022726d4, &Obj_ov068_02277750::func_ov068_022726c4,
                           &Obj_ov068_02277750::func_ov068_02272654, &Obj_ov068_02277750::func_ov068_0227254c,
                           &Obj_ov068_02277750::func_ov068_022724fc, &Obj_ov068_02277750::func_ov068_022724a4,
                           &Obj_ov068_02277750::func_ov068_022723ec, &Obj_ov068_02277750::func_ov068_022723b4,
                           &Obj_ov068_02277750::func_ov068_02272304, &Obj_ov068_02277750::func_ov068_02272238,
                           &Obj_ov068_02277750::func_ov068_022721e4, &Obj_ov068_02277750::func_ov068_0227215c,
                           &Obj_ov068_02277750::func_ov068_02272104};
    if (state < 17) {
        if ((this->*tbl[state])()) {
            state_2b4 = state;
            return 1;
        }
    }
    return 0;
}
