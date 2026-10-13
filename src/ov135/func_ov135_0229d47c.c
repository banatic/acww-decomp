/* func_ov135_0229d47c @ 0x0229d47c, 0x1a bytes, Thumb, module ov135
 * mwccarm 1.2/base -O4,s
 */

extern int func_020ee45c(int a);
extern int func_ov092_0229929c(int a);
extern void func_ov135_0229d0c8(int a);

int func_ov135_0229d47c(int a)
{
    int saved = a;
    int ret;

    ret = func_020ee45c(a);
    func_ov092_0229929c(ret);
    func_ov135_0229d0c8(saved);

    return 1;
}
