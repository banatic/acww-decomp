/* func_020c3534 @ 0x020c3534, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_020c80f8;
extern void func_02019d0c(int a, int b, int c, int d, int e, int f, int g, int h, int i, int j, int k);

int func_020c3534(int param)
{
    func_02019d0c(param + 0x564, 2, 2, 0xf400, 0x14600, 0, 0, 0, 0, data_020c80f8, 0);
    return 1;
}
