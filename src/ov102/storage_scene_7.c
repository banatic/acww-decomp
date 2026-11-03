/* storage_scene_7: 9 functions, module ov102
 * mwccarm 1.2/base -O4,s
 * func_ov102_0229e32c @ 0x0229e32c, 0x54 bytes, Thumb
 * func_ov102_0229e308 @ 0x0229e308, 0x24 bytes, Thumb
 * func_ov102_0229e29c @ 0x0229e29c, 0x6c bytes, Thumb
 * func_ov102_0229e24c @ 0x0229e24c, 0x50 bytes, Thumb
 * func_ov102_0229e224 @ 0x0229e224, 0x28 bytes, Thumb
 * func_ov102_0229e1cc @ 0x0229e1cc, 0x58 bytes, Thumb
 * func_ov102_0229e1c4 @ 0x0229e1c4, 0x8 bytes, Thumb
 * func_ov102_0229e130 @ 0x0229e130, 0x94 bytes, Thumb
 * func_ov102_0229e108 @ 0x0229e108, 0x28 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_0229e29c {
    char pad_00[0x24d4];
    int unk_24D4;
};

typedef struct {
    char pad_00[0x24d0];
    int val;
} UnkStruct_0229e24c;

struct UnkStruct_0229e1cc {
    u8 pad_00[0x24d4];
    int unk_24D4;
    u8 pad_24D8[0xd1];
    u8 unk_25A9;
};

struct UnkStruct_0229e130 {
    char pad_00[0xcc];
    void *unk_CC;
    char pad_D0[0xb2c - (0xcc + 4)];
    void *unk_B2C;
    char pad_B30[0xb54 - (0xb2c + 4)];
    void *unk_B54;
    char pad_B58[0x225c - (0xb54 + 4)];
    void *unk_225C;
    char pad_2260[0x24cc - (0x225c + 4)];
    int unk_24CC;
    char pad_24D0[0x24e8 - (0x24cc + 4)];
    void *unk_24E8;
    char pad_24EC[0x259f - (0x24e8 + 4)];
    char unk_259F;
    char pad_25A0[0x25a1 - (0x259f + 1)];
    char unk_25A1;
    char pad_25A2[0x25a5 - (0x25a1 + 1)];
    char unk_25A5;
    char pad_25A6[0x25a8 - (0x25a5 + 1)];
    char unk_25A8;
    char pad_25A9[0x25aa - (0x25a8 + 1)];
    char unk_25AA;
};

extern void func_ov102_0229cb50(void *);
extern int func_ov002_02207d24(void *, int);
extern void func_ov002_02207f04(void *, int, int, int, int);
extern void func_ov002_02207e90(void *, int);
extern void func_ov002_02207e80(void *, int, int, int);
extern int func_ov002_02207f60(void *);
extern int func_020ee45c(int);
extern void func_ov092_02299324(int, int, int);
extern void func_ov002_02208090(int, int);
extern int func_ov002_02207f3c(struct UnkStruct_0229e29c *p, int a);
extern void func_020027f0(int size);
extern void func_ov102_0229c288(struct UnkStruct_0229e29c *p, int a);
extern unsigned char *func_ov002_022080a0(UnkStruct_0229e24c *p, unsigned char value);
extern void func_ov102_0229e4f4(struct UnkStruct_0229e1cc *);
extern void func_ov102_0229e380(void *parameter0);
extern void func_ov094_0229af40(void *ptr, int val);
extern void func_ov094_0229bbd8(void *ptr, int val);
extern void func_ov094_0229a2b0(void *ptr, int val);
extern void func_ov002_02209e18(void *ptr);
extern int func_020984e8(void);
extern void *func_0209898c(int object);
extern unsigned short *func_0203a674(void *record);
extern void MI_CpuCopy8(void *a, void *b, int c);
extern void func_0206fb58(void);
extern void func_ov102_0229d470(void *);
extern void func_ov094_0229a038(void *);
extern void func_ov094_0229af18(void *);
extern void func_ov102_0229c534(void *);

void func_ov102_0229e24c(UnkStruct_0229e24c *p);
void func_ov102_0229e1cc(struct UnkStruct_0229e1cc *self);

void func_ov102_0229e32c(void *r0)
{
    func_ov002_02207d24((char *) r0 + 0x218c, 1);
    func_ov102_0229cb50(r0);
    func_ov002_02207f04(r0, 2, 4, 1, 0x30);
    func_ov002_02207e90(r0, 0x90);
    func_ov002_02207e80(r0, 4, 0, 0);
    *(int *) ((char *) r0 + 0x24d4) = func_ov002_02207f60(r0);
}

void func_ov102_0229e308(int arg)
{
    func_ov102_0229e32c((void *) arg);
    func_ov092_02299324(func_020ee45c(arg), 0x44, 1);
    func_ov002_02208090(arg, 5);
}

void func_ov102_0229e29c(struct UnkStruct_0229e29c *param)
{
    if (func_ov002_02207f3c(param, 0) != 0) {
        func_020027f0(4);
        func_ov102_0229c288(param, 0x80);
        func_ov002_02207f04((void *) param, 8, 0, 0, 0x30);
        func_ov002_02207e80((void *) param, 6, 0, 0);
        func_ov002_02208090((int) param, 6);
        func_ov102_0229e24c((UnkStruct_0229e24c *) param);
    } else {
        func_ov002_02207e80((void *) param, 4, 0, 0);
        param->unk_24D4 = func_ov002_02207f60((void *) param);
    }
}

void func_ov102_0229e24c(UnkStruct_0229e24c *p)
{
    if (func_ov002_02207f3c((struct UnkStruct_0229e29c *) p, 0)) {
        func_020027f0(6);
        (func_ov002_022080a0(p, 5), (int) ((char *) (p) + 0x8f));
        func_ov102_0229c288((struct UnkStruct_0229e29c *) p, 1);
        func_ov102_0229c288((struct UnkStruct_0229e29c *) p, 2);
    } else {
        func_ov002_02207e80((void *) p, 6, 0, 0);
    }
    p->val = func_ov002_02207f60((void *) p);
}

void func_ov102_0229e224(void *self)
{
    func_ov102_0229e32c(self);
    func_ov002_02208090((int) self, 8);
    ((unsigned char *) self)[0x25a9] = 4;
    func_ov102_0229e1cc((struct UnkStruct_0229e1cc *) self);
}

void func_ov102_0229e1cc(struct UnkStruct_0229e1cc *self)
{
    if (func_ov002_02207f3c((struct UnkStruct_0229e29c *) self, 0) != 0) {
        func_020027f0(4);
        if (self->unk_25A9 != 0) {
            self->unk_25A9--;
        } else {
            func_ov102_0229e4f4(self);
            func_ov002_02208090((int) self, 9);
        }
    } else {
        func_ov002_02207e80((void *) self, 4, 0, 0);
        self->unk_24D4 = func_ov002_02207f60((void *) self);
    }
}

void func_ov102_0229e1c4(void *arg0)
{
    func_ov102_0229e380((void *) arg0);
}

void func_ov102_0229e130(struct UnkStruct_0229e130 *self)
{
    self->unk_24CC = 0;
    func_ov094_0229af40(&self->unk_CC, 1);
    func_ov094_0229bbd8(&self->unk_B2C, 2);
    func_ov094_0229a2b0(&self->unk_B54, 6);
    self->unk_25A1 = 0x25;
    func_ov002_02209e18(&self->unk_225C);
    self->unk_259F = 0;
    self->unk_25A5 = 0;
    self->unk_25A8 = 0;
    MI_CpuCopy8(func_0203a674(func_0209898c(func_020984e8())), &self->unk_24E8, 0xb4);
    func_0206fb58();
    self->unk_25AA = 0;
}

void func_ov102_0229e108(void *p)
{
    func_ov102_0229d470(p);
    func_ov094_0229a038((char *) p + 0xb54);
    func_ov094_0229af18((char *) p + 0xcc);
    func_ov102_0229c534(p);
}
