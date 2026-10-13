/* func_020adb24 @ 0x020adb24, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020984e8(void);
extern void func_02099870(void);
extern int func_02094ffc(void);
extern int func_020b65c4(void);
extern void func_020adb70(int, int, int, int, int, int, int);

void func_020adb24(int p)
{
    int flag;

    func_020984e8();
    func_02099870();
    if (func_02094ffc()) {
        flag = 0;
    } else {
        flag = 1;
    }
    if (p > 150000) {
        p = 150000;
    }
    func_020adb70(63, p, func_020b65c4(), flag, 0, 1, 0);
}
