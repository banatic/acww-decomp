/* func_ov118_0229c63c @ 0x0229c63c, 0xd8 bytes, Thumb, module ov118
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov118_0229cc0819func_ov118_0229c63cEv
 */

#include "cpp/ov118/Obj_ov118_0229cc08.h"

typedef void (Obj_ov118_0229cc08::*PMF)();

int Obj_ov118_0229cc08::func_ov118_0229c63c()
{
    static PMF tbl[9] = {&Obj_ov118_0229cc08::func_ov118_0229c404, &Obj_ov118_0229cc08::func_ov118_0229c3d8,
                         &Obj_ov118_0229cc08::func_ov118_0229c3ac, &Obj_ov118_0229cc08::func_ov118_0229c378,
                         &Obj_ov118_0229cc08::func_ov118_0229c35c, &Obj_ov118_0229cc08::func_ov118_0229c2a0,
                         &Obj_ov118_0229cc08::func_ov118_0229c240, &Obj_ov118_0229cc08::func_ov118_0229c1ec,
                         &Obj_ov118_0229cc08::func_ov118_0229c18c};
    func_ov118_0229c070();
    (this->*tbl[state])();
    func_ov118_0229bfa4();
    return 1;
}
