/* func_ov122_022a0ad0 @ 0x022a0ad0, 0x2c bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02209f64(void *);
extern int func_ov002_02208098(void *, unsigned char);
extern void func_ov122_022a1f40(void *);

void func_ov122_022a0ad0(void *self)
{
    if (func_ov002_02209f64((char *) self + 0x4058) == 0) {
        func_ov002_02208098(self, *(unsigned char *) ((char *) self + 0xb4));
        func_ov122_022a1f40(self);
    }
}
