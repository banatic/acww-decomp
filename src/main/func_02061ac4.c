/* func_02061ac4 @ 0x02061ac4, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

void func_02061ac4(u16 *out, const u16 *in)
{
    unsigned int ok = 0;
    u16 v;
    unsigned int idx;
    int r;

    v = *in;
    if (v >= 0x38e4 && v <= 0x3933) {
        ok = 1;
    }
    if (ok > 0) {
        if (v >= 0x38e4 && v <= 0x3933) {
            idx = (v - 0x38e4) >> 2;
        } else {
            idx = (unsigned int) -1;
        }
        if (idx != (unsigned int) -1) {
            if (idx < 0x14) {
                r = 0x3934 + idx * 4;
            } else {
                r = 0x3934;
            }
            *out = r;
            return;
        }
    }
    *out = v;
}
