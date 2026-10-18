/* func_02013e68 @ 0x02013e68, 0x7c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN12Obj_020d8bd413func_02013e68EPv
 */

#include "cpp/main/Obj_020d8bd4.h"
typedef void (Obj_020d8bd4::*Pmf)(void *);
extern int data_021c1520;
extern Pmf data_020d895c, data_020d897c, data_020d899c;
extern Pmf data_021c16fc[3];

void Obj_020d8bd4::func_02013e68(void *arg)
{
    if (!(data_021c1520 & 1)) {
        data_021c16fc[0] = data_020d895c;
        data_021c16fc[1] = data_020d897c;
        data_021c16fc[2] = data_020d899c;
        data_021c1520 |= 1;
    }
    unsigned char i = unk_0A;
    if (i < 3) {
        (this->*(data_021c16fc[i]))(arg);
    }
}
