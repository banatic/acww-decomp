/* func_ov003_02226604 @ 0x02226604, 0x218 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void *data_ov003_0223cf70;
extern void *data_ov003_02236dac[][2];

extern int func_0204cab4(void);

extern void func_ov003_022269b0(void *g, int *a, int *b, int *c, int *d, int *e, int *f);
extern int func_ov003_0222703c(void *g, int *a, int *b);
extern int func_ov003_02226f5c(void *g, int *c, int *d, int *e, int *f);
extern int func_ov003_02226e78(void *g, int *a, int *e, void *p);
extern int func_ov003_02226cc4(void *g, int *a, int *c, void *p);
extern int func_ov003_02226a88(void *g, int *a, int *e, void *p);
extern void func_ov003_02226900(void *g, int *b, int *d, int *f);

extern void func_ov003_0222698c(void *g, int *a, int *b, int *c, int *d, int *e, int *f);
extern int func_ov003_02227000(void *g, int *a, int *b);
extern int func_ov003_02226f18(void *g, int *a, int *b, int *c, int *d);
extern int func_ov003_02226e30(void *g, int *a, int *b, void *p);
extern int func_ov003_02226c14(void *g, int *a, int *b, void *p);
extern int func_ov003_02226a40(void *g, int *a, int *b, void *p);
extern void func_ov003_022268a8(void *g, int *a, int *b, int *c);

extern void func_ov003_02226978(void *g, int *a, int *b, int *c, int *d);
extern int func_ov003_02226fdc(void *g, int *a, int *b);
extern int func_ov003_02226ef4(void *g, int *a, int *b);
extern int func_ov003_02226bb4(void *g, int *a, int *b);
extern void func_ov003_02226874(void *g, int *a, int *b);

extern int func_ov003_02226fa0(void *g, int *a, int *b);
extern int func_ov003_02226de8(void *g, int *a, int *b, void *p);
extern int func_ov003_02226b04(void *g, int *a, int *b, void *p);
extern int func_ov003_022269f8(void *g, int *a, int *b, void *p);
extern void func_ov003_0222681c(void *g, int *a, int *b, int *c);

int func_ov003_02226604(void)
{
    int iB0, iB1, iB2, iB3;
    int iC0, iC1, iC2, iC3;
    int iD0, iD1, iD2, iD3;
    int a0[3], a1[3], a2[3], a3[3];
    int b0[6], b1[6];
    int d0[6], d1[6];
    int m0[18], m1[18];
    void **p;
    int ok1, ok2, ok3;
    int r;

    r = func_0204cab4();
    ok1 = 0;
    ok2 = 0;
    ok3 = 0;
    p = data_ov003_02236dac[r];

    func_ov003_022269b0(data_ov003_0223cf70, m0, m1, a0, a1, a2, a3);
    if (func_ov003_0222703c(data_ov003_0223cf70, m0, m1) && func_ov003_02226f5c(data_ov003_0223cf70, a0, a1, a2, a3) &&
        func_ov003_02226e78(data_ov003_0223cf70, m0, a2, p) && func_ov003_02226cc4(data_ov003_0223cf70, m0, a0, p) &&
        func_ov003_02226a88(data_ov003_0223cf70, m0, a2, p)) {
        ok1 = 1;
    }
    func_ov003_02226900(data_ov003_0223cf70, m1, a1, a3);

    func_ov003_0222698c(data_ov003_0223cf70, b0, b1, &iB0, &iB1, &iB2, &iB3);
    if (func_ov003_02227000(data_ov003_0223cf70, b0, b1) && func_ov003_02226f18(data_ov003_0223cf70, &iB0, &iB1, &iB2, &iB3) &&
        func_ov003_02226e30(data_ov003_0223cf70, b0, &iB2, p) && func_ov003_02226c14(data_ov003_0223cf70, b0, &iB0, p) &&
        func_ov003_02226a40(data_ov003_0223cf70, b0, &iB2, p)) {
        ok2 = 1;
    }
    func_ov003_022268a8(data_ov003_0223cf70, b1, &iB1, &iB3);

    func_ov003_02226978(data_ov003_0223cf70, &iC0, &iC1, &iC2, &iC3);
    if (func_ov003_02226fdc(data_ov003_0223cf70, &iC0, &iC1) && func_ov003_02226ef4(data_ov003_0223cf70, &iC2, &iC3) &&
        func_ov003_02226bb4(data_ov003_0223cf70, &iC0, &iC2)) {
        ok2 = 1;
    }
    func_ov003_02226874(data_ov003_0223cf70, &iC1, &iC3);

    func_ov003_0222698c(data_ov003_0223cf70, d0, d1, &iD0, &iD1, &iD2, &iD3);
    if (func_ov003_02226fa0(data_ov003_0223cf70, d0, d1) && func_ov003_02226f18(data_ov003_0223cf70, &iD0, &iD1, &iD2, &iD3) &&
        func_ov003_02226de8(data_ov003_0223cf70, d0, &iD2, p) && func_ov003_02226b04(data_ov003_0223cf70, d0, &iD0, p) &&
        func_ov003_022269f8(data_ov003_0223cf70, d0, &iD2, p)) {
        ok3 = 1;
    }
    func_ov003_0222681c(data_ov003_0223cf70, d1, &iD1, &iD3);

    if (ok1 && ok2 && ok3) {
        return 1;
    }
    return 0;
}
