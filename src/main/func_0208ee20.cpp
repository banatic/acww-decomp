/* func_0208ee20 @ 0x0208ee20, 0x80 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/main/Obj_020e236c.h"

typedef void (Obj_020e236c::*Pmf)();
extern int data_021d35c8;
extern Pmf data_020e2344, data_020e234c, data_020e2354, data_020e235c;
extern Pmf data_021d35d8[4];

extern "C" void func_0208ee20(Obj_020e236c *self)
{
    if (!(data_021d35c8 & 1)) {
        data_021d35d8[0] = data_020e235c;
        data_021d35d8[1] = data_020e2344;
        data_021d35d8[2] = data_020e2354;
        data_021d35d8[3] = data_020e234c;
        data_021d35c8 |= 1;
    }
    (self->*(data_021d35d8[self->unk_20]))();
}
