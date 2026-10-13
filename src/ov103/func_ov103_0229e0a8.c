/* func_ov103_0229e0a8 @ 0x0229e0a8, 0x1a bytes, Thumb, module ov103
 * mwccarm 1.2/base -O4,s
 */

extern int func_020ee45c(void *arg);
extern void func_ov092_0229929c(int arg);
extern void func_ov103_0229d960(void *arg);

int func_ov103_0229e0a8(void *arg)
{
    int ret;

    ret = func_020ee45c(arg);
    func_ov092_0229929c(ret);
    func_ov103_0229d960(arg);
    return 1;
}
