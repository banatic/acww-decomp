/* func_ov068_0226d14c @ 0x0226d14c, 0xc0 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

class UnkStruct_0226d14c {
  public:
    virtual void vf00();
    virtual void vf01();
    virtual void vf02();
    virtual void vf03();
    virtual void vf04();
    virtual void vf05();
    virtual void vf06();
    virtual void vf07();
    virtual void vf08();
    virtual void vf09();
    virtual void vf10();
    virtual void vf11();
    virtual void vf12();
    virtual void vf13();
    virtual void vf14();
    virtual void vf15();
    virtual void vf16();
    virtual void vf17();
    virtual void vf18();
    virtual void vf19();
    virtual void vf20();
    virtual void vf21();
    virtual void vf22();
    virtual void vf23();
    virtual void vf24();
    virtual int vf25();
};

extern "C" {
extern int func_0207f1c8(int a);
extern int func_0209b5ec(int a);
extern int func_0209c330(int a);
extern int func_0202d6e4(const void *tbl, int n);
extern int func_0202d0ec(volatile u16 *a, int lo, int hi, u8 d, u8 e, u8 f);
extern int func_02086564(volatile u16 *p);
extern int func_02086744(void *p);
extern void *func_0208150c(int a);
extern void func_020867a4(void *p, void *q);
extern void func_02086748(void *p, int v);
extern void func_02086754(void *p, volatile u16 *q);
extern int data_021f3aa4;
extern const int data_ov068_0227675c;
extern const int data_ov068_02276774;
}

extern "C" void func_ov068_0226d14c(UnkStruct_0226d14c *self, u8 *p)
{
    unsigned int ok;
    volatile u16 t;
    const void *tbl;
    void *g;
    unsigned int i;
    int v;

    tbl = &data_ov068_0227675c;
    g = &data_021f3aa4;
    if (func_0209c330(func_0209b5ec(func_0207f1c8(self->vf25()))) == 0) {
        tbl = &data_ov068_02276774;
    }
    i = func_0202d6e4(tbl, 5);
    if (i < 4) {
        t = 0xfff1;
        if (func_0202d0ec(&t, i, i + 1, p[2], p[2], p[4]) != 0) {
            u16 lo;
            u16 hi;
            ok = 0;
            lo = t;
            hi = t;
            if (hi >= 0x12b0 && lo <= 0x12e7) {
                ok = 1;
            }
            if (ok != 0) {
                v = func_02086564(&t);
                if ((v >> 12) > (func_02086744(g) >> 12)) {
                    func_020867a4(g, func_0208150c(self->vf25()));
                    func_02086748(g, v);
                    func_02086754(g, &t);
                }
            }
        }
    }
}
