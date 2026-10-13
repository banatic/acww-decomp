/* func_ov003_02230f88 @ 0x02230f88, 0x104 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int FX_Div(int a, int b);

void func_ov003_02230f88(char *self)
{
    int *p;
    int *a;
    int *b;

    p = (int *) (self + 0x204);
    a = (int *) (self + 0x1b0);
    b = (int *) (self + 0x1bc);
    if (*(signed char *) (self + 0x24d) == 0x33) {
        a[0] = p[0] - FX_Div(0x6000, 0x10000);
        a[1] = FX_Div(0xa000, 0x10000);
        a[2] = p[2] - FX_Div(0x4000, 0x10000);
        b[0] = p[0] + FX_Div(0x6000, 0x10000);
        b[1] = FX_Div(0xc000, 0x10000);
        b[2] = p[2] + FX_Div(0x4000, 0x10000);
    } else if (*(signed char *) (self + 0x24d) == 0x19) {
        a[0] = p[0] - 0x6000;
        a[2] = p[2] + 0x6000;
        b[0] = p[0] + 0x6000;
        b[2] = p[2] - 0x6000;
    } else {
        a[0] = p[0] - FX_Div(0x9000, 0x10000);
        a[1] = FX_Div(0x9000, 0x10000);
        a[2] = p[2] - FX_Div(0x2000, 0x10000);
        b[0] = p[0] + FX_Div(0x9000, 0x10000);
        b[1] = 0x1000;
        b[2] = p[2] + FX_Div(0x5000, 0x10000);
    }
}
