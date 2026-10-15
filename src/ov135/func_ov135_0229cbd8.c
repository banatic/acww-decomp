/* func_ov135_0229cbd8 @ 0x0229cbd8, 0x26 bytes, Thumb, module ov135
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02209f64(void *);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov135_0229d268(void *);

void func_ov135_0229cbd8(void *self)
{
    if (func_ov002_02209f64((char *) self + 0x98) == 0) {
        func_ov002_02208098((void *) (self), *(unsigned char *) ((char *) self + 0x94));
        func_ov135_0229d268(self);
    }
}
