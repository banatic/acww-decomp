/* func_0209c410 @ 0x0209c410, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209c38c(unsigned char);

int func_0209c410(unsigned char *r5, unsigned char r6)
{
    unsigned char r4 = 0;
    unsigned char r0;

    if (func_0209c38c(r6) != 0) {
        r4 = r5[r6];
    }
    return r4;
}
