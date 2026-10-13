/* func_020b1050 @ 0x020b1050, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b1050(int r0, int r1);

int func_020b1050(int r0, int r1)
{
    int r3 = 0;
    if (r0 >= 0x20) {
        r3 += 0x400;
        r0 -= 0x20;
    }
    r1 <<= 5;
    r0 += r1;
    return r3 + r0;
}
