/* func_ov116_0229e0c0 @ 0x0229e0c0, 0x28 bytes, Thumb, module ov116
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e484(void *);
extern void func_ov116_0229de10(void *);
extern void func_ov002_02208098(void *, unsigned char);

void func_ov116_0229e0c0(void *self)
{
    if (func_0208e484((char *) self + 0x94)) {
        func_ov116_0229de10(self);
        func_ov002_02208098(self, *(unsigned char *) ((char *) self + 0x142c));
    }
}
