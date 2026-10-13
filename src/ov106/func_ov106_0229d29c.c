/* func_ov106_0229d29c @ 0x0229d29c, 0x48 bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov106_0229d090(unsigned char *a, int b);
extern int func_ov106_0229d20c(unsigned char *a, int b);
extern void func_02066830(unsigned char *dst, int val);
extern void func_ov106_0229d24c(unsigned char *p, unsigned char c, unsigned char *q);
extern void func_ov106_0229cd60(unsigned char *a, int b);

int func_ov106_0229d29c(unsigned char *a, int b)
{
    if (func_ov106_0229d090(a, b) == 0) {
        func_02066830(a + 0x4280, func_ov106_0229d20c(a, b));
        func_ov106_0229d24c(a, *(unsigned char *) (a + 0xb7), a + 0x4280);
    }
    func_ov106_0229cd60(a, b);
    return 1;
}
