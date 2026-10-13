/* func_02061118 @ 0x02061118, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02060a90(int arg);
extern void func_02061444(void);
extern void func_02138c48(int a, int b, int c, void (*d)(void));

int func_02061118(int arg)
{
    func_02060a90(arg + 0x1594);
    func_02138c48(arg, 5, 0x450, func_02061444);
    return arg;
}
