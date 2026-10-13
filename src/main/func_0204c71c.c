/* func_0204c71c @ 0x0204c71c, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204c774(unsigned short *p);

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
