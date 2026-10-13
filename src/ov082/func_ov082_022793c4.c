/* func_ov082_022793c4 @ 0x022793c4, 0x178 bytes, Thumb, module ov082
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u16 id;
    u16 unk_02;
    u16 unk_04;
    u16 unk_06;
    int unk_08;
    int unk_0C;
    int unk_10;
    int unk_14;
} UnkStruct_022793c4;

extern char data_021f3aa4;
extern char data_021e5a2c;
extern char data_021dc7a8;

extern int func_0202ec58(void);
extern void func_ov082_02279324(char *self, int a);
extern void func_020866b8(void *g, int a);
extern void func_0208674c(u16 *dst, void *g);
extern void func_020867e0(void *g);
extern int func_020644cc(int a);
extern void func_0209e474(int *p);
extern int func_020617d8(int a);
extern int func_0202d1a8(UnkStruct_022793c4 *w, int *a, int *b, int c, int d, int e, int f);
extern void func_02086754(void *g, UnkStruct_022793c4 *w);
extern int func_02086564(UnkStruct_022793c4 *w);
extern void func_02086748(void *g, int a);
extern int func_0207cc94(void *g, int a, int b);
extern int func_0208150c(void);
extern void func_020867a4(void *g, int a);
extern void func_02086834(void *g, int a);
extern void func_0209f128(void *p, int a);
extern void func_02016764(void *a, void *b, int c, int d, int e, int f, int g2, int h);
extern void func_02054188(void *a, int b, int c);

int func_ov082_022793c4(char *self)
{
    UnkStruct_022793c4 w;
    void *g;
    int idx;
    int t;
    int f;
    u16 a0, a1;

    if (func_0202ec58() == 0) {
        return 0;
    }

    func_ov082_02279324(self, 0);
    g = &data_021f3aa4;
    func_020866b8(g, 2);
    func_0208674c(&w.unk_02, g);

    f = 0;
    a0 = *(volatile u16 *) &w.unk_02;
    a1 = *(volatile u16 *) &w.unk_02;
    if (a1 >= 0x12b0 && a0 <= 0x12e7) {
        f = 1;
    }
    if (f == 0) {
        func_020867e0(g);
        idx = func_020644cc(2);
        w.unk_08 = 0;
        w.unk_0C = 0;
        w.unk_10 = 0;
        w.unk_14 = 0;
        w.id = 0xfff1;
        func_0209e474(&w.unk_10);
        t = func_020617d8(((u8 *) &w)[0x14] - 1);
        if (t != 0) {
            if (func_0202d1a8(&w, &w.unk_08, &w.unk_0C, idx, t, 0, 0) == 0) {
                func_0202d1a8(&w, &w.unk_08, &w.unk_0C, idx, t, 0, 0);
            }
        }
        func_02086754(g, &w);
        func_0208674c(&w.unk_04, g);

        f = 0;
        a0 = *(volatile u16 *) &w.unk_04;
        a1 = *(volatile u16 *) &w.unk_04;
        if (a1 >= 0x12b0 && a0 <= 0x12e7) {
            f = 1;
        }
        if (f != 0) {
            if (func_0207cc94(&data_021e5a2c, 0, 0) != 0) {
                func_020867a4(g, func_0208150c());
                func_02086834(g, 2);
                func_0209f128(&data_021dc7a8, 0xf);
            }
        }
        *(int *) (self + 0x724) = func_02086564(&w);
        func_02086748(g, *(int *) (self + 0x724));
    }

    func_02016764(self + 0x334, self, 0x140, 0, 0, 0x1000, 0, 1);
    func_02054188(self + 0xec, 0xc, 0xe);
    *(int *) (self + 0x4e8) |= 2;
    return 1;
}
