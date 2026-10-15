/* func_0203710c @ 0x0203710c, 0x84 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_020da24c;
extern unsigned short data_020da248;
extern unsigned short data_020da250;

extern int func_02036648(void);
extern int func_020373c8(int h, int a, int b, int c, int d);
extern char *func_02137550(short *p, int n);
extern int func_02037404(int h, short *a, short *b);
extern void func_020371ac(void *self, int v);
extern void func_02037190(void *self);

void func_0203710c(void *self)
{
    int h;
    int ok;
    short x[2];
    short y[2];

    h = func_02036648();
    ok = func_020373c8(h, 0x3b, 0x32, 0, 0x10);
    x[0] = data_020da24c;
    x[1] = data_020da248;
    y[0] = data_020da250;
    func_02137550(&y[1], 2);
    if (func_02037404(h, &x[0], &y[0]) || func_02037404(h, &x[1], &y[1])) {
        ok = 0;
    }
    if (ok) {
        func_020371ac(self, 0xc8);
    } else {
        func_02037190(self);
    }
}
