/* town_family_2: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02049ec4 @ 0x02049ec4, 0xb0 bytes, Thumb
 * func_02049d78 @ 0x02049d78, 0x14a bytes, Thumb
 */

#include "types.h"

int func_02049ec4(u16 *p0)
{
    int category = 7;
    unsigned int isLow = 0;
    u16 c = *p0;

    if (c <= 5) {
        isLow = 1;
    }

    if (isLow != 0 || (c >= 0x8a && c <= 0x8f) || (c >= 0x6e && c <= 0x73)) {
        category = 0;
        goto end;
    }
    if ((c >= 6 && c <= 0xb) || (c >= 0x90 && c <= 0x95) || (c >= 0x74 && c <= 0x79)) {
        category = 1;
        goto end;
    }
    if ((c >= 0xc && c <= 0x11) || (c >= 0x96 && c <= 0x9b) || (c >= 0x7a && c <= 0x7f)) {
        category = 2;
        goto end;
    }
    if ((c >= 0x12 && c <= 0x19) || c == 0x1c || (c >= 0x9c && c <= 0xa3) || c == 0xa5 || (c >= 0x80 && c <= 0x87)) {
        category = 3;
        goto end;
    }
    if ((int) c > 0x88) {
        goto check_a4;
    }
    if ((int) c >= 0x88) {
        goto set4;
    }
    if ((int) c > 0x1e) {
        goto end;
    }
    if ((int) c < 0x1a) {
        goto end;
    }
    if (c == 0x1a) {
        goto set4;
    }
    if (c == 0x1d) {
        goto set5;
    }
    if (c != 0x1e) {
        goto end;
    }
    goto set6;

check_a4:
    if (c != 0xa4) {
        goto end;
    }
set4:
    category = 4;
    goto end;
set5:
    category = 5;
    goto end;
set6:
    category = 6;
end:
    return category;
}

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
