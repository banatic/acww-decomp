/* func_ov135_0229c878 @ 0x0229c878, 0x3c bytes, Thumb, module ov135
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov134_022999ac(void *ptr);
extern void func_ov134_02299980(void *ptr, int value);
extern void func_ov135_0229c564(void *ptr, int value);
extern void func_ov135_0229c7fc(void *ptr);
extern void func_ov002_02207fc0(void *ptr);
extern void func_ov002_02208098(void *ptr, int value);

void func_ov135_0229c878(char *param)
{
    int result;
    result = func_ov134_022999ac(param + 0x2c8);
    func_ov134_02299980(param + 0x2c8, result);
    func_ov135_0229c564(param, 2);
    func_ov135_0229c7fc(param);
    func_ov002_02207fc0(param);
    func_ov002_02208098(param, 7);
}
