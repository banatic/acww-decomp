/* insect_tables: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020617d8 @ 0x020617d8, 0x18 bytes, Thumb
 * func_02061798 @ 0x02061798, 0x40 bytes, Thumb
 * func_02061624 @ 0x02061624, 0x174 bytes, Thumb
 * func_02061550 @ 0x02061550, 0xd2 bytes, Thumb
 */

#include "types.h"

extern unsigned int data_020dded8[];

int func_020617d8(int r0)
{
    if (r0 < 0 || r0 > 0xb) {
        r0 = 0;
    }
    return data_020dded8[r0];
}

int func_02061798(unsigned int a)
{
    if (a >= 4 && a <= 7) {
        return 1;
    }
    if (a >= 8 && a <= 0xf) {
        return 2;
    }
    if (a == 0x10) {
        return 3;
    }
    if ((u8) (a + 0xef) <= 1) {
        return 4;
    }
    if (a >= 0x13 && a <= 0x16) {
        return 5;
    }
    return 0;
}

int func_02061624(unsigned int x)
{
    switch (x) {
        case 0:
            return 50;
        case 1:
            return 50;
        case 2:
            return 90;
        case 3:
            return 105;
        case 4:
            return 85;
        case 5:
            return 115;
        case 6:
            return 42;
        case 7:
            return 260;
        case 8:
            return 60;
        case 9:
            return 280;
        case 10:
            return 13;
        case 11:
            return 38;
        case 12:
            return 73;
        case 13:
            return 58;
        case 14:
            return 82;
        case 15:
            return 35;
        case 16:
            return 58;
        case 17:
            return 60;
        case 18:
            return 44;
        case 19:
            return 45;
        case 20:
            return 70;
        case 21:
            return 38;
        case 22:
            return 76;
        case 23:
            return 90;
        case 24:
            return 5;
        case 25:
            return 14;
        case 26:
            return 45;
        case 27:
            return 28;
        case 28:
            return 18;
        case 29:
            return 43;
        case 30:
            return 35;
        case 31:
            return 85;
        case 32:
            return 8;
        case 33:
            return 23;
        case 34:
            return 25;
        case 35:
            return 35;
        case 36:
            return 90;
        case 37:
        case 57:
            return 15;
        case 38:
            return 35;
        case 39:
            return 30;
        case 40:
            return 65;
        case 41:
            return 60;
        case 42:
            return 68;
        case 43:
            return 59;
        case 44:
            return 80;
        case 45:
            return 120;
        case 46:
            return 115;
        case 47:
            return 160;
        case 48:
            return 2;
        case 49:
            return 10;
        case 50:
            return 6;
        case 51:
            return 9;
        case 52:
            return 28;
        case 53:
            return 25;
        case 54:
            return 65;
        case 55:
            return 160;
        case 56:
        default:
            return 0;
    }
}

int func_02061550(int kind)
{
    switch (kind) {
        case 9:
        case 16:
        case 17:
        case 18:
        case 19:
        case 20:
        case 31:
        case 33:
        case 34:
        case 38:
        case 39:
        case 40:
        case 41:
        case 42:
        case 43:
        case 44:
        case 52:
            return 0xe;
        case 53:
            return 0xc;
        case 36:
        case 45:
        case 46:
        case 47:
            return 0xd;
        case 35:
            return 0x10;
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
            return 1;
        case 12:
        case 13:
        case 27:
        case 28:
        case 29:
            return 4;
        case 10:
        case 14:
        case 15:
        case 26:
        case 32:
            return 2;
        case 21:
        case 22:
        case 23:
        case 50:
            return 0;
        case 25:
            return 6;
        case 37:
            return 5;
        case 30:
        case 54:
        case 55:
            return 9;
        case 49:
            return 0xa;
        case 8:
            return 0xb;
        case 11:
            return 0xc;
        case 51:
            return 8;
        case 59:
            return 7;
        case 48:
            return 0x11;
        case 24:
        case 56:
        case 57:
        case 58:
        default:
            return 4;
    }
}
