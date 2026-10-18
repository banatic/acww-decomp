/* func_0206afa4 @ 0x0206afa4, 0x80 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/main/Base_0206afa4.h"
typedef void (Base_0206afa4::*Pmf)();
extern int data_021cda8c;
extern Pmf data_020de854, data_020de994, data_020de9a4;
extern Pmf data_021cdabc[3];

extern "C" void func_0206afa4(Base_0206afa4 *self)
{
    if (!(data_021cda8c & 1)) {
        data_021cdabc[0] = data_020de9a4;
        data_021cdabc[1] = data_020de854;
        data_021cdabc[2] = data_020de994;
        data_021cda8c |= 1;
    }
    Pmf p = data_021cdabc[self->unk_3C];
    (self->*p)();
}
