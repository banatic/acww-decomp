/* func_02036b34 @ 0x02036b34, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020356c4(int, int, int, int);

void func_02036b34(int r0, int r1)
{
    int r5 = r0;
    int r4 = r1;
    func_020356c4(0x23, r4, 0x7f, 0);
    *(unsigned short *) (r5 + 0x10) = (unsigned short) r4;
}
