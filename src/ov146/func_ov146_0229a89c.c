/* func_ov146_0229a89c @ 0x0229a89c, 0x50 bytes, Thumb, module ov146
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov146_02299ba8(void);
extern int func_ov146_0229a5e8(void *self);
extern int func_ov146_0229a59c(void *self);
extern void func_ov146_02299c34(void *self);
extern void func_ov002_0220a0b4(void *self, int a, int b);
extern void func_ov002_02208098(void *self, int a);

extern unsigned short data_021fbe40;

void func_ov146_0229a89c(void *self)
{
    if ((data_021fbe40 & 1) != 0) {
        func_ov146_02299ba8();
        func_ov002_0220a0b4((char *) self + 0x15cc, func_ov146_0229a5e8(self), func_ov146_0229a59c(self));
    } else {
        func_ov146_02299c34(self);
        func_ov002_02208098(self, 5);
    }
}
