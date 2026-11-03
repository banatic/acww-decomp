/* tune_editor_states_3: 14 functions, module ov143
 * mwccarm 1.2/base -O4,s
 * func_ov143_0229abf0 @ 0x0229abf0, 0x4 bytes, Thumb
 * func_ov143_0229abec @ 0x0229abec, 0x4 bytes, Thumb
 * func_ov143_0229abcc @ 0x0229abcc, 0x1e bytes, Thumb
 * func_ov143_0229ab68 @ 0x0229ab68, 0x64 bytes, Thumb
 * func_ov143_0229ab40 @ 0x0229ab40, 0x28 bytes, Thumb
 * func_ov143_0229ab08 @ 0x0229ab08, 0x38 bytes, Thumb
 * func_ov143_0229aad8 @ 0x0229aad8, 0x30 bytes, Thumb
 * func_ov143_0229aaac @ 0x0229aaac, 0x2a bytes, Thumb
 * func_ov143_0229aa70 @ 0x0229aa70, 0x3c bytes, Thumb
 * func_ov143_0229aa4c @ 0x0229aa4c, 0x24 bytes, Thumb
 * func_ov143_0229aa18 @ 0x0229aa18, 0x34 bytes, Thumb
 * func_ov143_0229a9f4 @ 0x0229a9f4, 0x24 bytes, Thumb
 * func_ov143_0229a98c @ 0x0229a98c, 0x68 bytes, Thumb
 * func_ov143_0229a964 @ 0x0229a964, 0x28 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_0229a98c {
    char pad_00[0x98];
    u16 unk_98;
    short unk_9A;
    char pad_9C[4];
    void *unk_A0;
    u8 unk_A4;
};

struct G040 {
    char pad_00[0x14];
    u16 unk_14;
};

struct G028 {
    char pad_00[0x14];
    unsigned short lo10 : 10;
};

extern int func_ov143_0229a16c(void *arg0);
extern void func_020ee470(int);
extern void func_ov143_0229a8dc(void);
extern void func_ov143_0229a868(void *);
extern void func_ov143_0229a7fc(void *);
extern void func_ov143_022996ec(void *);
extern void func_02002708(int);
extern void func_ov143_02299640(void *, int);
extern int func_ov002_0220ac04(void *);
extern void func_ov002_02208090(void *, int);
extern void func_ov002_02207f20(void *, int, int, int, int);
extern int func_ov002_02207f48(void *p, int a);
extern unsigned char *func_ov002_022080a0(void *p, unsigned char value);
extern void func_ov143_0229a2e0(void *p);
extern int func_020ee45c(void *);
extern void func_ov092_02299324(int, int, int);
extern void func_ov002_02207f04(void *, int, int, int, int);
extern void func_020027f0(int a);
extern void func_ov002_02207e80(void *p, int a, int b, int c);
extern int func_ov002_02207f60(void *p);
extern int func_ov002_02207f3c(void *p, int n);
extern void func_ov002_02207eb4(void *p, int a, int b);
extern int func_ov002_0220a8e8(void *p, int n);
extern void func_ov143_02299680(void *p);
extern void func_ov143_0229a284(void *p);
extern struct G040 data_ov143_0229b040;
extern struct G028 data_ov143_0229b028;
extern void func_0206ea5c(void *a, void *b);
extern unsigned char data_021cfbbc[];
extern unsigned char data_021f3b68[];
extern void func_020b9ccc(void *);
extern void func_ov143_02299a38(void *);
extern void func_ov002_0220af74(void *);

void func_ov143_0229aaac(void *p);

int func_ov143_0229abf0(void)
{
    return 1;
}

int func_ov143_0229abec(void)
{
    return 1;
}

int func_ov143_0229abcc(int arg0)
{
    int result;

    if (func_ov143_0229a16c((void *) arg0) == 0) {
        result = 1;
    } else {
        func_020ee470(arg0);
        result = 1;
    }
    return result;
}

void func_ov143_0229ab68(void *r0)
{
    func_ov143_0229a8dc();
    func_ov143_0229a868(r0);
    func_ov143_0229a7fc(r0);
    func_ov143_022996ec(r0);
    func_ov002_02207f20(r0, 10, 4, 0, 24);
    func_02002708(6);
    func_02002708(4);
    func_ov143_0229aaac(r0);
    func_ov143_02299640(r0, 1);
    func_ov002_0220ac04((char *) r0 + 0x110);
    func_ov002_02208090(r0, 1);
}

void func_ov143_0229ab40(void *p)
{
    if (func_ov002_02207f48(p, 0) != 0) {
        func_ov002_022080a0(p, 2);
        func_ov143_0229a2e0(p);
    }
    func_ov143_0229aaac(p);
}

void func_ov143_0229ab08(void *obj)
{
    func_ov092_02299324(func_020ee45c(obj), 0x44, 1);
    func_ov002_02207f04(obj, 0xa, 0, 0, 0x18);
    func_ov143_0229aaac(obj);
    func_ov002_02208090(obj, 3);
}

void func_ov143_0229aad8(int p)
{
    if (func_ov002_02207f3c((void *) p, 0)) {
        func_020027f0(6);
        func_020027f0(4);
        func_ov002_022080a0((void *) p, 5);
    } else {
        func_ov143_0229aaac((void *) p);
    }
}

void func_ov143_0229aaac(void *p)
{
    func_ov002_02207e80(p, 6, 0, 0);
    func_ov002_02207e80(p, 4, 0, 0);
    *(int *) ((char *) p + 0x94) = func_ov002_02207f60(p);
}

void func_ov143_0229aa70(void *p)
{
    if (func_ov002_02207f3c(p, -1)) {
        func_ov002_02208090(p, 5);
        func_ov002_02207eb4(p, 0, 0);
        func_ov002_0220a8e8((char *) p + 0x110, 0x8d);
        func_ov143_02299680(p);
    }
}

void func_ov143_0229aa4c(void *p)
{
    if (func_ov002_02207f48(p, -1)) {
        func_ov143_0229a284(p);
        func_ov002_022080a0(p, 2);
    }
}

void func_ov143_0229aa18(void *param)
{
    if (func_ov002_02207f3c(param, -1)) {
        func_ov002_02208090(param, 7);
        func_ov002_02207eb4(param, 0, 0);
        func_ov002_0220ac04((char *) param + 0x110);
    }
}

void func_ov143_0229a9f4(void *p)
{
    if (func_ov002_02207f48(p, -1)) {
        func_ov143_0229a2e0(p);
        func_ov002_022080a0(p, 2);
    }
}

void func_ov143_0229a98c(struct UnkStruct_0229a98c *self)
{
    self->unk_98 = 0;
    self->unk_A0 = (void *) data_021cfbbc;
    func_0206ea5c((void *) data_021f3b68, self->unk_A0);
    data_ov143_0229b040.unk_14 =
        (u16) ((data_ov143_0229b040.unk_14 & 0xfffffc00) | ((u16) (data_ov143_0229b028.lo10 + 4) & 0x3ff));
    self->unk_9A = -1;
    self->unk_A4 = 0;
}

void func_ov143_0229a964(void *self)
{
    func_020b9ccc((char *) self + 0x119c);
    func_ov143_02299a38(self);
    func_ov002_0220af74((char *) self + 0x110);
}
