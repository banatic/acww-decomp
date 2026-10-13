/* func_ov003_02229eac @ 0x02229eac, 0x54 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

int func_02095794(int k);
int func_020ea990(int h, void *p);

void func_ov003_02229eac(u8 *st, char *obj)
{
    int h;
    if (st[0] != 0) {
        st[0] = (u8) (st[0] - 3);
        if (st[0] < 10) {
            st[0] = 0;
        }
    }
    if (st[2] != 0) {
        st[2] = (u8) (st[2] - 1);
    }
    h = func_02095794(0);
    if (h != 0) {
        if (func_020ea990(h, obj + 0x120) < 0x8000) {
            st[3] = 1;
        }
    }
}
