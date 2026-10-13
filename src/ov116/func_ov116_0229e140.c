/* func_ov116_0229e140 @ 0x0229e140, 0x28 bytes, Thumb, module ov116
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02209f64(void *);
extern void func_ov002_02208098(void *, unsigned char);
extern void func_ov116_0229e5e8(void *);

void func_ov116_0229e140(void *self)
{
    if (func_ov002_02209f64((char *) self + 0x94) == 0) {
        func_ov002_02208098(self, *(unsigned char *) ((char *) self + 0x142c));
        func_ov116_0229e5e8(self);
    }
}
