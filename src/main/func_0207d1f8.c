/* func_0207d1f8 @ 0x0207d1f8, 0x80 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208150c(void *a, void *b);
extern int func_02003704(int x);
extern void *func_020984e8(void);
extern int func_02099870(void *b);
extern int func_020951bc(int x);
extern int func_02099020(void *b, int n);
extern int func_0207d278(void *a);
extern int func_020807a8(void *a, int x);
extern int func_02081d20(void);
extern int func_020644cc(int n);
extern void func_0207d0f0(void *a, int n);

void func_0207d1f8(void *a, void *b)
{
    int x;
    int r4;
    int t;
    x = func_0208150c(a, b);
    if (func_02003704(x) == 0) {
        return;
    }
    r4 = 0;
    if (b == 0) {
        b = func_020984e8();
    }
    if (b != 0) {
        if (func_020951bc(func_02099870(b)) != 0 && func_02099020(b, 1) == 0 && func_0207d278(a) != 0 &&
            func_020807a8(a, func_02099870(b)) != 0) {
            t = func_02081d20();
            r4 = func_020644cc(3) * ((t + 0x100) >> 7);
        }
    }
    func_0207d0f0(a, r4);
}
