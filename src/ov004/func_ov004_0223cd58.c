/* func_ov004_0223cd58 @ 0x0223cd58, 0x20 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_0223c130(void);
int func_ov004_0223cd58(int *self, unsigned int i)
{
    int r;
    if (i < (unsigned int) func_ov004_0223c130()) {
        r = self[i];
    } else {
        r = 0;
    }
    return r;
}
