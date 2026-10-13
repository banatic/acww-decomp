/* func_ov133_0229b344 @ 0x0229b344, 0x28 bytes, Thumb, module ov133
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern u8 data_021f6c58;
extern int func_ov133_0229b0d4(void *p);

int func_ov133_0229b344(void *p)
{
    int t;
    int v;
    int w;

    t = data_021f6c58 - 0x18;
    if (t < 0) {
        t = 0;
    }
    v = t >> 4;
    w = func_ov133_0229b0d4(p);
    if (v > w) {
        v = w;
    }
    return v;
}
