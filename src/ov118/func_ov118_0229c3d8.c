/* func_ov118_0229c3d8 @ 0x0229c3d8, 0x2c bytes, Thumb, module ov118
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov118_0229be6c(int);
extern void func_ov002_02208090(int, int);
extern int func_ov118_0229a460(int, int);
extern void func_ov118_0229c3ac(int);

void func_ov118_0229c3d8(int arg)
{
    func_ov118_0229be6c(arg);
    func_ov002_02208090(arg, 2);
    if (func_ov118_0229a460(arg, 0x2000) == 0) {
        func_ov118_0229c3ac(arg);
    }
}
