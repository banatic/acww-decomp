/* func_ov138_0229d04c @ 0x0229d04c, 0x30 bytes, Thumb, module ov138
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207f3c(void *a, int b);
extern void func_020027f0(int a);
extern int func_ov002_022080a0(void *a, int b);
extern int func_ov138_0229d02c(void *a);

int func_ov138_0229d04c(void *arg)
{
    if (func_ov002_02207f3c(arg, 0)) {
        func_020027f0(6);
        func_020027f0(4);
        return func_ov002_022080a0(arg, 5);
    } else {
        return func_ov138_0229d02c(arg);
    }
}
