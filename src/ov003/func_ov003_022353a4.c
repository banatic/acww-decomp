/* func_ov003_022353a4 @ 0x022353a4, 0x3c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov003_0223522c(int kind);
extern void func_02004290(void *a, int b);
extern void func_020042a0(void *a, int b);

void func_ov003_022353a4(char *self, int b, int c)
{
    int k = func_ov003_0223522c(*(signed char *) (self + 0x24d));
    if (k >= 0) {
        if (c) {
            func_02004290(self + 0x174, k);
        } else {
            func_020042a0(self + 0x174, k);
        }
    }
}
