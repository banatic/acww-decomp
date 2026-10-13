/* func_020089b0 @ 0x020089b0, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0200d4e8(int a, int b, int c, int d);

void func_020089b0(int param)
{
    if (!((*(volatile unsigned short *) 0x027fffa8 & 0x8000) >> 15)) {
        func_0200d4e8(param, 3, 1, -1);
    }
}
