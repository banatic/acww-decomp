/* func_ov125_022a0030 @ 0x022a0030, 0x30 bytes, Thumb, module ov125
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02209f64(void *);
extern int func_ov002_02208098(void *, unsigned char);
extern void func_ov125_022a0714(void *);

void func_ov125_022a0030(void *self)
{
    if (func_ov002_02209f64((char *) self + 0x644) == 0) {
        func_ov002_02208098(self, *(unsigned char *) ((char *) self + 0x87f));
        func_ov125_022a0714(self);
    }
}
