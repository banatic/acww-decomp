/* func_02086034 @ 0x02086034, 0x84 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020984e8(void *);
extern void func_02099870(void *);
extern int func_020951bc(void);
extern int func_02099020(void *, int);
extern int func_0203cc38(void);
extern int func_0203cc1c(void);
extern void func_0209e474(void *);
extern void MI_CpuCopy8(void *, void *, unsigned int);
extern int func_0203fc78(int, void *, int);
extern void func_020860f0(void *, int);

void func_02086034(void *arg)
{
    void *a;
    void *p;
    int zero[2];
    char buf[8];

    a = arg;
    p = func_020984e8(a);
    if (p == 0) {
        return;
    }
    func_02099870(p);
    if (func_020951bc() == 0) {
        return;
    }
    if (func_02099020(p, 1) != 0) {
        return;
    }
    if (func_02099020(p, 0x21) != 0 || func_0203cc38() == 0) {
        if (func_02099020(p, 0x22) != 0) {
            return;
        }
        if (func_0203cc1c() == 0) {
            return;
        }
    }
    zero[0] = 0;
    zero[1] = 0;
    func_0209e474(zero);
    MI_CpuCopy8(zero, buf, 8);
    if (func_0203fc78(8, buf, 0) != 0) {
        return;
    }
    func_020860f0(a, 8);
}
