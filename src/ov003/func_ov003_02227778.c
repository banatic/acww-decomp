/* func_ov003_02227778 @ 0x02227778, 0x84 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void *data_ov003_0223bdb8;
extern void func_0205556c(void *r, int tag, void *h);
extern void func_0209d238(void *arg, void *p);
extern void *func_0209d324(void);
extern void *NNS_G3dGetJntAnmSet(void *m);
extern void *func_02107b44(void *a, int b);
extern int func_02055140(void *r, void *p);
extern void func_02055060(void *r, void *q, int a, int b, int c, int d);
extern void func_02055050(void *r);

int func_ov003_02227778(char *self, void *m, void *arg)
{
    int ok = 0;
    char *r = self + 0x144;
    void *p;
    void *q;
    func_0205556c(r, 0x66736477, data_ov003_0223bdb8);
    if (m == 0) {
        return ok;
    }
    func_0209d238(arg, self + 0x7c);
    p = func_0209d324();
    q = func_02107b44(NNS_G3dGetJntAnmSet(m), 0);
    if (func_02055140(r, p)) {
        func_02055060(r, q, 0, 0x1000, 1, 0);
        func_02055050(r);
        ok = 1;
    }
    return ok;
}
