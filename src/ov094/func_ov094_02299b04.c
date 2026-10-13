/* func_ov094_02299b04 @ 0x02299b04, 0x70 bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

int func_ov094_02299b04(unsigned int x)
{
    volatile long long unused;
    (void) &unused;
    if ((x >= 0x1531 && x <= 0x153a) || (x >= 0x153b && x <= 0x1541) || (x >= 0x154a && x <= 0x1553) ||
        (x >= 0x12e8 && x <= 0x131f) || (x >= 0x12b0 && x <= 0x12e7)) {
        return 1;
    }
    return 0;
}
