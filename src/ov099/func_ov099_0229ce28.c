/* func_ov099_0229ce28 @ 0x0229ce28, 0x3e bytes, Thumb, module ov099
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov099_0229cf30(unsigned char *a, int b);
extern int func_ov099_0229cf04(unsigned char *a, int b);
extern void func_ov094_0229aa14(unsigned char *p, int r, int c, int d);
extern void func_ov094_0229a9b4(unsigned char *p, int r);

void func_ov099_0229ce28(unsigned char *a, int b, int c, int d)
{
    if (func_ov099_0229cf30(a, b)) {
        int r = func_ov099_0229cf04(a, b);
        func_ov094_0229aa14(a + 0xcc, r, c, d);
        a += 0xcc;
        func_ov094_0229a9b4(a, r);
    }
}
