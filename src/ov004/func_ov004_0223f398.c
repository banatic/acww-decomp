/* func_ov004_0223f398 @ 0x0223f398, 0x82 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

int func_ov004_0223f398(void *a, int i, int m)
{
    switch (i) {
        case 9:
        case 11:
        case 16:
        case 17:
        case 18:
        case 19:
        case 20:
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
        case 49:
        case 53:
            return 0;
        case 30:
            if (m != 4 && m != 3) {
                return 0;
            }
            break;
    }
    return 1;
}
