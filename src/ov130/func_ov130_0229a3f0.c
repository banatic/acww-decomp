/* func_ov130_0229a3f0 @ 0x0229a3f0, 0xd8 bytes, Thumb, module ov130
 * mwccarm 1.2/base -O4,s
 */

extern void *data_021fbe94;
extern char data_ov130_0229ac30[];
extern char data_ov130_0229ac44[];
extern char data_ov130_0229ac58[];
extern char data_ov130_0229ac6c[];
extern void *data_ov130_0229a980[];

extern int func_02002d14(void *t, void *g, int a, int b, int c, int d);
extern int func_02002c6c(void *t, void *g, int a, int b, int c, int d);
extern void *func_02064b2c(void *t, void *g, int a, int *out);
extern int func_02002a88(void *p, int a, int b, int c, int d);
extern void func_020e993c(void *g, void *h);
extern int func_02002cd8(void *t, void *g, int a, int b, int c);

int func_ov130_0229a3f0(int a)
{
    void *g;
    void *h;
    char *p;
    int i;
    int k;
    int tmp;

    g = data_021fbe94;
    func_02002d14(data_ov130_0229ac30, g, 8, 4, 4, 0xe);
    func_02002c6c(data_ov130_0229ac44, g, 8, 0xc0, 0xc0, 0x15f);
    func_02002c6c(data_ov130_0229ac58, g, 8, 0x160, 0x160, 0x1ff);
    h = func_02064b2c(data_ov130_0229a980[a / 5], g, -4, &tmp);
    p = (char *) h + (a % 5) * 0xc0;
    k = 0x15a;
    for (i = 0; i < 6; i++) {
        func_02002a88(p, 8, k, k, k + 5);
        p = p + 0x400;
        k = k + 0x20;
    }
    func_020e993c(g, h);
    return func_02002cd8(data_ov130_0229ac6c, g, 8, a, 4);
}
