/* func_0208dd78 @ 0x0208dd78, 0x98 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/main/Obj_020e226c.h"
typedef void (Obj_020e226c::*Pmf)();
extern "C" void func_0208d4a4(Obj_020e226c *);
extern "C" void func_0208d784(Obj_020e226c *);
extern "C" void func_0208d410(Obj_020e226c *);
extern int data_021d3158;
extern Pmf data_020e212c, data_020e213c, data_020e214c, data_020e215c;
extern Pmf data_021d3170[4];

extern "C" void func_0208dd78(Obj_020e226c *self)
{
    if (!(data_021d3158 & 1)) {
        data_021d3170[0] = data_020e213c;
        data_021d3170[1] = data_020e212c;
        data_021d3170[2] = data_020e215c;
        data_021d3170[3] = data_020e214c;
        data_021d3158 |= 1;
    }
    (self->*(data_021d3170[self->unk_20]))();
    func_0208d4a4(self);
    func_0208d784(self);
    if (self->unk_20) {
        func_0208d410(self);
    }
}
