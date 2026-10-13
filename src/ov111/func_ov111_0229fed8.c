/* func_ov111_0229fed8 @ 0x0229fed8, 0x88 bytes, Thumb, module ov111
 * mwccarm 1.2/base -O4,s
 */

extern int *data_021fbe94;
extern int data_ov111_022a0f78[];
extern void *func_02064b2c(int, int *, int, int);
extern void MI_CpuCopy8(char *, char *, int);
extern void func_0206fd60(char *, int, int, int, int, int, int);
extern void func_020e993c(int *, void *);
extern void func_ov095_0229bf70(char *);

void func_ov111_0229fed8(char *p, int n)
{
    char *res;
    int *g;
    char *base;

    g = data_021fbe94;
    res = func_02064b2c((n == 0) ? data_ov111_022a0f78[0] : data_ov111_022a0f78[n - 1], g, -4, 0);
    base = p + 0x24d4;
    MI_CpuCopy8(res + 0x100, base + 0x100, 0x140);

    if (n == 1) {
        func_0206fd60(base, 0, 4, 0x1f, 9, 5, 6);
    }

    func_020e993c(g, res);
    p += 0xac;
    func_ov095_0229bf70(p);
}
