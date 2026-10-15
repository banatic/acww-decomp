/* func_ov004_0222c14c @ 0x0222c14c, 0x62 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#pragma opt_propagation off

extern void *func_02096718(int a);
extern int func_0200e828(void *arg0);
extern int func_02064594(short v);
extern int func_ov004_0222b214(void *p, int a, int b, int c, int e, int f, short g);

int func_ov004_0222c14c(int *a, int *b, short *c, short d, int mode)
{
    void *p = func_02096718(4);
    int n;
    int t;

    if (p != 0) {
        n = 6;
        if (n <= func_0200e828((void *) p)) {
            return 0;
        }
        t = (func_02064594((short) (*c - d)) == 1) ? 1 : 0;
        return func_ov004_0222b214(p, *a, *b, *c, t, 6, -1);
    }
    return 0;
}
