/* func_0209a204 @ 0x0209a204, 0xe6 bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

extern int FX_MulFunc(int, int);

void func_0209a204(int *a, int *b, int *out)
{
    int out0, out1, out2, out3;
    int t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15;

    t0 = FX_MulFunc(a[3], b[3]);
    t1 = FX_MulFunc(a[0], b[0]);
    t2 = FX_MulFunc(a[1], b[1]);
    t3 = FX_MulFunc(a[2], b[2]);
    out3 = t0 - t1 - t2 - t3;

    t4 = FX_MulFunc(a[1], b[2]);
    t5 = FX_MulFunc(a[3], b[0]);
    t6 = FX_MulFunc(a[0], b[3]);
    t7 = FX_MulFunc(a[2], b[1]);
    out0 = (t5 + t6) + t4 - t7;

    t8 = FX_MulFunc(a[2], b[0]);
    t9 = FX_MulFunc(a[3], b[1]);
    t10 = FX_MulFunc(a[1], b[3]);
    t11 = FX_MulFunc(a[0], b[2]);
    out1 = (t9 + t10) + t8 - t11;

    t12 = FX_MulFunc(a[0], b[1]);
    t13 = FX_MulFunc(a[3], b[2]);
    t14 = FX_MulFunc(a[2], b[3]);
    t15 = FX_MulFunc(a[1], b[0]);
    out2 = (t13 + t14) + t12 - t15;

    out[0] = out0;
    out[1] = out1;
    out[2] = out2;
    out[3] = out3;
}
