/* func_ov003_02227a48 @ 0x02227a48, 0x68 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

#pragma opt_propagation off

extern char data_ov003_0225f76c[];
extern int func_020961a8(int k);
extern int func_ov003_02227a30(void *a0);

int func_ov003_02227a48(void *a0, void *a1, int v)
{

    int i;
    char *p;
    int c;

    c = (v == 0x34 || v == 0x35 || v == 0x36) ? 1 : 0;
    if (c) {
        if (func_020961a8(4) == 0) {
            return 0;
        }
        p = data_ov003_0225f76c + 3 * 0x24c;
        for (i = 3; i < 6; i++) {
            if ((char *) a1 != p && *(u8 *) (p + 0x7f) != 0) {
                return 0;
            }
            p += 0x24c;
        }
    } else if (v == 0x37) {
        if (func_ov003_02227a30(a0) == 0) {
            return 0;
        }
    }
    return 1;
}
