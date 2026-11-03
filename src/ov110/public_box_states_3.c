/* public_box_states_3: 12 functions, module ov110
 * mwccarm 1.2/base -O4,s
 * func_ov110_0229e748 @ 0x0229e748, 0x4 bytes, Thumb
 * func_ov110_0229e744 @ 0x0229e744, 0x4 bytes, Thumb
 * func_ov110_0229e734 @ 0x0229e734, 0x10 bytes, Thumb
 * func_ov110_0229e718 @ 0x0229e718, 0x1c bytes, Thumb
 * func_ov110_0229e68c @ 0x0229e68c, 0x8c bytes, Thumb
 * func_ov110_0229e60c @ 0x0229e60c, 0x7e bytes, Thumb
 * func_ov110_0229e5d4 @ 0x0229e5d4, 0x38 bytes, Thumb
 * func_ov110_0229e564 @ 0x0229e564, 0x70 bytes, Thumb
 * func_ov110_0229e4fc @ 0x0229e4fc, 0x68 bytes, Thumb
 * func_ov110_0229e4b0 @ 0x0229e4b0, 0x4a bytes, Thumb
 * func_ov110_0229e3c4 @ 0x0229e3c4, 0xec bytes, Thumb
 * func_ov110_0229e38c @ 0x0229e38c, 0x38 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_0229e60c {
    char pad_00[0x98];
    void *unk_98;
    void *unk_9C;
};

struct UnkStruct_0229e5d4 {
    char pad_00[0x9c];
    int unk_9C;
};

typedef struct UnkStruct_0229e4fc {
    char pad_00[0x9c];
    int unk_9C;
} UnkStruct_0229e4fc;

typedef struct {
    char pad_00[0x98];
    int unk_98;
} UnkStruct_0229e4b0;

struct UnkStruct_0229e3c4 {
    u8 pad_00[0x94];
    u32 unk_94;
    u8 pad_98[0xb0 - 0x98];
    u16 arr1[15];
    u16 arr2[15];
    u8 pad_EC[0xf1 - 0xec];
    u8 unk_F1;
    u8 pad_F2[0xf3 - 0xf2];
    u8 unk_F3;
    u8 pad_F4[0xf5 - 0xf4];
    u8 unk_F5;
    u8 pad_F6[0xfb - 0xf6];
    u8 unk_FB;
    u8 pad_FC[0x138 - 0xfc];
    u32 unk_138;
    u8 pad_13C[0xb98 - 0x13c];
    u32 unk_B98;
    u8 pad_B9C[0xbc0 - 0xb9c];
    u32 unk_BC0;
    u8 pad_BC4[0x22c8 - 0xbc4];
    u32 unk_22C8;
    u8 pad_22CC[0x2344 - 0x22cc];
    u32 unk_2344;
};

extern void func_020ee470(void *argument0);
extern void func_ov110_0229e2c4(void);
extern void func_ov110_0229e2b0(void *);
extern void func_ov002_02208090(void *, int);
extern unsigned int func_ov110_0229e1cc(void *p);
extern void func_ov094_0229ad20(void *p);
extern void func_ov094_0229ace4(void *p, void *q);
extern void func_ov110_0229d17c(void *p);
extern void func_ov094_0229b2b0(void *p);
extern void func_ov094_0229b794(void *p, int n);
extern void func_ov002_02207f20(void *p, int a, int b, int c, int d);
extern void func_02002708(int n);
extern void func_ov002_02207e80(void *p, int a, int b, int c);
extern void func_ov110_0229c2b8(void *p, int a);
extern int func_ov002_02207f60(void *p);
extern int func_ov002_02207f48(void *, int);
extern void func_ov002_02207e90(void *, int);
extern void func_ov110_0229e1dc(void *);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);
extern void func_ov110_0229d840(void *);
extern int func_ov110_0229c2dc(unsigned int);
extern void func_ov110_0229cbe0(unsigned int);
extern int func_ov002_02207d24(char *, int);
extern int func_020ee45c(unsigned int);
extern void func_ov092_02299324(int, int, int);
extern void func_ov002_02207f04(unsigned int, int, int, int, int);
extern int func_ov002_02207f3c(void *, int);
extern void func_020027f0(int);
extern void func_ov110_0229c2a8(void *, int);
extern void func_ov094_0229af40(void *, int);
extern void func_ov094_0229bbd8(void *, int);
extern void func_ov094_0229a2b0(void *, int);
extern void func_ov002_02209e18(void *);
extern void func_ov002_02209984(void *, int, int, int _x);
extern int func_0206fca4(void);
extern void func_0206fb58(void);
extern void MI_CpuCopy8(void *, const void *, int);
extern unsigned char data_021f3a68[30];
extern unsigned char data_021f3a86[30];
extern void func_ov110_0229d5f0(void *);
extern void func_ov094_0229a038(void *);
extern void func_ov094_0229af18(void *);
extern void func_ov002_02209178(void *);
extern void func_ov110_0229c574(void *);

void func_ov110_0229e4b0(UnkStruct_0229e4b0 *p);

int func_ov110_0229e748(void)
{
    return 1;
}

int func_ov110_0229e744(void)
{
    return 1;
}

int func_ov110_0229e734(void *argument0)
{
    func_020ee470(argument0);
    return 1;
}

void func_ov110_0229e718(void *arg0)
{
    func_ov110_0229e2c4();
    func_ov110_0229e2b0(arg0);
    func_ov002_02208090(arg0, 1);
}

void func_ov110_0229e68c(void *self)
{
    func_ov110_0229e1cc(self);
    func_ov094_0229ad20((char *) self + 0x138);
    func_ov094_0229ace4((char *) self + 0x138, (char *) self + 0xb0);
    func_ov110_0229d17c(self);
    func_ov094_0229b2b0((char *) self + 0xb98);
    func_ov094_0229b794((char *) self + 0xb98, 0xf);
    func_ov002_02207f20(self, 8, 0, 0, 0x30);
    func_02002708(6);
    func_ov002_02207e80(self, 6, 0, 0);
    func_ov002_02208090(self, 2);
    func_ov110_0229c2b8(self, 1);
    func_ov110_0229c2b8(self, 2);
    *(int *) ((char *) self + 0x98) = func_ov002_02207f60(self);
}

void func_ov110_0229e60c(void *p)
{
    struct UnkStruct_0229e60c *s = (struct UnkStruct_0229e60c *) p;
    int cond;
    int zero = 0;

    cond = func_ov002_02207f48(s, 0);
    func_ov002_02207e80(s, 6, zero, zero);
    s->unk_98 = (void *) func_ov002_02207f60(s);
    if (cond != 0) {
        func_ov110_0229e1dc(s);
        func_ov002_02207f20(s, 2, zero, 1, 0x30);
        func_ov002_02207e90(s, 0x80);
        func_ov110_0229c2b8(s, 0x80);
        func_02002708(4);
        func_ov002_02207e80(s, 4, zero, zero);
        s->unk_9C = (void *) func_ov002_02207f60(s);
        func_ov002_02208090(s, 3);
    }
}

void func_ov110_0229e5d4(struct UnkStruct_0229e5d4 *self)
{
    int zero = 0;

    if (func_ov002_02207f48(self, zero)) {
        func_ov002_022080a0((void *) (self), 2);
        func_ov110_0229d840(self);
    }
    func_ov002_02207e80(self, 4, zero, zero);
    self->unk_9C = func_ov002_02207f60(self);
}

void func_ov110_0229e564(unsigned int param0)
{
    if (func_ov110_0229c2dc(param0) != 0) {
        unsigned int value;
        char *p;

        func_ov002_02207d24((char *) param0 + 0x21f8, 1);
        func_ov110_0229cbe0(param0);
        func_ov092_02299324(func_020ee45c(param0), 0x44, 1);
        func_ov002_02207f04(param0, 2, 4, 1, 0x30);
        func_ov002_02207e90((void *) param0, 0x80);
        func_ov002_02207e80((void *) param0, 4, 0, 0);
        value = (unsigned int) func_ov002_02207f60((void *) param0);
        p = (char *) param0;
        p += 0x9c;
        *(unsigned int *) p = value;
        func_ov002_02208090((void *) param0, 5);
    }
}

void func_ov110_0229e4fc(UnkStruct_0229e4fc *param)
{
    if (func_ov002_02207f3c(param, 0) != 0) {
        func_020027f0(4);
        func_ov110_0229c2a8(param, 0x80);
        func_ov002_02207f04((unsigned int) param, 8, 0, 0, 0x30);
        func_ov002_02207e80(param, 6, 0, 0);
        func_ov002_02208090(param, 6);
        func_ov110_0229e4b0((UnkStruct_0229e4b0 *) param);
    } else {
        func_ov002_02207e80(param, 4, 0, 0);
        param->unk_9C = func_ov002_02207f60(param);
    }
}

void func_ov110_0229e4b0(UnkStruct_0229e4b0 *p)
{
    if (func_ov002_02207f3c(p, 0)) {
        func_020027f0(6);
        func_ov002_022080a0((void *) (p), 5);
        func_ov110_0229c2a8(p, 1);
        func_ov110_0229c2a8(p, 2);
    } else {
        func_ov002_02207e80(p, 6, 0, 0);
    }
    p->unk_98 = func_ov002_02207f60(p);
}

void func_ov110_0229e3c4(struct UnkStruct_0229e3c4 *self)
{
    int v;
    int i;

    self->unk_94 = 0;
    func_ov094_0229af40(&self->unk_138, 1);
    func_ov094_0229bbd8(&self->unk_B98, 2);
    func_ov094_0229a2b0(&self->unk_BC0, 6);
    self->unk_F3 = 0x1f;
    func_ov002_02209e18(&self->unk_22C8);
    self->unk_F1 = 0;
    self->unk_F5 = 0;
    func_ov002_02209984(&self->unk_2344, 3, 1, 0);
    self->unk_FB = 0;

    v = func_0206fca4() - 0x1d;
    switch (v) {
        case 0:
        case 1:
            for (i = 0; i < 15; i++) {
                self->arr1[i] = 0xfff1;
            }
            func_ov110_0229c2b8((void *) self, 0x200);
            break;
        case 2:
            MI_CpuCopy8(data_021f3a68, self->arr1, 30);
            break;
        case 3:
            MI_CpuCopy8(data_021f3a86, self->arr1, 30);
            break;
    }
    MI_CpuCopy8(self->arr1, self->arr2, 30);
    func_0206fb58();
}

void func_ov110_0229e38c(void *self)
{
    func_ov110_0229d5f0(self);
    func_ov094_0229a038((char *) self + 0xbc0);
    func_ov094_0229af18((char *) self + 0x138);
    func_ov002_02209178((char *) self + 0x2344);
    func_ov110_0229c574(self);
}
