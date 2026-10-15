/* func_ov004_0223c3b8 @ 0x0223c3b8, 0x54 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov004_0223cd50(void);
extern void *func_ov004_0223cbe8(void *, void *, int);
extern int func_ov004_0223c430(void *, short, int);
int func_ov004_0223c3b8(void *self, int a)
{
    void *e = func_ov004_0223cbe8(func_ov004_0223cd50(), self, 0);
    if (e != 0 && *(long *) ((char *) e + 0x780) != 0x26) {
        return 0;
    }
    if (func_ov004_0223c430(self, (short) (a + 0x4000), 0x2000) == 2) {
        return 1;
    }
    return 0;
}
