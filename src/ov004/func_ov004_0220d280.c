/* func_ov004_0220d280 @ 0x0220d280, 0x10 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

void func_ov004_0220d280(unsigned char *p, unsigned char v, int f)
{
    if (f) {
        p[1] = v;
    } else {
        p[0] = v;
        p[1] = p[0];
    }
}
