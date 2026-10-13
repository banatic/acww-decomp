/* func_0204be88 @ 0x0204be88, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_0204be88(unsigned short *p)
{
    int result = 0;

    if (*p >= 0x1408 && *p <= 0x1428) {
        result = 1;
    }

    if (result) {
        return 1;
    } else {
        return 0;
    }
}
