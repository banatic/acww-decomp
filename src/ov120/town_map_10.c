/* town_map_10: 2 functions, module ov120
 * mwccarm 1.2/base -O4,s
 * func_ov120_0229c43c @ 0x0229c43c, 0x20 bytes, Thumb
 * func_ov120_0229c420 @ 0x0229c420, 0x1a bytes, Thumb
 */

extern void func_ov120_0229bc74(void *);
extern void func_ov002_02208090(void *, int);
extern unsigned char *func_ov002_022080a0(void *, unsigned char value);
extern __arm int func_020ee45c(void *arg);
extern void func_ov092_0229929c(int arg);
extern void func_ov120_0229bc54(void *arg);

int func_ov120_0229c43c(void *arg)
{
    func_ov120_0229bc74(arg);
    func_ov002_02208090(arg, 0);
    func_ov002_022080a0(arg, 1);
    return 1;
}

int func_ov120_0229c420(void *arg)
{
    int ret;
    ret = func_020ee45c(arg);
    func_ov092_0229929c(ret);
    func_ov120_0229bc54(arg);
    return 1;
}
