/* func_ov004_0223cd78 @ 0x0223cd78, 0x2a bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_0223c130(void);
int func_ov004_0223cd78(int *a, int v)
{
    unsigned int i;
    for (i = 0; i < (unsigned int) func_ov004_0223c130(); i++) {
        int t = a[i];
        if (t == v) {
            return i;
        }
    }
    return -1;
}
