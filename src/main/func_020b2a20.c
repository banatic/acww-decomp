/* func_020b2a20 @ 0x020b2a20, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b2a60(int, int, int);
extern void func_020b2a10(int, int, int);

void func_020b2a20(int a, int b, int c)
{
    int ret = func_020b2a60(a, b, c);
    func_020b2a10(ret, b, c);
}
