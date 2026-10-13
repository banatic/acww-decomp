/* func_02098d84 @ 0x02098d84, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern u16 *func_02098f48(void *, int);
extern int func_02098e8c(void *, int);
extern int func_0204c878(u16 *);

int func_02098d84(void *self)
{
    u16 *p;
    int total;
    int i;

    p = func_02098f48(self, 0);
    total = 0;
    i = 0;
    for (; i < 0xf; i++) {
        unsigned int ok = 0;
        if (*p >= 0x1492 && *p <= 0x14fd) {
            ok = 1;
        }
        if (ok != 0) {
            if (func_02098e8c(self, i) == 0) {
                total = total + func_0204c878(p);
            }
        }
        p++;
    }
    return total;
}
