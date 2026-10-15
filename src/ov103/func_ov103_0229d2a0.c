/* func_ov103_0229d2a0 @ 0x0229d2a0, 0x30 bytes, Thumb, module ov103
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov103_0229ce84(void *self, unsigned char value);
extern int func_ov002_02209f9c(void *self);
extern unsigned char *func_ov002_02208098(void *self, unsigned char value);

void func_ov103_0229d2a0(void *self)
{
    if (func_ov002_02209f9c((char *) self + 0x2274)) {
        func_ov103_0229ce84(self, ((unsigned char *) self)[0x2da4]);
        func_ov002_02208098(self, 0xf);
    }
}
