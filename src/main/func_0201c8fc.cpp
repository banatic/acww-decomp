/* func_0201c8fc @ 0x0201c8fc, 0xa8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/main/Base_0201c8fc.h"
typedef int (Base_0201c8fc::*Pmf)(int);
extern "C" int func_0201c8fc(Base_0201c8fc *self, int arg1, unsigned int idx)
{
    static Pmf tbl[] = {0, &Base_0201c8fc::func_0201cb24, &Base_0201c8fc::func_0201ca9c, &Base_0201c8fc::func_0201ca24,
                        &Base_0201c8fc::func_0201ca9c};
    if (idx < 5 && tbl[idx]) {
        if ((self->*(tbl[idx]))(arg1) != 0) {
            return 1;
        }
    }
    return 0;
}
