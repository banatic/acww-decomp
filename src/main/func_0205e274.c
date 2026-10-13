/* func_0205e274 @ 0x0205e274, 0xd2 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0205e194(void *p, int n);
extern void *func_0205e160(void *p, int n);
extern int func_0205e138(void *p, int n);
extern void *func_021077e8(void *p);
extern int NNS_G3dTexGetRequiredSize(void *p);
extern int NNS_G3dTex4x4GetRequiredSize(void *p);
extern int NNS_G3dPlttGetRequiredSize(void *p);
extern void func_02055b50(void *a, void *b);
extern int func_02055c74(void *a, int b);
extern int func_02055c2c(void *a, int b, int c);
extern int func_02055c68(void *a, int b);
extern int func_02055c18(void *a, int b, int c);
extern int func_02055c40(void *a, int b);
extern int func_02055bac(void *a, int b, int c);
extern void func_02055b34(void *a, int b, int c, int d);

void func_0205e274(void *p)
{
    void *q;
    void *a;
    void *tmp;
    void *b;
    int v1, v2, v3, w1, w2, w3;
    int t1, t2, t3, t4, t5, t6;

    a = func_021077e8(func_0205e194(p, 0));
    q = func_0205e160(p, 0);
    func_02055b50(q, a);

    if (func_0205e138(p, 1) >= 0x9e) {
        return;
    }

    tmp = func_0205e194(p, 1);
    if (tmp == 0) {
        return;
    }

    v1 = NNS_G3dTexGetRequiredSize(a);
    v2 = NNS_G3dTex4x4GetRequiredSize(a);
    v3 = NNS_G3dPlttGetRequiredSize(a);

    b = func_021077e8(tmp);

    w1 = NNS_G3dTexGetRequiredSize(b);
    w2 = NNS_G3dTex4x4GetRequiredSize(b);
    w3 = NNS_G3dPlttGetRequiredSize(b);

    p = func_0205e160(p, 1);

    t1 = func_02055c74(q, v1);
    t2 = func_02055c2c(q, t1, w1);
    t3 = func_02055c68(q, v2);
    t4 = func_02055c18(q, t3, w2);
    t5 = func_02055c40(q, v3);
    t6 = func_02055bac(q, t5, w3);

    func_02055b34(p, t2, t4, t6);
    func_02055b50(p, b);
}
