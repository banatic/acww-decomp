/* func_ov004_0223cadc @ 0x0223cadc, 0x34 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_0223c72c(void);
extern int func_ov004_0223cb5c(void *);

void *func_ov004_0223cadc(char *self, int i)
{
    char *p;
    if (func_ov004_0223c72c() != 0) {
        p = self + (i & 1) * 0x40;
        if (func_ov004_0223cb5c(p) != -1) {
            return p;
        }
    }
    return 0;
}
