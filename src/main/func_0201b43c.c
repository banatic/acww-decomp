/* func_0201b43c @ 0x0201b43c, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984e8(int a, int b);
extern int func_02099734(int a);
extern void func_02098a6c(int a, int b, int c, int d);

void func_0201b43c(int a, int b)
{
    int t1;
    int t2;
    t1 = func_020984e8(a, b);
    t2 = func_02099734(t1);
    func_02098a6c(t2, -b, 1, 0);
}
