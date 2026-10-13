/* func_ov141_0229a028 @ 0x0229a028, 0xb4 bytes, Thumb, module ov141
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

int func_ov141_0229a028(u8 *base, u8 *key)
{
    int i;
    int e5, e4, e3, e2, e1;
    u8 *e;

    for (i = 0; i < 6; i++) {
        if (*(base + i + 0x1a7f) != 2) {
            continue;
        }
        e5 = 0;
        e4 = 0;
        e3 = 0;
        e2 = 0;
        e1 = 0;
        e = base + 0xc8e + i * 0xe0;
        if (key[2] == e[0] && key[3] == e[1]) {
            e1 = 1;
        }
        if (e1 != 0) {
            if (key[4] == e[2]) {
                e2 = 1;
            }
        }
        if (e2 != 0) {
            if (key[5] == e[3]) {
                e3 = 1;
            }
        }
        if (e3 != 0) {
            if (key[6] == e[4]) {
                e4 = 1;
            }
        }
        if (e4 != 0) {
            if (key[7] == e[5]) {
                e5 = 1;
            }
        }
        if (e5 != 0) {
            return i;
        }
    }
    return -1;
}
