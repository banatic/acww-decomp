/* func_ov146_0229a82c @ 0x0229a82c, 0x2c bytes, Thumb, module ov146
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02209f64(void *);
extern void func_ov002_02208098(void *, unsigned char);
extern void func_ov146_0229af2c(void *);

void func_ov146_0229a82c(void *self)
{
    if (func_ov002_02209f64((char *) self + 0x15cc) != 0) {
        return;
    }
    func_ov002_02208098(self, ((unsigned char *) self)[0xb3]);
    func_ov146_0229af2c(self);
}
