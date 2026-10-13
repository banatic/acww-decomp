/* func_ov004_0223efc4 @ 0x0223efc4, 0x98 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

int func_ov004_0223efc4(void *unused, char *p)
{
    switch (*(signed char *) (p + 0x196)) {
        case 9:
        case 16:
        case 17:
        case 18:
        case 19:
        case 20:
        case 24:
        case 25:
        case 31:
        case 33:
        case 34:
        case 35:
        case 36:
        case 38:
        case 39:
        case 40:
        case 41:
        case 42:
        case 43:
        case 44:
        case 45:
        case 46:
        case 47:
        case 48:
        case 50:
        case 51:
        case 56:
            return 0;
        case 30:
            if (*(short *) (p + 0x172) != 0x19) {
                return 1;
            }
            return 0;
    }
    return 1;
}
