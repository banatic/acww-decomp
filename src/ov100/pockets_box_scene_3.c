/* pockets_box_scene_3: 12 functions, module ov100
 * mwccarm 1.2/base -O4,s
 * func_ov100_0229e7ac @ 0x0229e7ac, 0x4 bytes, Thumb
 * func_ov100_0229e7a8 @ 0x0229e7a8, 0x4 bytes, Thumb
 * func_ov100_0229e798 @ 0x0229e798, 0x10 bytes, Thumb
 * func_ov100_0229e77c @ 0x0229e77c, 0x1c bytes, Thumb
 * func_ov100_0229e6ec @ 0x0229e6ec, 0x90 bytes, Thumb
 * func_ov100_0229e668 @ 0x0229e668, 0x84 bytes, Thumb
 * func_ov100_0229e62c @ 0x0229e62c, 0x3c bytes, Thumb
 * func_ov100_0229e5b8 @ 0x0229e5b8, 0x74 bytes, Thumb
 * func_ov100_0229e54c @ 0x0229e54c, 0x6c bytes, Thumb
 * func_ov100_0229e4fc @ 0x0229e4fc, 0x50 bytes, Thumb
 * func_ov100_0229e400 @ 0x0229e400, 0xfc bytes, Thumb
 * func_ov100_0229e3cc @ 0x0229e3cc, 0x34 bytes, Thumb
 */

#include "types.h"

typedef struct UnkStruct_0229e62c {
    unsigned char pad_00[0x28c8];
    int unk_28C8;
} UnkStruct_0229e62c;

struct UnkStruct_0229e54c {
    char pad_00[0x28c8];
    int unk_28C8;
};

struct Context {
    char pad_00[0x28c4];
    int value;
};

extern void func_020ee470(void *argument0);
extern void func_ov100_0229e308(void);
extern void func_ov100_0229e2f4(void *);
extern void func_ov002_02208090(void *, int);
extern int func_ov100_0229e208(void *p);
extern void func_ov094_0229ad20(void *p);
extern void func_ov094_0229ace4(void *p, void *q);
extern void func_ov100_0229d1d0(void *p);
extern void func_ov094_0229b2b0(void *p);
extern void func_ov094_0229b794(void *p, int n);
extern void func_ov002_02207f20(void *p, int a, int b, int c, int d);
extern void func_02002708(int n);
extern void func_ov002_02207e80(void *p, int a, int b, int c);
extern void func_ov100_0229c2b0(void *p, int a);
extern int func_ov002_02207f60(void *p);
extern int func_ov002_02207f48(void *, int);
extern void func_ov002_02207e90(void *, int);
extern void func_ov100_0229e218(void *);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);
extern void func_ov100_0229d8b0(UnkStruct_0229e62c *p);
extern int func_ov100_0229c2d8(void *);
extern int func_ov002_02207d24(void *, int);
extern void func_ov100_0229cc3c(void *);
extern int func_020ee45c(void *);
extern void func_ov092_02299324(int, int, int);
extern void func_ov002_02207f04(void *, int, int, int, int);
extern void func_020027f0(int);
extern void func_ov100_0229c2a0(struct UnkStruct_0229e54c *, int);
extern int func_ov002_02207f3c(struct UnkStruct_0229e54c *, int);
extern void func_ov094_0229af40(void *a, int b);
extern void func_ov094_0229bbd8(void *a, int b);
extern void func_ov094_0229a2b0(void *a, int b);
extern void func_ov002_02209e18(void *a);
extern void func_ov002_02209984(void *a, int b, int c, int _x);
extern int func_0206fca4(void);
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern void func_0206fb58(void);
extern const u8 data_021f3a68[];
extern const u8 data_021f3a86[];
extern void func_ov100_0229d63c(void *);
extern void func_ov094_0229a038(void *);
extern void func_ov094_0229af18(void *);
extern void func_ov002_02209178(void *);
extern void func_ov100_0229c5e0(void *);

void func_ov100_0229e4fc(struct Context *p);

int func_ov100_0229e7ac(void)
{
    return 1;
}

int func_ov100_0229e7a8(void)
{
    return 1;
}

int func_ov100_0229e798(void *argument0)
{
    func_020ee470(argument0);
    return 1;
}

void func_ov100_0229e77c(void *p)
{
    func_ov100_0229e308();
    func_ov100_0229e2f4(p);
    func_ov002_02208090(p, 1);
}

void func_ov100_0229e6ec(void *param)
{
    func_ov100_0229e208(param);
    func_ov094_0229ad20((char *) param + 0xcc);
    func_ov094_0229ace4((char *) param + 0xcc, (char *) param + 0x28dc);
    func_ov100_0229d1d0(param);
    func_ov094_0229b2b0((char *) param + 0x0b2c);
    func_ov094_0229b794((char *) param + 0x0b2c, 0xf);
    func_ov002_02207f20(param, 8, 0, 0, 0x30);
    func_02002708(6);
    func_ov002_02207e80(param, 6, 0, 0);
    func_ov002_02208090(param, 2);
    func_ov100_0229c2b0(param, 1);
    func_ov100_0229c2b0(param, 2);
    *(int *) ((char *) param + 0x28c4) = func_ov002_02207f60(param);
}

void func_ov100_0229e668(void *arg)
{
    int cond;
    int zero;

    cond = func_ov002_02207f48(arg, 0);
    zero = 0;
    func_ov002_02207e80(arg, 6, zero, zero);
    *(int *) ((char *) arg + 0x28C4) = func_ov002_02207f60(arg);

    if (cond != 0) {
        func_ov100_0229e218(arg);
        func_ov002_02207f20(arg, 2, zero, 1, 0x30);
        func_ov002_02207e90(arg, 0x80);
        func_ov100_0229c2b0(arg, 0x80);
        func_02002708(4);
        func_ov002_02207e80(arg, 4, zero, zero);
        *(int *) ((char *) arg + 0x28C8) = func_ov002_02207f60(arg);
        func_ov002_02208090(arg, 3);
    }
}

void func_ov100_0229e62c(UnkStruct_0229e62c *p)
{
    if (func_ov002_02207f48((void *) p, 0)) {
        func_ov002_022080a0((void *) (p), 2);
        func_ov100_0229d8b0(p);
    }
    func_ov002_02207e80((void *) p, 4, 0, 0);
    p->unk_28C8 = func_ov002_02207f60((void *) p);
}

void func_ov100_0229e5b8(void *param)
{
    if (func_ov100_0229c2d8(param) == 0) {
        return;
    }
    func_ov002_02207d24((char *) param + 0x218c, 1);
    func_ov100_0229cc3c(param);
    func_ov092_02299324(func_020ee45c(param), 0x44, 1);
    func_ov002_02207f04(param, 2, 4, 1, 0x30);
    func_ov002_02207e90(param, 0x80);
    func_ov002_02207e80(param, 4, 0, 0);
    *((int *) ((char *) param + 0x28c8)) = func_ov002_02207f60(param);
    func_ov002_02208090(param, 5);
}

void func_ov100_0229e54c(struct UnkStruct_0229e54c *this)
{
    int zero = 0;

    if (func_ov002_02207f3c(this, 0)) {
        func_020027f0(4);
        func_ov100_0229c2a0(this, 0x80);
        func_ov002_02207f04((void *) this, 8, zero, zero, 0x30);
        func_ov002_02207e80((void *) this, 6, zero, zero);
        func_ov002_02208090((void *) this, 6);
        func_ov100_0229e4fc((struct Context *) this);
    } else {
        func_ov002_02207e80((void *) this, 4, zero, zero);
        this->unk_28C8 = func_ov002_02207f60((void *) this);
    }
}

void func_ov100_0229e4fc(struct Context *p)
{
    if (func_ov002_02207f3c((struct UnkStruct_0229e54c *) p, 0)) {
        func_020027f0(6);
        func_ov002_022080a0((void *) (p), 5);
        func_ov100_0229c2a0((struct UnkStruct_0229e54c *) p, 1);
        func_ov100_0229c2a0((struct UnkStruct_0229e54c *) p, 2);
    } else {
        func_ov002_02207e80((void *) p, 6, 0, 0);
    }
    p->value = func_ov002_02207f60((void *) p);
}

void func_ov100_0229e400(void *self)
{
    int ret;
    int i;

    *(u32 *) ((char *) self + 0x28c0) = 0;
    func_ov094_0229af40((char *) self + 0xcc, 1);
    func_ov094_0229bbd8((char *) self + 0xb2c, 2);
    func_ov094_0229a2b0((char *) self + 0xb54, 6);
    ((u8 *) self)[0x291f] = 0x20;
    func_ov002_02209e18((char *) self + 0x225c);
    ((u8 *) self)[0x291d] = 0;
    ((u8 *) self)[0x2921] = 0;
    func_ov002_02209984((char *) self + 0x22d8, 3, 1, 0);
    ((u8 *) self)[0x2927] = 0;

    ret = func_0206fca4();

    switch (ret) {
        case 29:
        case 30:
            for (i = 0; i < 15; i++) {
                ((u16 *) ((char *) self + 0x28dc))[i] = 0xfff1;
            }
            func_ov100_0229c2b0(self, 0x200);
            break;
        case 31:
            MI_CpuCopy8(data_021f3a68, (char *) self + 0x28dc, 0x1e);
            break;
        case 32:
            MI_CpuCopy8(data_021f3a86, (char *) self + 0x28dc, 0x1e);
            break;
    }

    MI_CpuCopy8((char *) self + 0x28dc, (char *) self + 0x28fa, 0x1e);
    func_0206fb58();
}

void func_ov100_0229e3cc(void *r0)
{
    void *r4 = r0;
    func_ov100_0229d63c(r4);
    func_ov094_0229a038((char *) r4 + 0xb54);
    func_ov094_0229af18((char *) r4 + 0xcc);
    func_ov002_02209178((char *) r4 + 0x22d8);
    func_ov100_0229c5e0(r4);
}
