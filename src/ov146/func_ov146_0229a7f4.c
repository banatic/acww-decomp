/* func_ov146_0229a7f4 @ 0x0229a7f4, 0x38 bytes, Thumb, module ov146
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e484(void *);
extern int func_ov146_02299a4c(void *, unsigned char);
extern void func_ov002_02208098(void *, int);
extern void func_ov146_0229a464(void *);

void func_ov146_0229a7f4(void *self)
{
    if (func_0208e484((char *) self + 0x15cc)) {
        if (func_ov146_02299a4c(self, *(unsigned char *) ((char *) self + 0xb2)) == 0) {
            func_ov002_02208098(self, 3);
            func_ov146_0229a464(self);
        }
    }
}
