/* func_ov106_0229cd60 @ 0x0229cd60, 0x28 bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov106_0229d24c(void *self, int arg, void *ptr);

void func_ov106_0229cd60(void *self, int arg)
{
    if (((unsigned char *) self)[0xb4] == 1) {
        func_ov106_0229d24c(self, arg, (char *) self + 0x4180);
    }
    ((unsigned char *) self)[0xb4] = 0;
}
