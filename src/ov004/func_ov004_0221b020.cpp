/* func_ov004_0221b020 @ 0x0221b020, 0x40 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov004_0225328c19func_ov004_0221b020Ev
 */

#include "cpp/ov004/Obj_ov004_0225328c.h"

#include "types.h"

extern "C" int func_020b6590(void);
extern "C" void func_020b7d84(int, void *, void *, int, int, int);

int Obj_ov004_0225328c::func_ov004_0221b020()
{
    char *self = (char *) this;
    // DECLS
    // ENDDECLS
    ((Obj_ov004_0225328c *) self)->func_ov004_0221ae00();
    func_020b7d84(func_020b6590(), self + 0x138, self + 0x5c, *(int *) (self + 0x158), 0x10, *(u8 *) (self + 0x154));
    return 0x1;
}
