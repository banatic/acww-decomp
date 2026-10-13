/* func_ov094_022999e4 @ 0x022999e4, 0x70 bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

int func_ov094_022999e4(unsigned int x)
{
    volatile long long unused;
    (void) &unused;
    if ((x >= 0x12e8 && x <= 0x131f) || (x >= 0x12b0 && x <= 0x12e7)) {
        return 0;
    }
    if ((x >= 0x137c && x <= 0x137c) || (x >= 0x1408 && x <= 0x1428) || (x >= 0x1471 && x <= 0x1491)) {
        return 0;
    }
    return 1;
}
