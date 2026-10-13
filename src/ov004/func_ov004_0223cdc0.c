/* func_ov004_0223cdc0 @ 0x0223cdc0, 0x26 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_0223c130(void);
int func_ov004_0223cdc0(int *a)
{
    int n = 0;
    unsigned int i;
    for (i = 0; i < (unsigned int) func_ov004_0223c130(); i++) {
        if (a[i] != 0) {
            n++;
        }
    }
    return n;
}
