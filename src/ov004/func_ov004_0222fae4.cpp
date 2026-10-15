/* func_ov004_0222fae4 @ 0x0222fae4, 0x28 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov004_022553d819func_ov004_0222fae4Ev
 */

#include "cpp/ov004/Obj_ov004_022553d8.h"

extern "C" int func_020b6590(void);
extern "C" int func_020b7e04(int, void *);

int Obj_ov004_022553d8::func_ov004_0222fae4()
{
    char *self = (char *) this;
    // DECLS
    // ENDDECLS
    ((Obj_ov004_022553d8 *) self)->func_ov004_0222f908();
    ((Obj_ov004_022553d8 *) self)->func_ov004_0222f640();
    func_020b7e04(func_020b6590(), self + 0x374);
    return 0x1;
}
