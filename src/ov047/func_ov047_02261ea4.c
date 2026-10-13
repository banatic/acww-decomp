/* func_ov047_02261ea4 @ 0x02261ea4, 0xd0 bytes, Thumb, module ov047
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

int func_ov047_02261ea4(u16 *p, int flag)
{
    // DECLS
    unsigned int a;
    u16 v;
    unsigned int b;
    unsigned int c;
    unsigned int d;
    unsigned int e;
    unsigned int g;
    unsigned int h;
    // ENDDECLS

    if (flag == 0) {
        a = 0;
        v = *p;
        if (v >= 0x450c && v <= 0x45db) {
            a = 1;
        }
        b = (v >= 0x3934 && v <= 0x3983) ? 1 : 0;
        c = (v >= 0x38e4 && v <= 0x3933) ? 1 : 0;
        d = (v >= 0x12e8 && v <= 0x131f) ? 1 : 0;
        e = (v >= 0x12b0 && v <= 0x12e7) ? 1 : 0;
        g = (v >= 0x3894 && v <= 0x38e3) ? 1 : 0;
        h = (v >= 0x1549 && v <= 0x1549) ? 1 : 0;
        return h | a | g | e | d | c | b;
    }
    return 0;
}
