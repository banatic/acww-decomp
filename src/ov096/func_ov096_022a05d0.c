/* func_ov096_022a05d0 @ 0x022a05d0, 0x2c bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e484(void *);
extern void func_ov002_02208098(void *, int);
extern int func_ov096_0229ea5c(void *);

int func_ov096_022a05d0(char *self)
{
    if (func_0208e484(self + 0x2500)) {
        func_ov002_02208098(self, *(unsigned char *) (self + 0xba));
    }
    return func_ov096_0229ea5c(self);
}
