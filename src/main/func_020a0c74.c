/* func_020a0c74 @ 0x020a0c74, 0x234 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020984fc(int a);
extern void *func_020641c8(void *o);
extern void *func_020641b0(void *o);
extern int func_02099870(void *p);
extern int func_02095040(void *);
extern void func_02064210(int a, void *o);
extern void *func_02099688(void *p);
extern int func_020882dc(void *p);
extern void func_020a0ea8(void *a, void *b);
extern int func_02073dd4(void *g, int i);
extern int func_020ec1e8(void);
extern int func_020a0c18(void *a, void *b, void *c);
extern short *func_0209d358(int a, int b);
extern int func_020644cc(int n);
extern void func_020882b0(void *p, unsigned char f);
extern void func_020882e4(void *p, int v);
extern void func_020882cc(void *p, int v);
extern int func_020a2450(void *a, int i);
extern void *func_02090040(int a);
extern void *func_02090124(void *p);
extern void MI_CpuCopy8(void *a, void *b, int n);
extern void *data_020ccf94;

void func_020a0c74(void *self, int idx)
{
    char o1[0x20];
    char o2[0x20];
    char o3[0x20];
    char o4[0x20];
    void *p;
    void *pr;
    int best;
    void *q;
    void *rr;
    void *g;
    int i;
    int A, B;
    void *x, *y;

    p = func_020984fc(idx);
    if (p == 0) {
        return;
    }
    func_020641c8(o1);
    func_02064210(func_02095040((void *) func_02099870(p)), o1);
    pr = func_02099688(p);
    if (func_020882dc(pr) != 0) {
        func_020a0ea8(self, pr);
        func_020641b0(o1);
        return;
    }
    best = 4;
    q = 0;
    rr = 0;
    func_020641c8(o2);
    i = 0;
    g = data_020ccf94;
    for (; i < 4; i++) {
        if (i == idx) {
            continue;
        }
        if (func_02073dd4(g, i) == 0) {
            continue;
        }
        q = func_020984fc(i);
        if (q == 0) {
            continue;
        }
        func_02064210(func_02095040((void *) func_02099870(q)), o2);
        rr = func_02099688(q);
        if (func_020882dc(rr) != 0) {
            continue;
        }
        if (func_020ec1e8() == 3 || func_020ec1e8() == 4) {
            if (func_020a0c18(self, q, p) == 0) {
                continue;
            }
            if (func_020a0c18(self, p, q) == 0) {
                continue;
            }
        }
        best = i;
        break;
    }
    if (best == 4) {
        func_020641b0(o2);
        func_020641b0(o1);
        return;
    }
    if (*func_0209d358(0, 0x49) == 0) {
        if (func_020644cc(0x10) != 0) {
            func_020641b0(o2);
            func_020641b0(o1);
            return;
        }
    }
    i = func_020644cc(2);
    func_020882b0(rr, (unsigned char) (i == 0));
    func_020882e4(rr, func_02095040((void *) func_02099870(p)));
    func_020882cc(rr, 0xa);
    func_020882b0(pr, (unsigned char) (i == 1));
    func_020882e4(pr, func_02095040((void *) func_02099870(q)));
    func_020882cc(pr, 0xa);
    func_020a0ea8(self, pr);
    func_020a0ea8(self, rr);
    A = func_020a2450(self, idx);
    B = func_020a2450(self, best);
    x = func_020984fc(A);
    y = func_02090040(A);
    func_020641c8(o3);
    if (x != 0) {
        func_02064210(func_02095040((void *) func_02099870(x)), o3);
    }
    MI_CpuCopy8(pr, func_02090124(y), 0x10);
    x = func_020984fc(B);
    y = func_02090040(B);
    func_020641c8(o4);
    if (x != 0) {
        func_02064210(func_02095040((void *) func_02099870(x)), o4);
    }
    MI_CpuCopy8(rr, func_02090124(y), 0x10);
    func_020641b0(o4);
    func_020641b0(o3);
    func_020641b0(o2);
    func_020641b0(o1);
}
