/* func_ov101_0229d134 @ 0x0229d134, 0x34 bytes, Thumb, module ov101
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov101_0229c944(void *, unsigned char);
extern int func_ov101_0229cf80(void *);
extern int func_ov101_0229c9d8(void *);
extern int func_ov002_02209d8c(void *);

void func_ov101_0229d134(void *self)
{
    if (func_ov002_02209d8c((char *) self + 0x2284)) {
        func_ov101_0229c944(self, *(unsigned char *) ((char *) self + 0xb2));
        func_ov101_0229cf80(self);
    } else {
        func_ov101_0229c9d8(self);
    }
}
