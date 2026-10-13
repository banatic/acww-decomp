/* func_ov004_022183b8 @ 0x022183b8, 0x5c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_020ea6e0(int *u, int a);
extern void VEC_Add(int *a, int *b, int *d);

void func_ov004_022183b8(int a0, int *dst, int *src, int a3, int *opt)
{
    struct {
        int t[3];
        int u[3];
    } s;

    dst[0] = src[0];
    dst[1] = src[1];
    dst[2] = src[2];
    s.t[0] = 0;
    s.t[1] = 0;
    s.t[2] = 0;
    if (opt != 0) {
        s.t[0] = opt[0];
        s.t[1] = opt[1];
        s.t[2] = opt[2];
    }
    s.u[0] = s.t[0];
    s.u[1] = s.t[1];
    s.u[2] = s.t[2] + 0x1000;
    func_020ea6e0(s.u, a3);
    VEC_Add(dst, s.u, dst);
}
