/* func_020b2a20 @ 0x020b2a20, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b2a60(int);
extern unsigned int func_020b2a10(int, int, int);

unsigned int func_020b2a20(int a, int b, int c)
{
    int ret = func_020b2a60(a);
    return func_020b2a10(ret, b, c);
}
