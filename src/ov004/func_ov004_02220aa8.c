/* func_ov004_02220aa8 @ 0x02220aa8, 0x18c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_0204bcdc(void *p);
extern int func_0204bc64(void *p);
extern int func_020644cc(int n);
extern int func_0206fbc0(void);
extern int func_0206fc6c(void);
extern int func_0204c878(void *p);
extern void *func_020984e8(void);
extern void *func_02099870(void *p);
extern int func_020807a8(void *a, void *b);
extern int func_02081d20(int h);
extern int _fflt(int x);
extern int _fadd(int a, int b);
extern int _fsub(int a, int b);
extern int _ffix(int f);
extern int FX_Div(int a, int b);
extern int FX_MulFunc(int a, int b);
extern int func_0206f83c(void);
extern void func_02015fb0(void *self, int a, int b, int c, int d, int e);
extern void func_0208b520(void);
extern void *func_0208150c(void *p);
extern void func_0200366c(void *a, void *b, int n, void *c);
extern void func_0206844c(int a, void *b, void *c);
extern void func_ov004_02220c34(void *self, int a);
extern char data_ov004_02257df0[];
extern char data_ov004_02253ed0[];

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

void func_ov004_02220aa8(void *self)
{
    // DECLS
    int saved;
    int h;
    int v;
    int t;
    // ENDDECLS
    u8 code;

    saved = *(int *) ((char *) self + 0x40);
    code = (u8) (func_020644cc(2) + 8);
    *(int *) ((char *) self + 0x1a8) = 0;
    if (func_0206fbc0() == 0) {
        return;
    }
    if (func_0206fc6c() != 0) {
        h = 0;
        v = 0;
        if (chk((u16 *) ((char *) *(void **) ((char *) self + 0x1a4) + 0x898), 0xfff1) == 0) {
            *(int *) ((char *) self + 0x1a8) = func_0204c878((char *) *(void **) ((char *) self + 0x1a4) + 0x898);
            if (func_020984e8() != 0) {
                h = func_020807a8(*(void **) ((char *) *(void **) ((char *) self + 0x1a4) + 0x830),
                                  func_02099870(func_020984e8()));
            }
            if (h != 0) {
                v = func_02081d20(h);
            }
            v += 0xff;
            if (v > 0) {
                t = _fadd(0x3f000000, _fflt(v << 12));
            } else {
                t = _fsub(_fflt(v << 12), 0x3f000000);
            }
            v = FX_Div(_ffix(t), 0x200000);
            func_02015fb0(self, func_0206f83c(), 0, 0xa, 0, 0);
            v = FX_MulFunc(*(int *) ((char *) self + 0x1a8), v);
            if (v <= 0xa) {
                v = 0xa;
            }
            if (func_0206f83c() > v) {
                code = (u8) (func_020644cc(2) + 0xa);
            } else {
                *(int *) ((char *) self + 0x1a8) = func_0206f83c();
                code = (u8) (func_020644cc(2) + 0xc);
                func_0208b520();
            }
        }
    }
    func_0200366c(func_0208150c(*(void **) ((char *) *(void **) ((char *) self + 0x1a4) + 0x830)), data_ov004_02257df0, 0x28,
                  data_ov004_02253ed0);
    func_0206844c(saved, &code, data_ov004_02257df0);
    func_ov004_02220c34(self, 0);
}
