/* func_02009f48 @ 0x02009f48, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02056f94(int arg);
extern int func_02057d34(int arg);
extern int func_02057c20(int arg);
extern void func_02057d0c(int arg1, int arg2);
extern int func_02057bf0(int arg);
extern void func_02009ef4(int arg1, int arg2, int arg3);

void func_02009f48(int param)
{
    if (func_02056f94(param + 0x2d0) == 0) {
        return;
    }
    if (func_02057d34(param) == 0) {
        if (func_02057c20(param) != 1) {
            return;
        }
        func_02057d0c(3, param);
    }
    if (func_02057bf0(3) != 0) {
        return;
    }
    func_02009ef4(param, 6, -1);
}
