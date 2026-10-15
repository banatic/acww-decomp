/* func_ov140_0229a460 @ 0x0229a460, 0x40 bytes, Thumb, module ov140
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov140_02299fb0(const char *a, int b);
extern int func_020b9bbc(const char *a, const char *b, int c, int d, int e);
extern void func_ov140_02299f90(const char *a, int b);

void func_ov140_0229a460(char *arg)
{
    if (!func_ov140_02299fb0(arg, 4)) {
        return;
    }
    if (!func_020b9bbc(arg + 0x14bc, arg + 0xac, 6, 0x800, 0)) {
        return;
    }
    func_ov140_02299f90(arg, 4);
}
