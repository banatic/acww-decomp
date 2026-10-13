/* func_02017cac @ 0x02017cac, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02057bf0(int);
extern unsigned short data_020c80f8;
extern void func_02016764(char *p1, char *p2, int p3, int p4, int p5, int p6, int p7, int p8);

void func_02017cac(char *a, char *b)
{
    if (func_02057bf0(1) != 0) {
        return;
    }
    func_02016764(b + 0x334, b, 0x2c, data_020c80f8, 1, 0x1000, 0, 0);
    *(a + 0x98) = 0xf;
}
