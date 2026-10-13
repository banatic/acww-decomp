/* func_ov004_02230f74 @ 0x02230f74, 0x28 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O1,s
 */

#include "types.h"

extern u8 data_021c75b8;
extern void func_ov004_0223121c(char *self, int a);
void func_ov004_02230f74(char *self)
{
    int t = (data_021c75b8 == 2) ? 1 : 0;
    if (t) {
        func_ov004_0223121c(self, 9);
    }
}
