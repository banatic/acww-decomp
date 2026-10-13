/* func_ov004_02213e74 @ 0x02213e74, 0x6c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov004_0225237419func_ov004_02213e74Ev
 */

#include "cpp/ov004/Obj_ov004_02252374.h"

typedef void (Obj_ov004_02252374::*Pmf)(void);

void Obj_ov004_02252374::func_ov004_02213e74()
{
    static Pmf tbl[] = {&Obj_ov004_02252374::func_ov004_02213e10, &Obj_ov004_02252374::func_ov004_02213d70};
    unsigned char i = unk_874;
    if (i < 2) {
        (this->*(tbl[i]))();
    }
}
