/* func_0202ea80 @ 0x0202ea80, 0x46 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984e8(int a, int b);
extern int func_0209967c(int a);
extern int func_020887c0(int a, int b);
extern int func_0208878c(int a, int b);

int func_0202ea80(int p0, int p1)
{
    int r;
    int x;
    int ok;

    r = func_020984e8(p0, p1);
    if (!r) {
        return 0;
    }

    x = func_0209967c(r);
    ok = 1;
    if (func_020887c0(x, p0) == 0) {
        ok = 0;
    }

    if (p1 != 0) {
        func_0208878c(x, p0);
    }

    if (ok) {
        return 1;
    }
    return 0;
}
