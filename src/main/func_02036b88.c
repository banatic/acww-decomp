/* func_02036b88 @ 0x02036b88, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020356c4(int, int, int, int);

void func_02036b88(short *ptr, int value)
{
    short *p = ptr;
    int v = value;
    func_020356c4(0x20, v, 0x7f, 0);
    p[5] = (short) v;
}
