/* func_ov129_0229cbdc @ 0x0229cbdc, 0x2c bytes, Thumb, module ov129
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02209f64(void *p);
extern void func_ov002_02208098(void *p, unsigned char c);
extern void func_ov129_0229d780(void *p);

void func_ov129_0229cbdc(void *self)
{
    if (func_ov002_02209f64((char *) self + 0x3a0) == 0) {
        func_ov002_02208098(self, *((unsigned char *) self + 0xac));
        func_ov129_0229d780(self);
    }
}
