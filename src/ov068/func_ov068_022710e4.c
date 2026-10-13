/* func_ov068_022710e4 @ 0x022710e4, 0x7c bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov003_02219cb4(int *p);
extern int *func_020961a8(int n);
extern int FX_Div(int a, int b);
extern int func_020644cc(int n);

int func_ov068_022710e4(int *self)
{
    int *p;
    int *q;
    p = (int *) ((char *) self + 0x204);
    if (func_ov003_02219cb4(p) && (q = func_020961a8(4)) != 0) {
        if (*p < q[23]) {
            *p = *p - FX_Div(0x14000, 0x10000);
        } else {
            *p = *p + FX_Div(0x14000, 0x10000);
        }
        if (func_020644cc(0x64) > 50) {
            *((char *) self + 0x24c) = 0;
        } else {
            *((char *) self + 0x24c) = 1;
        }
        return 1;
    }
    return 0;
}
