/* func_ov106_0229cd20 @ 0x0229cd20, 0x40 bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

extern void func_02066830(void *a, void *b);
extern void func_ov106_0229cd88(void *a, void *b);
extern void func_ov106_0229d24c(void *a, void *b, void *c);

void func_ov106_0229cd20(unsigned char *self, void *arg)
{
    if (self[0xb4] == 1) {
        func_02066830(self + 0x4280, self + 0x4180);
        func_ov106_0229cd88(self, arg);
        func_ov106_0229d24c(self, arg, self + 0x4280);
    }
}
