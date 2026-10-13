/* func_ov004_0223c40c @ 0x0223c40c, 0x24 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_0223c430(void *a, short b, int c);
int func_ov004_0223c40c(void *a, int b)
{
    int r;
    if (func_ov004_0223c430(a, (short) b, 0x2000) == 2) {
        r = 1;
    } else {
        r = 0;
    }
    return r;
}
