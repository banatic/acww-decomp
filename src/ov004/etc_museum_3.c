/* etc_museum_3: 5 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0221bedc @ 0x0221bedc, 0x1c bytes, Thumb
 * func_ov004_0221bea4 @ 0x0221bea4, 0x38 bytes, Thumb
 * func_ov004_0221be68 @ 0x0221be68, 0x3c bytes, Thumb
 * func_ov004_0221be28 @ 0x0221be28, 0x40 bytes, Thumb
 * func_ov004_0221bd28 @ 0x0221bd28, 0x100 bytes, Thumb
 */

#include "types.h"

struct SubEC {
    void *ptr;
};

struct UnkStruct_0221be68 {
    void *unk_00;
    char pad_04[0xec - 4];
    struct SubEC subEC;
    char pad_F0[0x138 - 0xf0];
    char sub138;
};

typedef struct UnkStruct_0221be28 {
    void *vt0;
    unsigned char pad_04[0xec - 4];
    void *unk_EC;
    unsigned char pad_F0[0x138 - 0xec - 4];
    unsigned char unk_138[1];
} UnkStruct_0221be28;

typedef struct {
    int x, y, z;
} Vec3;

struct UnkStruct_0221bd28 {
    u8 pad_00[0x64];
    int unk_64;
};

union UnkStruct_0221bd28_2 {
    u16 w;
    struct {
        u16 a : 2;
        u16 b : 6;
        u16 c : 8;
    } unk_00;
};

extern int func_020edf70(unsigned int size);
extern void *func_0203f130(void *);
extern void *func_02066a30(void *);
extern void *func_020b7f70(void *);
extern char data_ov004_022533e0[];
extern char data_ov004_02253454[];
extern int func_020b7f60(void *);
extern void *func_02066994(void *);
extern void *func_0203f080(void *);
extern void func_020edf54(void *p);
extern void func_ov004_0221bc98(void);
extern int func_ov004_0221bc44(char *self);
extern int func_ov004_0221b98c(char *self);
extern char *func_02096190(int k);
extern void func_01ffd070(Vec3 *out, void *m, Vec3 *in);
extern u8 func_020b65c4(void);
extern void func_0203efb0(char *self, u16 v);
extern int func_ov004_0221b570(char *self, int a);
extern int func_ov004_0221bad0(char *self);
extern int data_ov004_02257914;
extern s16 data_ov004_0225337c;
extern int data_ov004_02257928;
extern int data_ov004_02257938;
extern s16 FX_SinCosTable_[];
extern struct UnkStruct_0221bd28 *data_020ccf94;

void *func_ov004_0221bea4(void *this);

void func_ov004_0221bedc(void)
{
    void *conditionInput0;

    if ((conditionInput0 = (void *) (func_020edf70(0x170)))) {
        func_ov004_0221bea4((void *) conditionInput0);
    }
}

void *func_ov004_0221bea4(void *this)
{
    func_0203f130(this);
    func_02066a30((char *) this + 0xec);
    *(void **) this = (void *) data_ov004_022533e0;
    *(void **) ((char *) this + 0xec) = (void *) data_ov004_02253454;
    func_020b7f70((char *) this + 0x138);
    return this;
}

struct UnkStruct_0221be68 *func_ov004_0221be68(struct UnkStruct_0221be68 *this)
{
    this->unk_00 = ((char *) data_ov004_022533e0);
    this->subEC.ptr = ((char *) data_ov004_02253454);
    func_020b7f60(&this->sub138);
    func_02066994(&this->subEC);
    func_0203f080(this);
    return this;
}

struct UnkStruct_0221be28 *func_ov004_0221be28(struct UnkStruct_0221be28 *this)
{
    this->vt0 = ((char *) data_ov004_022533e0);
    this->unk_EC = ((char *) data_ov004_02253454);
    func_020b7f60(&this->unk_138);
    func_02066994((void *) (&this->unk_EC));
    func_0203f080(this);
    func_020edf54(this);
    return this;
}

int func_ov004_0221bd28(char *self)
{
    // DECLS
    union UnkStruct_0221bd28_2 u;
    Vec3 in;
    Vec3 out;
    char *p;
    int a;
    // ENDDECLS

    func_ov004_0221bc98();
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
