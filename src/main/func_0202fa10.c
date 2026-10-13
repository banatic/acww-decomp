/* func_0202fa10 @ 0x0202fa10, 0x8c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020eaca0(void *dst, const void *src, unsigned int size);
extern int FX_MulFunc(int a, int b);

int func_0202fa10(void *src, unsigned int size)
{
    int v[3][3];
    int a, b, c;

    func_020eaca0(&v[0], (char *) src + 4, size);
    func_020eaca0(&v[1], (char *) src + 0x10, size);
    func_020eaca0(&v[2], (char *) src + 0x1c, size);

    a = FX_MulFunc(v[0][1], v[1][2]) - FX_MulFunc(v[0][2], v[1][1]);
    b = FX_MulFunc(v[1][1], v[2][2]) - FX_MulFunc(v[1][2], v[2][1]);
    c = FX_MulFunc(v[2][1], v[0][2]) - FX_MulFunc(v[2][2], v[0][1]);

    if ((a >= 0 && b >= 0 && c >= 0) || (a <= 0 && b <= 0 && c <= 0)) {
        return 1;
    }
    return 0;
}
