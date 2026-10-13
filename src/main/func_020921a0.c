/* func_020921a0 @ 0x020921a0, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02094cf8(int, int, int, int, int, void *);
extern char data_020e2794[];
extern char data_020e27a0[];

int func_020921a0(int a, int b, int c, int d)
{
    int ret = 3;
    if (d != 0) {
        int i = 0;
        func_02094cf8(0x6c, a, b, c, d, data_020e2794);
        if (((short *) d)[i] >= 0xc00) {
            func_02094cf8(0x6d, a, b, c, d, data_020e27a0);
        }
        ret = 1;
    }
    return ret;
}
