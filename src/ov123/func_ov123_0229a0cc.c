/* func_ov123_0229a0cc @ 0x0229a0cc, 0x7c bytes, Thumb, module ov123
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov123_0229ae7c(void);
extern int func_ov123_0229ae74(int *a, int b);
extern int func_ov123_02299650(int *a, int b);
extern void func_02088df8(int a, int *b, int c, int d, int e, int f, int g, int h, int i, int j, int k, int l);
extern int *data_ov123_0229cfec[];
extern int data_ov123_0229ce90[];

void func_ov123_0229a0cc(int *p0, int p1, int p2, int p3)
{
    int res1, res2;
    unsigned char b;
    int *ptr;

    res1 = func_ov123_0229ae7c();
    res2 = func_ov123_0229ae74(p0, p2);
    b = ((unsigned char *) p0)[0xa4];
    ptr = data_ov123_0229cfec[b];
    if (func_ov123_02299650(p0, 0x800) != 0) {
        ptr = data_ov123_0229ce90;
    }
    if (((unsigned char *) p0)[0xa4] == 1) {
        res1 -= 2;
        res2 -= 2;
    }
    if (ptr != 0) {
        func_02088df8(1, ptr, res1, res2, -1, -1, 0x1000, 0x1000, 0, -1, 0, 0);
    }
}
