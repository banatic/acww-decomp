/* func_ov004_0221f474 @ 0x0221f474, 0x2a8 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct OUT {
    void *unk_00;
    u8 unk_04;
};

extern int func_0204bcdc(void *p);
extern int func_0204bc64(void *p);
extern void *func_020984e8(void);
extern void *func_02099870(void *p);
extern int func_020804b8(void *a, void *b);
extern void func_02081e14(int r, int a, int b, int c);
extern void *func_0208150c(void *p);
extern void func_0200366c(void *a, void *b, int n, void *c);
extern int func_020644cc(int n);
extern void func_02015de4(void *self, void *p, int a, int b);
extern int func_0204c878(void *p);
extern int func_020807a8(void *a, void *b);
extern int func_02081d20(int h);
extern int _fflt(int x);
extern int _fadd(int a, int b);
extern int _fsub(int a, int b);
extern int _ffix(int f);
extern int FX_MulFunc(int a, int b);
extern int FX_Div(int a, int b);
extern int _s32_div_f(int a, int b);
extern void func_02015fb0(void *self, int a, int b, int c, int d, int e);
extern int func_0207f708(void *a, u16 *p);
extern int func_02099fe8(void);
extern int func_0201b43c(void *a, int b);
extern char data_ov004_02257d30[];
extern char data_ov004_02253c98[];
extern char data_ov004_02253ca4[];
extern char data_ov004_02253cb0[];
extern char data_ov004_02253cbc[];

static __inline int chk(u16 *p, u16 k)
{
    u16 t;
    int t1;

    if (func_0204bcdc((void *) p) != 0) {
        t = k;
        t1 = func_0204bc64((void *) p);
        return (t1 == func_0204bc64((void *) &t)) ? 1 : 0;
    }
    return (*p == k) ? 1 : 0;
}

void func_ov004_0221f474(void *self, struct OUT *out)
{
    // DECLS
    int h;
    void *g;
    u16 *pi;
    int c;
    int n;
    int t;
    int w;
    int r;
    int k;
    // ENDDECLS
    u16 tmp;

    h = func_020804b8(*(void **) ((char *) *(void **) ((char *) self + 0x1a4) + 0x830), func_02099870(func_020984e8()));
    if (h != 0) {
        func_02081e14(h, 0, 0, 0);
    }
    g = *(void **) ((char *) self + 0x1a4);
    if (*(u8 *) ((char *) g + 0xa54) == 3) {
        func_0200366c(func_0208150c(*(void **) ((char *) g + 0x830)), data_ov004_02257d30, 0x28, data_ov004_02253c98);
        out->unk_00 = data_ov004_02257d30;
        out->unk_04 = (u8) (func_020644cc(3) + 3);
    } else {
        pi = (u16 *) ((char *) g + 0x898);
        if (chk(pi, 0xfff1) == 0) {
            c = 0;
            func_02015de4(self, (char *) *(void **) ((char *) self + 0x1a4) + 0x898, c, 7);
            *(int *) ((char *) self + 0x1a8) = func_0204c878((char *) *(void **) ((char *) self + 0x1a4) + 0x898);
            if (*(int *) ((char *) self + 0x1a8) < 0xa) {
                *(int *) ((char *) self + 0x1a8) = 0xa;
            }
            if (func_020984e8() != 0) {
                h = func_020807a8(*(void **) ((char *) *(void **) ((char *) self + 0x1a4) + 0x830),
                                  func_02099870(func_020984e8()));
            }
            if (h != 0) {
                c = func_02081d20(h);
            }
            n = 0xff - c;
            if (n > 0) {
                t = _fadd(0x3f000000, _fflt(n << 12));
            } else {
                t = _fsub(_fflt(n << 12), 0x3f000000);
            }
            *(int *) ((char *) self + 0x1a8) = FX_Div(FX_MulFunc(*(int *) ((char *) self + 0x1a8), _ffix(t)), 0x200000);
            w = *(int *) ((char *) self + 0x1a8);
            r = _s32_div_f(w, 0xa) * 0xa;
            if (w - r >= 5) {
                r += 0xa;
            }
            *(int *) ((char *) self + 0x1a8) = r;
            func_02015fb0(self, *(int *) ((char *) self + 0x1a8), 3, 0xa, 0, 0);
            k = 0;
            if (*(void **) ((char *) *(void **) ((char *) self + 0x1a4) + 0x830) != 0) {
                tmp = 0xfff1;
                k = 0xa - func_0207f708(*(void **) ((char *) *(void **) ((char *) self + 0x1a4) + 0x830), &tmp);
            }
            if (*(int *) ((char *) *(void **) ((char *) self + 0x1a4) + 0x89c) == -1 || func_02099fe8() == -1 || k <= 3 ||
                func_0201b43c(*(void **) ((char *) self + 0x1a4), *(int *) ((char *) self + 0x1a8)) == 0) {
                func_0200366c(func_0208150c(*(void **) ((char *) *(void **) ((char *) self + 0x1a4) + 0x830)),
                              data_ov004_02257d30, 0x28, data_ov004_02253ca4);
            } else {
                func_0200366c(func_0208150c(*(void **) ((char *) *(void **) ((char *) self + 0x1a4) + 0x830)),
                              data_ov004_02257d30, 0x28, data_ov004_02253cb0);
            }
            out->unk_00 = data_ov004_02257d30;
            out->unk_04 = (u8) func_020644cc(3);
        } else {
            switch (*(u8 *) ((char *) *(void **) ((char *) self + 0x1a4) + 0xa54)) {
                case 0:
                    func_0200366c(func_0208150c(*(void **) ((char *) *(void **) ((char *) self + 0x1a4) + 0x830)),
                                  data_ov004_02257d30, 0x28, data_ov004_02253c98);
                    out->unk_04 = (u8) func_020644cc(3);
                    break;
                case 1:
                    func_0200366c(func_0208150c(*(void **) ((char *) *(void **) ((char *) self + 0x1a4) + 0x830)),
                                  data_ov004_02257d30, 0x28, data_ov004_02253cbc);
                    out->unk_04 = (u8) func_020644cc(3);
                    break;
                case 2:
                    func_0200366c(func_0208150c(*(void **) ((char *) *(void **) ((char *) self + 0x1a4) + 0x830)),
                                  data_ov004_02257d30, 0x28, data_ov004_02253c98);
                    out->unk_04 = (u8) (func_020644cc(3) + 6);
                    break;
            }
            out->unk_00 = data_ov004_02257d30;
        }
    }
}
