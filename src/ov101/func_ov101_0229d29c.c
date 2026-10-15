/* func_ov101_0229d29c @ 0x0229d29c, 0x28 bytes, Thumb, module ov101
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e484(void *);
extern void func_ov101_0229c680(void *);
extern unsigned char *func_ov002_02208098(void *, unsigned char value);

void func_ov101_0229d29c(void *self)
{
    if (func_0208e484((char *) self + 0x229c)) {
        func_ov101_0229c680(self);
        func_ov002_02208098(self, 6);
    }
}
