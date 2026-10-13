/* func_02088318 @ 0x02088318, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984e8(void);
extern int func_02099688(void);
extern void MI_CpuCopy8(char *p, int a, int b);
extern int func_020882dc(char *p);
extern int func_020e8b0c(int a, int b, int c);
extern void func_02098fd0(int a, int b);
extern char data_021dc7a8[];

void func_02088318(void)
{
    int a;
    int b;
    int c;
    char *base;

    base = (char *) data_021dc7a8;
    a = func_020984e8();
    if (a == 0 || base == 0) {
        return;
    }
    b = func_02099688();
    MI_CpuCopy8(base + 0x173e2, b, 0x10);
    c = func_020882dc(base + 0x173e2);
    if (func_020e8b0c(c, 1, 7) == 0) {
        func_02098fd0(a, 0x33);
    }
}
