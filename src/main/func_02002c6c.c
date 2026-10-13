/* func_02002c6c @ 0x02002c6c, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02064b2c(int, int, int, int *);
extern int func_02002a88(int, int, int, int, int);
extern void func_020e993c(int, int);

int func_02002c6c(int p1, int p2, int p3, int p4, int p5, int p6)
{
    int temp[2];
    int s;
    int r;

    s = func_02064b2c(p1, p2, ~3, temp);
    r = func_02002a88(s, p3, p4, p5, p6);
    func_020e993c(p2, s);
    return r;
}
