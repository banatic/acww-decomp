/* func_0206b474 @ 0x0206b474, 0x9c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/main/Base_0206b474.h"

typedef void (Base_0206b474::*PMF)();

extern "C" void func_0206b474(Base_0206b474 *obj)
{
    static PMF table[5] = {&Base_0206b474::func_0206a62c, &Base_0206b474::func_0206a600, &Base_0206b474::func_0206a5d4,
                           &Base_0206b474::func_0206a5a8, &Base_0206b474::func_0206a57c};
    PMF pmf = table[obj->index];
    (obj->*pmf)();
}
