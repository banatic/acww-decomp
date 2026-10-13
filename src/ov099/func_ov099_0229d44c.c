/* func_ov099_0229d44c @ 0x0229d44c, 0x50 bytes, Thumb, module ov099
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e484(void *);
extern void func_ov002_02209114(void *, unsigned char, int);
extern void func_ov002_02208098(void *, int);

void func_ov099_0229d44c(void *self)
{
    if (func_0208e484((unsigned char *) self + 0x2274)) {
        func_ov002_02209114((unsigned char *) self + 0x22d8, *((unsigned char *) self + 0x290c), 1);
        *((unsigned char *) self + 0x290b) = *((unsigned char *) self + *((unsigned char *) self + 0x290c) + 0x26c5);
        func_ov002_02208098(self, 18);
    }
}
