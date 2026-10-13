/* func_ov113_0229aaa8 @ 0x0229aaa8, 0x3c bytes, Thumb, module ov113
 * mwccarm 1.2/base -O4,s
 */

extern void G2x_SetBlendBrightnessExt_(unsigned int a0, unsigned int a1, unsigned int a2, unsigned int a3, unsigned int a4,
                                       unsigned int a5);
extern void func_ov002_02208090(unsigned int a0, unsigned int a1);
extern void func_ov002_022080a0(unsigned int a0, unsigned int a1);
extern void func_ov113_0229a474(unsigned int a0);

int func_ov113_0229aaa8(unsigned int arg0)
{
    G2x_SetBlendBrightnessExt_(0x04000050, 0x1f, 0x20, 0x10, 0x10, 0);
    func_ov113_0229a474(arg0);
    func_ov002_02208090(arg0, 0);
    func_ov002_022080a0(arg0, 1);
    return 1;
}
