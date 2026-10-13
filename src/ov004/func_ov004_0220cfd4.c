/* func_ov004_0220cfd4 @ 0x0220cfd4, 0x18 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

int func_ov004_0220cfd4(signed char *p, int v)
{
    unsigned int i;
    for (i = 0; i < 4; i++) {
        if (v == p[i]) {
            return 1;
        }
    }
    return 0;
}
