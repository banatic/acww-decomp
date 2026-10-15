/* func_020b141c @ 0x020b141c, 0x26 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b15b0(void);
extern void func_02051c08(int a, int b, int c);

void func_020b141c(int a, int b)
{
    int t = func_020b15b0();
    func_02051c08(a, t + b * 74 + 30, 6);
}
