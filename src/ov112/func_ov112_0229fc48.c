/* func_ov112_0229fc48 @ 0x0229fc48, 0x8c bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_02070854(u8 *p, int a, int b, unsigned int off, unsigned int n);

void func_ov112_0229fc48(u8 *base, int a1, int a2, unsigned int pos, unsigned int rem)
{
    int i;
    unsigned int acc;
    int len;
    unsigned int take;
    unsigned int end;

    acc = 0;
    for (i = 0; i < 6; i++) {
        len = *(int *) (base + (i + 1) * 4 + 0x6c50) - *(int *) (base + i * 4 + 0x6c50);
        if (len == 0) {
            return;
        }
        if (pos >= acc) {
            end = acc + len;
            if (pos < end) {
                if (end > pos + rem) {
                    take = rem;
                } else {
                    take = len - (pos - acc);
                }
                func_02070854(base + 0x3fac + i * 0x6c, a1, a2, pos - acc, take);
                pos = (u8) end;
                rem -= take;
                if (rem == 0) {
                    return;
                }
            }
        }
        acc += len;
    }
}
