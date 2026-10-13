/* func_020980c4 @ 0x020980c4, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02066688(void);
extern void func_02066694(void);
extern void func_02138d6c(int, int, int, void (*)(void), void (*)(void));

int func_020980c4(int param)
{
    func_02138d6c(param, 10, 256, func_02066694, func_02066688);
    return param;
}
