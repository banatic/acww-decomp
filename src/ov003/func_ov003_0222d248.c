/* func_ov003_0222d248 @ 0x0222d248, 0xb6 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

int func_ov003_0222d248(int a, int b)
{
    switch (a) {
        case 16:
        case 17:
        case 18:
        case 19:
        case 20:
            if (b == 1 || b == 2) {
                return 5;
            }
            break;
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 10:
        case 12:
        case 13:
        case 14:
        case 15:
        case 21:
        case 22:
        case 23:
        case 25:
        case 27:
        case 28:
        case 29:
        case 32:
        case 37:
        case 50:
        case 51:
        case 54:
        case 55:
            if (b == 1 || b == 2) {
                return 4;
            }
            break;
        case 59:
            if (b == 1) {
                return 4;
            }
            break;
        case 26:
            if (b != 1) {
                return 4;
            }
            break;
        default:
            return 3;
    }
    return 3;
}
