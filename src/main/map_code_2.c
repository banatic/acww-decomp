/* map_code_2: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0204c774 @ 0x0204c774, 0x14 bytes, Thumb
 * func_0204c71c @ 0x0204c71c, 0x58 bytes, Thumb
 */

int func_0204c774(unsigned short *ptr)
{
    if (*ptr == 0xFFFF) {
        return 1;
    }
    return 0;
}

int func_0204c71c(unsigned short *p)
{
    int res = 1;
    int f3 = res;
    int f2 = res;
    int f1 = res;
    unsigned short v = *p;

    if (v != 0xF030 && v != 0xF031) {
        f1 = 0;
    }
    if (f1 == 0) {
        if (v != 0xFFFD) {
            f2 = 0;
        }
    }
    if (f2 == 0) {
        if (v != 0xFFFE) {
            f3 = 0;
        }
    }
    if (f3 == 0) {
        if (func_0204c774(p) == 0) {
            res = 0;
        }
    }
    return res;
}
