/* func_0206ae64 @ 0x0206ae64, 0x60 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/main/Base_0206ae64.h"
typedef void (Base_0206ae64::*PMF)();
extern "C" void func_0206ae64(Base_0206ae64 *obj)
{
    static PMF table[] = {&Base_0206ae64::func_02069510};
    PMF pmf = table[obj->index];
    (obj->*pmf)();
}
