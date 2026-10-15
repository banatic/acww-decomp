/* func_ov120_0229c420 @ 0x0229c420, 0x1a bytes, Thumb, module ov120
 * mwccarm 1.2/base -O4,s
 */

extern __arm int func_020ee45c(void *arg);
extern void func_ov092_0229929c(int arg);
extern void func_ov120_0229bc54(void *arg);

int func_ov120_0229c420(void *arg)
{
    int ret;
    ret = func_020ee45c(arg);
    func_ov092_0229929c(ret);
    func_ov120_0229bc54(arg);
    return 1;
}
