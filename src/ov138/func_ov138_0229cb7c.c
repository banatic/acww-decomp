/* func_ov138_0229cb7c @ 0x0229cb7c, 0x26 bytes, Thumb, module ov138
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov138_0229d16c(void *);
extern int func_ov002_02209f64(void *);
extern void func_ov002_02208098(void *, unsigned char);

void func_ov138_0229cb7c(void *self)
{
    if (func_ov002_02209f64((char *) self + 0x98) == 0) {
        func_ov002_02208098(self, *(unsigned char *) ((char *) self + 0x94));
        func_ov138_0229d16c(self);
    }
}
