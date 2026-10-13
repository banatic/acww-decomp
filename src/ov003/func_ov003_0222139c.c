/* func_ov003_0222139c @ 0x0222139c, 0x5c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int data_020ccf94;
extern int func_02073d90(int);
extern void func_ov003_022213f8(int *a, int b, int *c, int *d, int e, unsigned short f, short g, int h);

void func_ov003_0222139c(int *a, int b, int *c, int *d, int e, unsigned short f, short g, int h)
{
    int v2[2];
    int v3[3];

    if (func_02073d90(data_020ccf94) == 0) {
        b = 0;
    }

    v3[0] = d[0];
    v3[1] = d[1];
    v3[2] = d[2];

    v2[0] = c[0];
    v2[1] = c[1];

    func_ov003_022213f8(a, b, v2, v3, e, f, g, h);
}
