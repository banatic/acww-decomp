/* func_0208c04c @ 0x0208c04c, 0xac bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/main/Obj_020e2234.h"

typedef void (Obj_020e2234::*PMF)();

extern int data_021d315c;
extern PMF data_020e216c, data_020e2174, data_020e217c, data_020e2184, data_020e218c, data_020e2194, data_020e21a4;
extern PMF data_021d3220[7];

extern "C" void func_0208c04c(Obj_020e2234 *self)
{
    if (!(data_021d315c & 1)) {
        data_021d3220[0] = data_020e21a4;
        data_021d3220[1] = data_020e216c;
        data_021d3220[2] = data_020e2194;
        data_021d3220[3] = data_020e218c;
        data_021d3220[4] = data_020e2184;
        data_021d3220[5] = data_020e217c;
        data_021d3220[6] = data_020e2174;
        data_021d315c |= 1;
    }
    (self->*data_021d3220[self->idx])();
}
