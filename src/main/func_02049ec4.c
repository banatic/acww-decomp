/* func_02049ec4 @ 0x02049ec4, 0xb0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
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
