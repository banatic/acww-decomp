/* func_0201c8fc @ 0x0201c8fc, 0xa8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/main/Base_0201c8fc.h"
typedef int (Base_0201c8fc::*Pmf)(int);
extern int data_021c1cf0;
extern Pmf data_020d8ef0, data_020d9010, data_020d9098, data_020d9328;
extern Pmf data_021c1dec[5];

extern "C" int func_0201c8fc(Base_0201c8fc *self, int arg1, unsigned int idx)
{
    if (!(data_021c1cf0 & 1)) {
        data_021c1dec[0] = 0;
        data_021c1dec[1] = data_020d9328;
        data_021c1dec[2] = data_020d8ef0;
        data_021c1dec[3] = data_020d9010;
        data_021c1dec[4] = data_020d9098;
        data_021c1cf0 |= 1;
    }
    if (idx < 5 && data_021c1dec[idx]) {
        if ((self->*(data_021c1dec[idx]))(arg1) != 0) {
            return 1;
        }
    }
    return 0;
}
