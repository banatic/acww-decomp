/* func_020b19e4 @ 0x020b19e4, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02138d6c(int a, int b, int c, void (*f1)(void), void (*f2)(void));
extern void func_020b1a54(void);
extern void func_020b1a64(void);

int func_020b19e4(int arg)
{
    func_02138d6c(arg, 0x10, 0x4A, func_020b1a64, func_020b1a54);
    return arg;
}
