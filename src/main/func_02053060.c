/* func_02053060 @ 0x02053060, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02053314(int arg1, int arg2, int arg3, int arg4);

int func_02053060(int a, int b, int c, int d, unsigned char e)
{
    return func_02053314(a + (d << 5), b, c, e);
}
