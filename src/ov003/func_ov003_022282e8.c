/* func_ov003_022282e8 @ 0x022282e8, 0x60 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov003_02227fe4(void *a0, void *p, void *b);
extern int func_ov003_02219e58(void *b);
extern int func_ov003_02228018(void *b);

int func_ov003_022282e8(void *a0, void *b, void *self)
{
    int r = 0;
    if (func_ov003_02227fe4(a0, (char *) self + 0x120, b)) {
        if (func_ov003_02219e58(b)) {
            r = 1;
        } else if (func_ov003_02228018(b)) {
            u8 *p = (u8 *) ((char *) self + 0x214);
            if (*p) {
                *p -= 1;
            } else {
                r = 1;
            }
        } else {
            *(u8 *) ((char *) self + 0x214) = 6;
        }
    } else {
        *(u8 *) ((char *) self + 0x214) = 6;
    }
    return r;
}
