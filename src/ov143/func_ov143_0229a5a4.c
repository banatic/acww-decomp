/* func_ov143_0229a5a4 @ 0x0229a5a4, 0x26 bytes, Thumb, module ov143
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov143_0229ac10(void *);
extern int func_ov002_02209f64(void *);
extern void func_ov002_02208098(void *, unsigned char);

void func_ov143_0229a5a4(void *self)
{
    if (func_ov002_02209f64((char *) self + 0xac) == 0) {
        func_ov002_02208098(self, *(unsigned char *) ((char *) self + 0x9e));
        func_ov143_0229ac10(self);
    }
}
