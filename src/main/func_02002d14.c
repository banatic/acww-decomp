/* func_02002d14 @ 0x02002d14, 0x3a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02064b2c(int, int, int, int);
extern int func_02002bd0(int, int, int, unsigned char, unsigned char);
extern void func_020e993c(int, int);

int func_02002d14(int a0, int a1, int a2, int a3, unsigned char a4, unsigned char a5)
{
    int t1, t2;
    t1 = func_02064b2c(a0, a1, ~3, 0);
    t2 = func_02002bd0(t1, a2, a3, a4, a5);
    func_020e993c(a1, t1);
    return t2;
}
