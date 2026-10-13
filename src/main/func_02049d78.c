/* func_02049d78 @ 0x02049d78, 0x14a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_02049ec4(u16 *p);

int func_02049d78(u16 *p)
{
    int r;
    unsigned int d;
    unsigned int c;
    unsigned int b;
    u16 v;
    unsigned int a;

    r = 1;
    b = c = d = 1;
    a = 0;
    v = *p;
    if (v <= 5) {
        a = 1;
    }
    if (!a) {
        if (!(v >= 6 && v <= 0xb)) {
            b = 0;
        }
    }
    if (!b) {
        if (!(v >= 0xc && v <= 0x11)) {
            c = 0;
        }
    }
    if (!c) {
        if (!((v >= 0x12 && v <= 0x19) || v == 0x1c)) {
            d = 0;
        }
    }
    if (d) {
        switch (func_02049ec4(p)) {
            case 0:
                r = *p + 1;
                break;
            case 1:
                r = *p - 5;
                break;
            case 2:
                r = *p - 0xb;
                break;
            case 3:
                if (*p == 0x1c) {
                    r = 9;
                } else {
                    r = *p - 0x11;
                }
                break;
        }
    } else if ((v >= 0x8a && v <= 0x8f) || (v >= 0x90 && v <= 0x95) || (v >= 0x96 && v <= 0x9b) || (v >= 0x9c && v <= 0xa3) ||
               v == 0xa5) {
        switch (func_02049ec4(p)) {
            case 0:
                r = *p - 0x89;
                break;
            case 1:
                r = *p - 0x8f;
                break;
            case 2:
                r = *p - 0x95;
                break;
            case 3:
                if (*p == 0xa5) {
                    r = 7;
                } else {
                    r = *p - 0x9b;
                }
                break;
        }
    } else if ((v >= 0x6e && v <= 0x73) || (v >= 0x74 && v <= 0x79) || (v >= 0x7a && v <= 0x7f) || (v >= 0x80 && v <= 0x87)) {
        switch (func_02049ec4(p)) {
            case 0:
                r = *p - 0x6d;
                break;
            case 1:
                r = *p - 0x73;
                break;
            case 2:
                r = *p - 0x79;
                break;
            case 3:
                r = *p - 0x7f;
                break;
        }
    }
    return r;
}
