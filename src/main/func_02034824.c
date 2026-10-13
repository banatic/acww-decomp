/* func_02034824 @ 0x02034824, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02138d6c(int, int, int, void (*)(void), void (*)(void));
extern void func_02034714(int);
extern void func_02034820(void);
extern void func_02034850(void);

int func_02034824(int param)
{
    func_02138d6c(param, 0x24, 8, func_02034850, func_02034820);
    func_02034714(param);
    return param;
}
