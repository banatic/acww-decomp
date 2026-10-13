/* func_ov131_0229b24c @ 0x0229b24c, 0x28 bytes, Thumb, module ov131
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov131_0229b644(void *self);
extern int func_ov002_02209f64(void *self);
extern int func_ov002_02208098(void *self, unsigned char value);

void func_ov131_0229b24c(void *self)
{
    if (func_ov002_02209f64((char *) self + 0x94) == 0) {
        func_ov002_02208098(self, *(unsigned char *) ((char *) self + 0x1556));
        func_ov131_0229b644(self);
    }
}
