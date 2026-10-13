/* func_020991a0 @ 0x020991a0, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_020991a0(unsigned char *p)
{
    p[0x2451] = p[0x2451] + 1;
    if (p[0x2451] == 1) {
        p[0x2451] = 2;
    }
    if (p[0x2451] > 10) {
        p[0x2451] = 10;
    }
}
