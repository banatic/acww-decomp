/* func_0206b474 @ 0x0206b474, 0x9c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/main/Base_0206b474.h"

typedef void (Base_0206b474::*PMF)();

extern int data_021cda90;
extern PMF data_020de94c, data_020dea0c, data_020debac, data_020debb4, data_020debbc;
extern PMF data_021cdaec[5];

extern "C" void func_0206b474(Base_0206b474 *obj)
{
    if (!(data_021cda90 & 1)) {
        data_021cdaec[0] = data_020de94c;
        data_021cdaec[1] = data_020dea0c;
        data_021cdaec[2] = data_020debbc;
        data_021cdaec[3] = data_020debb4;
        data_021cdaec[4] = data_020debac;
        data_021cda90 |= 1;
    }
    PMF pmf = data_021cdaec[obj->index];
    (obj->*pmf)();
}
