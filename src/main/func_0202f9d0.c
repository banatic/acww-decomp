/* func_0202f9d0 @ 0x0202f9d0, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202fb28(int, int);
extern int func_0202f904(int, int, int, int);
extern int FX_MulFunc(int, int);

int func_0202f9d0(int a, int b, int c, int d)
{
    int e;
    int f;

    e = func_0202fb28(a, c);
    f = func_0202fb28(a, d);
    if (FX_MulFunc(e, f) < 0) {
        return func_0202f904(a, b, c, d);
    }
    return 0;
}
