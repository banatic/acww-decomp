/* func_0204864c @ 0x0204864c, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020644cc(int);
extern int func_02048cb8(int, int, int, int, int, int (*predicate)(int, int, int), int);
extern int func_02048f6c(void *, int, int);

void func_0204864c(int p1, int p2, int p3, int p4)
{
    int a = func_020644cc(p3);
    int b = func_020644cc(p4);
    int c = func_020644cc(100);
    func_02048cb8(p1, p2, a + 1, b + 1, (c < 2) ? 0x20 : 0x1f, (((int (*)(int, int, int)) func_02048f6c)), 0);
}
