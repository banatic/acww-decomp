/* func_020b5b18 @ 0x020b5b18, 0x74 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/main/Obj_020e5408.h"
typedef void (Obj_020e5408::*Pmf)();
extern int data_021f6910;
extern Pmf data_020e53e8, data_020e53f0, data_020e53f8;
extern Pmf data_021f6914[3];

extern "C" int func_020b5b18(Obj_020e5408 *self)
{
    if (!(data_021f6910 & 1)) {
        data_021f6914[0] = data_020e53f8;
        data_021f6914[1] = data_020e53f0;
        data_021f6914[2] = data_020e53e8;
        data_021f6910 |= 1;
    }
    (self->*(data_021f6914[self->unk_50]))();
    return 1;
}
