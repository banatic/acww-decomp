/* room_object_body_5: 11 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_022109cc @ 0x022109cc, 0x18 bytes, Thumb
 * func_ov004_022108d0 @ 0x022108d0, 0xfc bytes, Thumb
 * func_ov004_022108cc @ 0x022108cc, 0x4 bytes, Thumb
 * func_ov004_022108c8 @ 0x022108c8, 0x4 bytes, Thumb
 * func_ov004_022108c4 @ 0x022108c4, 0x2 bytes, Thumb
 * func_ov004_022108c0 @ 0x022108c0, 0x2 bytes, Thumb
 * func_ov004_022108bc @ 0x022108bc, 0x2 bytes, Thumb
 * func_ov004_022108b8 @ 0x022108b8, 0x2 bytes, Thumb
 * func_ov004_02210838 @ 0x02210838, 0x80 bytes, Thumb
 * func_ov004_0221082c @ 0x0221082c, 0xc bytes, Thumb
 * func_ov004_0221081c @ 0x0221081c, 0x10 bytes, Thumb
 */

#include "types.h"

typedef struct {
    int unk_00, unk_04, unk_08;
} UnkStruct_02210838;

extern int func_0203efdc(char *arg0);
extern void func_ov004_0223cf68(void *p);
extern void func_ov004_0220ecec(void *self);
extern void func_ov004_0220f994(void *self);
extern int func_ov004_0220cdf8(void *self);
extern int func_ov004_0220cdec(void *self);
extern void func_ov004_0220d2bc(void *p, void *self);
extern int func_ov004_0220e028(void *p);
extern void func_0209d200(void *d, void *p);
extern int func_ov004_0220e758(void *self, int *x, int *y, int a, int b);
extern int func_020b65c4(void);
extern int func_ov004_0223d348(void);
extern int func_020b6694(int v);
extern int func_020b67e8(int v);
extern void func_ov004_0220f100(void *self, unsigned char a, int b);
extern int func_0204f538(void *g, u16 *t, int x, int y, int k);
extern int func_ov004_0220e640(void *self);
extern int *func_ov004_0223ce84(void);
extern int func_ov004_0223cde8(int *a, void *self);
extern void func_02003510(void *self, int mode);
extern int data_ov004_02259698;
extern void *data_021c80bc;
extern UnkStruct_02210838 data_ov004_02256dc8;
extern int data_ov004_02256c68;
extern int data_ov004_02256dbc;
extern short FX_SinCosTable_[];
extern void __register_global_object(UnkStruct_02210838 *a, void *destructor, void *c);
extern void func_020012dc(void *arg0);
extern void *func_020961a8(int i);
extern int func_020537a8(int);

int func_ov004_022109cc(int result)
{
    if (func_0203efdc((char *) result) != 0) {
        result = 1;
    } else {
        result = 0;
    }
    return result;
}

void func_ov004_022108d0(char *self, int mode)
{
    u16 t;
    int x;
    int y;
    int v;
    void *g;

    if (mode == 2) {
        func_ov004_0223cf68(self + 0x798);
        func_ov004_0220ecec(self);
        func_ov004_0220f994(self);
        if (func_ov004_0220cdf8(self) == 0 && func_ov004_0220cdec(self) == 0) {
            func_ov004_0220d2bc(self + 0x740, self);
        }
        func_ov004_0220e028(self + 0x6cc);
        func_0209d200(&data_ov004_02259698, self + 0x132);
        if (func_ov004_0220cdf8(self) != 0) {
            func_ov004_0220e758(self, &x, &y, 0, 0);
            v = func_020b65c4();
            if (func_ov004_0223d348() != 0 && func_020b6694(v) == 0 && func_020b67e8(v) == 0) {
                g = data_021c80bc;
                func_ov004_0220f100(self, 0, 0);
                if (g != 0) {
                    t = 0x1547;
                    func_0204f538(g, &t, x, y, 0);
                }
            } else {
                func_ov004_0220f100(self, 1, 0);
            }
            func_ov004_0220e640(self);
        }
        func_ov004_0223cde8(func_ov004_0223ce84(), self);
    }
    func_02003510(self, mode);
}

int func_ov004_022108cc(void)
{
    return 0;
}

int func_ov004_022108c8(void)
{
    return 1;
}

void func_ov004_022108c4(void) {}

void func_ov004_022108c0(void) {}

void func_ov004_022108bc(void) {}

void func_ov004_022108b8(void) {}

UnkStruct_02210838 *func_ov004_02210838(char *self)
{
    void *p;
    int i;

    if ((data_ov004_02256c68 & 1) == 0) {
        __register_global_object(&data_ov004_02256dc8, ((void *) &func_020012dc), &data_ov004_02256dbc);
        data_ov004_02256c68 |= 1;
    }
    data_ov004_02256dc8.unk_00 = *(int *) (self + 0x5c);
    data_ov004_02256dc8.unk_04 = *(int *) (self + 0x60);
    data_ov004_02256dc8.unk_08 = *(int *) (self + 0x64);
    p = func_020961a8(4);
    if (p != 0) {
        i = *(u16 *) ((char *) p + 0x8e) >> 4;
        data_ov004_02256dc8.unk_00 = *(int *) ((char *) p + 0x5c) + FX_SinCosTable_[i * 2];
        data_ov004_02256dc8.unk_04 = *(int *) ((char *) p + 0x60);
        data_ov004_02256dc8.unk_08 = *(int *) ((char *) p + 0x64) + FX_SinCosTable_[i * 2 + 1];
    }
    return &data_ov004_02256dc8;
}

int func_ov004_0221082c(char *self)
{
    // DECLS
    // ENDDECLS
    return *(u8 *) (self + 0x77c);
}

int func_ov004_0221081c(char *self)
{
    // DECLS
    // ENDDECLS
    return func_020537a8(*(int *) (self + 0x284));
}
