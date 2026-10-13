/* func_020900ac @ 0x020900ac, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02138d6c(int, int, int, int, int);

extern void func_020901a0(void);
extern void func_020901d8(void);

int func_020900ac(int arg)
{
    func_02138d6c(arg, 3, 0x950, (int) (unsigned int) func_020901d8, (int) (unsigned int) func_020901a0);
    return arg;
}
