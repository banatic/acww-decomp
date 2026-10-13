/* func_ov081_02279380 @ 0x02279380, 0x158 bytes, Thumb, module ov081
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u16 id;
    u16 unk_02;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
} UnkStruct_02279380;

extern char data_021f3aa4;
extern char data_021e5a2c;
extern char data_021dc7a8;

extern int func_0202ec58(void);
extern void func_ov081_022792e0(char *self, int a);
extern void func_020866b8(void *g, int a);
extern void func_0208674c(u16 *dst, void *g);
extern void func_020867e0(void *g);
extern int func_020644cc(int a);
extern void func_0209e474(int *p);
extern int func_0204fafc(int b);
extern int func_0204fc3c(int a, int b);
extern int func_0202cca4(UnkStruct_02279380 *w, int *a, int *b, int c, int d);
extern void func_02086754(void *g, UnkStruct_02279380 *w);
extern int func_02086564(UnkStruct_02279380 *w);
extern void func_02086748(void *g, int a);
extern int func_0207cc94(void *g, int a, int b);
extern int func_0208150c(void);
extern void func_020867a4(void *g, int a);
extern void func_02086834(void *g, int a);
extern void func_0209f128(void *p, int a);
extern void func_02016764(void *a, void *b, int c, int d, int e, int f, int g2, int h);
extern void func_02054188(void *a, int b, int c);

int func_ov081_02279380(char *self)
{
    UnkStruct_02279380 w;
    void *g;
    int idx;
    int t;
    int b0;
    int f;
    u16 a0, a1;

    if (func_0202ec58() == 0) {
        return 0;
    }

    func_ov081_022792e0(self, 0);
    g = &data_021f3aa4;
    func_020866b8(g, 1);
    func_0208674c(&w.unk_02, g);

    f = 0;
    a0 = *(volatile u16 *) &w.unk_02;
    a1 = *(volatile u16 *) &w.unk_02;
    if (a1 >= 0x12e8 && a0 <= 0x131f) {
        f = 1;
    }
    if (f == 0) {
        func_020867e0(g);
        idx = func_020644cc(2);
        w.unk_04 = 0;
        w.unk_08 = 0;
        w.unk_0C = 0;
        w.unk_10 = 0;
        w.id = 0xfff1;
        func_0209e474(&w.unk_0C);
        b0 = ((u8 *) &w)[0x10];
        t = func_0204fc3c(b0, func_0204fafc(((u8 *) &w)[0xf]));
        if (t != 0) {
            if (func_0202cca4(&w, &w.unk_04, &w.unk_08, idx, t) == 0) {
                func_0202cca4(&w, &w.unk_04, &w.unk_08, (idx + 1) & 1, t);
            }
        }
        func_02086754(g, &w);
        *(int *) (self + 0x724) = func_02086564(&w);
        func_02086748(g, *(int *) (self + 0x724));
        if (func_0207cc94(&data_021e5a2c, 0, 0) != 0) {
            func_020867a4(g, func_0208150c());
            func_02086834(g, 1);
            func_0209f128(&data_021dc7a8, 0xf);
        }
    }

    func_02016764(self + 0x334, self, 0x140, 0, 0, 0x1000, 0, 1);
    func_02054188(self + 0xec, 0xc, 0xe);
    *(int *) (self + 0x4e8) |= 2;
    return 1;
}
