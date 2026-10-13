/* func_02060b18 @ 0x02060b18, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02060b48(int a, unsigned short *b);

int func_02060b18(int a)
{
    unsigned short val = 0xfff1;
    return func_02060b48(a, &val);
}
