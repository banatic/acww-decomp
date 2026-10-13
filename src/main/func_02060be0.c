/* func_02060be0 @ 0x02060be0, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_02060be0(unsigned int *r0)
{
    unsigned int r1;
    unsigned int r0_val;
    int result;

    r1 = 0x15a0;
    r0_val = r0[r1 / 4];
    r0_val = (r0_val << 8) >> 0x1a;
    if (r0_val == 0) {
        result = 0;
    } else {
        result = 1;
    }
    return result;
}
