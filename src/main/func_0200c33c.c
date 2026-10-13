/* func_0200c33c @ 0x0200c33c, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02010f5c(int);
extern int func_02056f94(int);
extern void func_020109fc(int, int, int, int);

void func_0200c33c(int param)
{
    func_02010f5c(param);
    if (func_02056f94(param + 0x2d0)) {
        func_020109fc(param, 0, 3, 0);
    }
}
