/* func_020bdd9c @ 0x020bdd9c, 0x88 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209df64(void *p);
extern void func_0209def4(void *p);
extern int func_0209dcdc(void *p, void *q);
extern int FX_Div(int a, int b);

int func_020bdd9c(void)
{
    unsigned char buf[8];
    int value;
    int shifted;
    int quotient;
    int c;

    buf[2] = 1;
    buf[3] = 1;
    buf[4] = 0;
    buf[5] = 0;
    func_0209df64(&buf[6]);
    func_0209def4(&buf[0]);
    value = func_0209dcdc(&buf[6], &buf[2]);
    if (buf[1] < 12) {
        value--;
    }
    if (value < 0) {
        value = 0;
    }
    value = value * 100 + 0x974;
    shifted = (value % 0xb89) << 12;
    quotient = shifted / 100;
    c = FX_Div(quotient, 0x1d87b);
    c = c * 28 - 0x800;
    c = c >> 12;
    if (c < 0) {
        c = 0x1b;
    }
    if (c > 0x1b) {
        c = 0x1b;
    }
    return c + 3;
}
