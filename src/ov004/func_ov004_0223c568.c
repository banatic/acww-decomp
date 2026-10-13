/* func_ov004_0223c568 @ 0x0223c568, 0x3c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O1,s
 */

extern void *func_ov004_0223cd50(void);
extern char *func_ov004_0223cbe8(void *, void *, int);
extern int func_ov004_02218414(void *, void *, int, int);

int func_ov004_0223c568(void *a0, int a1, int a2)
{
    char *p = func_ov004_0223cbe8(func_ov004_0223cd50(), a0, 0);
    if (p != 0) {
        int t = (*(unsigned short *) (p + 0xc) == 0x37) ? 1 : 0;
        if (t != 0) {
            return func_ov004_02218414(p, a0, a1, a2);
        }
    }
    return 0;
}
