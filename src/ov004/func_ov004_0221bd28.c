/* func_ov004_0221bd28 @ 0x0221bd28, 0x100 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec3;

struct UnkStruct_0221bd28 {
    u8 pad_00[0x64];
    int unk_64;
};

extern void func_ov004_0221bc98(char *self);
extern int func_ov004_0221bc44(char *self);
extern int func_ov004_0221b98c(char *self);
extern char *func_02096190(int k);
extern void func_01ffd070(Vec3 *out, void *m, Vec3 *in);
extern u8 func_020b65c4(void);
extern void func_0203efb0(char *self, u16 v);
extern void func_ov004_0221b570(char *self, int a);
extern int func_ov004_0221bad0(char *self);

extern int data_ov004_02257914;
extern s16 data_ov004_0225337c;
extern int data_ov004_02257928;
extern int data_ov004_02257938;
extern s16 FX_SinCosTable_[];
extern struct UnkStruct_0221bd28 *data_020ccf94;

union UnkStruct_0221bd28_2 {
    u16 w;
    struct {
        u16 a : 2;
        u16 b : 6;
        u16 c : 8;
    } unk_00;
};

int func_ov004_0221bd28(char *self)
{
    // DECLS
    union UnkStruct_0221bd28_2 u;
    Vec3 in;
    Vec3 out;
    char *p;
    int a;
    // ENDDECLS

    func_ov004_0221bc98(self);
    *(int *) (self + 0x15c) = data_ov004_02257914;
    *(s16 *) (self + 0x160) = data_ov004_0225337c;
    *(int *) (self + 0x168) = data_ov004_02257928;
    *(int *) (self + 0x158) = data_ov004_02257938;
    if (func_ov004_0221bc44(self) != 0) {
        if (func_ov004_0221b98c(self) != 0) {
            p = func_02096190(4);
            if (p != 0) {
                a = *(u16 *) (p + 0x8e) >> 4;
                in.x = FX_SinCosTable_[a << 1];
                in.y = 0;
                in.z = FX_SinCosTable_[(a << 1) + 1];
                func_01ffd070(&out, p + 0x5c, &in);
                *(int *) (self + 0x5c) = out.x;
                *(int *) (self + 0x60) = out.y;
                *(int *) (self + 0x64) = out.z;
            }
        }
        u.unk_00.a = (u16) data_020ccf94->unk_64;
        u.unk_00.b = func_020b65c4();
        u.unk_00.c = *(u8 *) (self + 0x154);
        func_0203efb0(self, u.w);
        func_ov004_0221b570(self, 0);
        return func_ov004_0221bad0(self);
    }
    return 0;
}
