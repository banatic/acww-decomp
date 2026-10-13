/* func_0203b0b8 @ 0x0203b0b8, 0x78 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020eaca0(void *out, void *a, void *b);
extern void func_01ffd070(void *out, void *a, void *b);
extern void func_020eaad0(void *out, void *in, int scale);
extern int VEC_Mag(void *v);
extern int FX_MulFunc(int a, int b);
extern int data_020da718;

int func_0203b0b8(int *a, int *b, int *out, int *extra)
{
    int ret;
    volatile int d[3];
    int e[3];
    func_020eaca0((void *) d, a, b);
    e[0] = d[0];
    e[1] = d[1];
    e[2] = d[2];
    e[2] = FX_MulFunc(d[2], data_020da718);
    ret = VEC_Mag(e);
    if (out != 0) {
        int t[3];
        int r[3];
        func_01ffd070(t, a, b);
        func_020eaad0(r, t, 1);
        out[0] = r[0];
        out[1] = r[1];
        out[2] = r[2];
        if (extra != 0) {
            int v = d[2] >> 1;
            if (v < 0) {
                v = -v;
            }
            *extra = v;
        }
    }
    return ret;
}
