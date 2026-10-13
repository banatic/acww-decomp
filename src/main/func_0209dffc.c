/* func_0209dffc @ 0x0209dffc, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_0209dffc(const unsigned char *p)
{
    int result = 0;
    int good = result;

    if (p[0] < 60 && p[1] < 60 && p[2] < 24 && p[3] >= 1 && p[3] <= 31 && p[4] >= 1 && p[4] <= 12) {
        good = 1;
    }
    if (good != 0 && p[5] <= 99) {
        result = 1;
    }

    if (result != 0) {
        return 0;
    } else {
        return 1;
    }
}
