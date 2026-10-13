/* func_0204a034 @ 0x0204a034, 0x11c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_0204bbec(u16 *);
extern int func_0204ba94(u16 *);

int func_0204a034(u16 *p)
{
    int b8, b7, b6, b5, b4, b3, b2, b1, b0;
    int c3, c2, c1, c0;
    int ret;
    u16 v;

    ret = 0;
    if (func_0204bbec(p)) {
        ret = 1;
    } else {
        b8 = 1;
        b7 = 1;
        b6 = 1;
        b5 = 1;
        b4 = 1;
        b3 = 1;
        b2 = 1;
        b1 = 1;
        b0 = 0;
        v = *p;
        if (v >= 0x26 && v <= 0x2a) {
            b0 = 1;
        }
        if (!b0 && !(v >= 0x5d && v <= 0x61)) {
            b1 = 0;
        }
        if (!b1 && !(v >= 0x2f && v <= 0x56)) {
            b2 = 0;
        }
        if (!b2 && !(v >= 0x57 && v <= 0x5b)) {
            b3 = 0;
        }
        if (!b3 && !(v >= 0x66 && v <= 0x68)) {
            b4 = 0;
        }
        if (!b4 && !(v == 0x69)) {
            b5 = 0;
        }
        if (!b5 && !(v >= 0x6a && v <= 0x6c)) {
            b6 = 0;
        }
        if (!b6 && !(v == 0x6d)) {
            b7 = 0;
        }
        if (!b7 && !(v >= 0xc8 && v <= 0xcf)) {
            b8 = 0;
        }
        if (b8 && func_0204ba94(p) == 0) {
            ret = 1;
        } else {
            c3 = 1;
            c2 = 1;
            c1 = 1;
            c0 = 0;
            v = *p;
            if (v >= 0x2b && v <= 0x2e) {
                c0 = 1;
            }
            if (!c0 && !(v >= 0xff && v <= 0x102)) {
                c1 = 0;
            }
            if (!c1 && !(v >= 0x62 && v <= 0x65)) {
                c2 = 0;
            }
            if (!c2 && !(v >= 0xd0 && v <= 0xd3)) {
                c3 = 0;
            }
            if (c3) {
                ret = 1;
            }
        }
    }
    return ret;
}
