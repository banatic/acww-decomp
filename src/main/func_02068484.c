/* func_02068484 @ 0x02068484, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021f43f8;
extern void func_0206844c(unsigned char *, int, int);

int func_02068484(unsigned char *p, int a, int b)
{
    int r = 0;
    if (p[0x1e77] == data_021f43f8) {
        func_0206844c(p, a, b);
        r = 1;
    }
    return r;
}
