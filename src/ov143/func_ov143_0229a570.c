/* func_ov143_0229a570 @ 0x0229a570, 0x32 bytes, Thumb, module ov143
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e484(void *);
extern int func_ov143_02299e18(void *, unsigned char);
extern void func_ov002_02208098(void *, int);
extern void func_ov143_02299f48(void *);

void func_ov143_0229a570(void *self)
{
    if (func_0208e484((char *) self + 0xac)) {
        if (!func_ov143_02299e18(self, *(unsigned char *) ((char *) self + 0xa4))) {
            func_ov002_02208098(self, 2);
            func_ov143_02299f48(self);
        }
    }
}
