/* func_0207d4bc @ 0x0207d4bc, 0x84 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern short data_021dc7aa;

extern int func_0208150c(void *p);
extern int func_02003704(int h);
extern void *func_020984e8(void);
extern void *func_02099870(void *a);
extern int func_020951bc(void *m);
extern int func_02094ffc(void *m);
extern void *func_020807a8(void *p, void *m);
extern void *func_02099158(void *a);
extern int func_02081d20(void *e);
extern int func_02099d08(void *a, int b, int c, int d);

int func_0207d4bc(void *p0, void *p1)
{
    int t;
    void *a;
    void *m;
    void *e;
    int h;

    a = p1;
    if (func_02003704(func_0208150c(p0)) == 0) {
        goto zero;
    }
    t = (int) &data_021dc7aa;
    if (a == 0) {
        a = func_020984e8();
    }
    if (a == 0) {
        goto zero;
    }
    if (t == 0) {
        goto zero;
    }
    m = func_02099870(a);
    if (func_020951bc(m) == 0) {
        goto zero;
    }
    if (func_02094ffc(m) != 1) {
        goto zero;
    }
    e = func_020807a8(p0, m);
    if (e == 0) {
        goto zero;
    }
    a = func_02099158(a);
    h = func_0208150c(p0);
    return func_02099d08(a, h, func_02081d20(e), t);
zero:
    return 0;
}
