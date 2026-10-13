/* func_020b081c @ 0x020b081c, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020b0a80(void);
extern void func_02138c48(int, int, int, int);

int func_020b081c(int a)
{
    func_02138c48(a, 3, 6, (int) func_020b0a80);
    return a;
}
