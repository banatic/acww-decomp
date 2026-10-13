/* func_0201079c @ 0x0201079c, 0x130 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0205f670(unsigned short *p);
extern int func_0205ceb0(void *q);
extern void func_0205cc1c(char *a, int b, int c, int d);
extern void func_0205cb94(char *a);
extern int NNS_G3dGetJntAnmSet(void);
extern int func_02107b44(int a, int b);
extern void func_020547b0(char *a, int b, int c, int d, int e, int f, int g, int h);
extern int func_0205cebc(int a);
extern unsigned int func_0205cf10(int a);
extern int func_0205ceec(int a, unsigned int b);
extern int func_0205cec8(int a, unsigned int b);
extern void func_02054740(char *a, int b, int c);
extern void func_02054718(char *a, int b, int c);
extern void func_02054768(char *a, int b, int c);

void func_0201079c(char *self, unsigned short *p, void *q, int a3)
{
    int h;
    int mode;
    unsigned int ok;
    unsigned short v;
    int t;
    unsigned int n;
    unsigned int i;
    int x;

    h = func_0205f670(p);
    mode = func_0205ceb0(q);
    if (mode == 3) {
        goto Lend;
    }
    if (h == 0x144) {
        goto Lend;
    }
    if (mode == 1) {
        ok = 0;
        v = *p;
        if (v >= 0x1380 && v <= 0x139f) {
            ok = 1;
        }
        if (ok == 0) {
            if (v < 0x13a0) {
                goto Lend;
            }
            if (v > 0x13a7) {
                goto Lend;
            }
        }
    }
    func_0205cc1c(self + 0x701, h, 1, 0);
    func_0205cb94(self + 0x701);
    func_020547b0(self + 0x234, func_02107b44(NNS_G3dGetJntAnmSet(), 0), a3, 0, 0x1000, 0, 0, 0);
    t = func_0205cebc(h);
    if (t < 4) {
        n = func_0205cf10(t);
        for (i = 0; i < n; i++) {
            x = func_0205ceec(t, i);
            func_02054740(self + 0x234, x, func_0205cec8(t, i));
        }
        if (mode == 2) {
            x = func_0205ceec(1, 0);
            func_02054718(self + 0x234, x, func_0205cec8(1, 0));
        }
    } else {
        func_02054768(self + 0x234, a3, 0);
    }
    goto Ltail;
Lend:
    func_02054768(self + 0x234, a3, 0);
Ltail:
    *(int *) (self + 0x708) = h;
}
