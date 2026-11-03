/* paired_town_2: 6 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020a0efc @ 0x020a0efc, 0x40 bytes, Thumb
 * func_020a0eac @ 0x020a0eac, 0x50 bytes, Thumb
 * func_020a0ea8 @ 0x020a0ea8, 0x2 bytes, Thumb
 * func_020a0c74 @ 0x020a0c74, 0x234 bytes, Thumb
 * func_020a0c18 @ 0x020a0c18, 0x5a bytes, Thumb
 * func_020a0b94 @ 0x020a0b94, 0x82 bytes, Thumb
 */

struct UnkStruct_020a0c18 {
    char pad_00[0x24];
};

extern int func_02090040(int a);
extern int func_02090124(int);
extern void func_020882f0(void *);
extern int func_020a6ed0(void);
extern void *data_020ccf94;
extern int func_02073dd4(void *p, int i);
extern void *func_020984fc(int a);
extern void *func_020641c8(void *o);
extern void *func_020641b0(void *o);
extern int func_02099870(void *p);
extern int func_02095040(void *);
extern void func_02064210(int a, void *o);
extern void *func_02099688(void *p);
extern int func_020882dc(void *p);
extern int func_020ec1e8(void);
extern short *func_0209d358(int a, int b);
extern int func_020644cc(int n);
extern void func_020882b0(void *p, unsigned char f);
extern void func_020882e4(void *p, int v);
extern void func_020882cc(void *p, int v);
extern int func_020a2450(void *a, int i);
extern void MI_CpuCopy8(void *a, void *b, int n);
extern void *func_02099664(int a);
extern void *func_02077bc8(void *p);
extern void *func_02077d68(void *);
extern void *func_02099658(int a);
extern void *func_02077d00(void *entries);
extern void *func_02077c3c(struct UnkStruct_020a0c18 *p);
extern int func_020eb058(void *a, void *b);
extern void *func_020984e8(void);
extern int func_020882ec(void *);
extern int func_020882c4(void *);

void func_020a0c74(void *self, int idx);
int func_020a0c18(int a, int b, int c);

void func_020a0efc(int param)
{
    int i = 3;
    int temp = (*(int *) &data_020ccf94);
    do {
        if (func_02073dd4((void *) temp, i) != 0) {
            func_020882f0((void *) func_02090124((int) func_02090040(i)));
        }
    } while (--i >= 0);
    func_020a0c74((void *) param, func_020a6ed0());
}

void func_020a0eac(void *a0)
{
    void *p;
    int i;
    for (i = 3, p = data_020ccf94; i >= 0; i--) {
        if (func_02073dd4(p, i)) {
            func_020882f0((void *) func_02090124((int) func_02090040(i)));
        }
    }
    for (i = 3; i >= 0; i--) {
        if (func_02073dd4(p, i)) {
            func_020a0c74(a0, i);
        }
    }
}

void func_020a0ea8(void *self, void *record) {}

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
            if (func_020a0c18((int) self, (int) q, (int) p) == 0) {
                continue;
            }
            if (func_020a0c18((int) self, (int) p, (int) q) == 0) {
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
    y = (void *) func_02090040(A);
    func_020641c8(o3);
    if (x != 0) {
        func_02064210(func_02095040((void *) func_02099870(x)), o3);
    }
    MI_CpuCopy8(pr, (void *) func_02090124((int) y), 0x10);
    x = func_020984fc(B);
    y = (void *) func_02090040(B);
    func_020641c8(o4);
    if (x != 0) {
        func_02064210(func_02095040((void *) func_02099870(x)), o4);
    }
    MI_CpuCopy8(rr, (void *) func_02090124((int) y), 0x10);
    func_020641b0(o4);
    func_020641b0(o3);
    func_020641b0(o2);
    func_020641b0(o1);
}

int func_020a0c18(int a, int b, int c)
{
    void *x;
    struct UnkStruct_020a0c18 *arr;
    void *y;
    int i;

    x = (func_02077d68((void *) func_02077bc8(func_02099664(b))));
    arr = func_02077d00(func_02099658(c));
    for (i = 0; i < 0x20; i++) {
        y = (func_02077d68((void *) func_02077c3c(&arr[i])));
        if (y != 0 && func_020eb058(x, y) != 0) {
            return 1;
        }
    }
    return 0;
}

void func_020a0b94(void *receiver)
{
    void *p5, *p4;
    int r6;
    char obj1[0x20];
    char obj2[0x20];

    p5 = (void *) func_02090040(4);
    p4 = func_020984e8();

    func_020641c8(obj1);
    func_02064210(func_02095040((void *) func_02099870(p4)), obj1);

    r6 = (int) func_02099688(p4);
    p4 = (void *) func_02090124((int) p5);

    func_020641c8(obj2);
    func_02064210(func_020882ec(p4), obj2);

    if (func_020882dc(p4) != 0) {
        MI_CpuCopy8(p4, (void *) r6, 0x10);
        func_020882c4(p4);
    }

    func_020882f0((void *) func_02090124((int) p5));

    func_020641b0(obj2);
    func_020641b0(obj1);
}
