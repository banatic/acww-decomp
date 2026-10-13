/* func_020831a4 @ 0x020831a4, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02083148(int a, int b, unsigned short *ptr);

int func_020831a4(int a, int b)
{
    unsigned short tmp = 0xfff1;
    return func_02083148(a, b, &tmp);
}
