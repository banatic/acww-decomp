/* func_ov105_0229e0d0 @ 0x0229e0d0, 0x40 bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e484(void *ptr);
extern void func_ov105_0229cd9c(void *ptr);
extern void func_ov002_02208098(void *ptr, int n);

void func_ov105_0229e0d0(void *self)
{
    if (func_0208e484((char *) self + 0x24a4) != 0) {
        func_ov105_0229cd9c(self);
        if (*(unsigned char *) ((char *) self + 0x2b4) == 1) {
            func_ov002_02208098(self, 8);
        } else {
            func_ov002_02208098(self, 7);
        }
    }
}
