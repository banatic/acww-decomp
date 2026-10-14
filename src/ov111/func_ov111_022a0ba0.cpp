/* func_ov111_022a0ba0 @ 0x022a0ba0, 0x2a bytes, Thumb, module ov111
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov111_022a100819func_ov111_022a0ba0Ev
 */

#include "cpp/ov111/Obj_ov111_022a1008.h"

extern "C" int func_ov111_022a0a5c(int arg);
extern "C" void func_ov111_022a0b58(int arg);
extern "C" void func_ov111_022a0b20(int arg);

int Obj_ov111_022a1008::func_ov111_022a0ba0()
{
    int arg = (int) this;
    if (func_ov111_022a0a5c(arg) != 0) {
        return 1;
    }
    func_ov111_022a0b58(arg);
    ((Obj_ov111_022a1008 *) arg)->func_ov111_022a0bcc();
    func_ov111_022a0b20(arg);
    return 1;
}
