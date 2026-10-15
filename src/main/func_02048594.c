/* func_02048594 @ 0x02048594, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020485d4(void *dst, int src, int, int);
extern int func_02048cb8(int a, int b, int c, int d, int e, int (*predicate)(int, int, int), int g);
extern int func_02048ee4(void *, int, int);

void func_02048594(int p0, int p1, int argument2, int argument3)
{
    struct {
        int x;
        int y;
    } s;
    int a, b;

    func_020485d4(&s, p0, (int) argument2, (int) argument3);
    a = s.x;
    b = s.y;
    if (a == -1) {
        return;
    }
    func_02048cb8(p0, p1, a + 1, b + 1, 26, (((int (*)(int, int, int)) func_02048ee4)), 0);
}
