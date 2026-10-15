/* func_ov112_022a1310 @ 0x022a1310, 0xe4 bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_ov095_0229c084(void *, int);
extern void func_02051bf8(void *, int);
extern void *func_02070c08(void *);
extern int func_020984e8(void);
extern void *func_02094fd4(void *);
extern int func_02099870(int);
extern void *func_02095074(int, void *);
extern void *func_020b496c(int, void *);
extern int func_0207094c(void *, int);
extern void *func_020707d0(void *);
extern int func_020a87e0(void *, void *);
extern int func_02051c8c_unk(void *, int);
extern int func_02051c08(void *, void *, int);
extern void func_ov002_0220a580(void *);
extern void MI_CpuFill8(void *, int, int);
extern void *func_020707b8(void *);
extern void *func_02094fbc(void *);
extern int **func_02070be8(void *);

void func_ov112_022a1310(char *self)
{
    struct {
        u8 a[0x20];
        u8 b[0x6c];
        u8 c[0x0c];
        u8 d[0x54];
    } s;
    int r4;

    *(u32 *) (self + 0xac) = 0;

    func_ov095_0229c084(self + 0x384, 2);
    func_02051bf8(self + 0xc4, 0x60);

    func_02070c08(s.b);
    r4 = func_020984e8();
    func_02094fd4(s.a);
    func_02095074(func_02099870(r4), s.a);
    func_020b496c(0, s.a);

    func_0207094c(s.b, 0x89);
    func_020707d0(s.c);
    func_020a87e0(s.c, s.b);

    r4 = func_02051c8c_unk(&s.d[2], 0x10);
    func_02051c08(&s.d[2], self + 0xc4, r4);

    for (; r4 < 0x10; r4++) {
        ((u16 *) (self + 0xc4))[r4] = 0x3000;
    }

    *(u8 *) (self + 0xc0) = 0x10;

    func_ov002_0220a580(self + 0x4234);
    MI_CpuFill8(self + 0x4e50, 0xdd, 0x1e00);

    *(u8 *) (self + 0xb6) = 0;
    *(u8 *) (self + 0xb7) = 0;
    *(u8 *) (self + 0xb8) = 0;

    func_020707b8(s.c);
    func_02094fbc(s.a);
    func_02070be8(s.b);
}
