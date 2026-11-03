/* obj_020dd33c_4: 7 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02059b5c @ 0x02059b5c, 0x10 bytes, Thumb
 * func_02059ac4 @ 0x02059ac4, 0x98 bytes, Thumb
 * func_020599a8 @ 0x020599a8, 0x11c bytes, Thumb
 * func_0205996c @ 0x0205996c, 0x3a bytes, Thumb
 * func_0205992c @ 0x0205992c, 0x3e bytes, Thumb
 * func_02059920 @ 0x02059920, 0xc bytes, Thumb
 * func_02059904 @ 0x02059904, 0x1c bytes, Thumb
 */

#include "types.h"

typedef struct UnkStruct_02059ac4 {
    unsigned char pad_00[0x50];
    unsigned short u16_50;
    unsigned char pad_52[0x58 - 0x52];
    unsigned char u8_58;
    unsigned char pad_59[0x78 - 0x59];
    unsigned int u32_78;
    unsigned int u32_7c;
    unsigned int u32_80;
    unsigned int u32_84;
    unsigned int u32_88;
    unsigned int u32_8c;
    unsigned char pad_90[0xa8 - 0x90];
    unsigned int u32_a8;
    unsigned int u32_ac;
    unsigned int u32_b0;
    unsigned char pad_B4[0xbc - 0xb4];
    unsigned int u32_bc;
    unsigned int u32_c0;
    unsigned int u32_c4;
    unsigned char u8_c8;
    unsigned char pad_C9[0xcc - 0xc9];
    unsigned int u32_cc[2];
    unsigned char u8_d4;
    unsigned char pad_D5[0xd6 - 0xd5];
    unsigned short u16_d6;
    unsigned char u8_d8;
} UnkStruct_02059ac4;

typedef struct UnkStruct_020599a8 {
    u8 pad_00[0x50];
    u16 unk_50;
    u8 pad_52[2];
    int unk_54;
    u8 unk_58;
    u8 pad_59[3];
    int unk_5C;
    u8 pad_60[0xbc - 0x60];
    int unk_BC;
    u8 pad_C0[4];
    int unk_C4;
    u8 unk_C8;
    u8 pad_C9[3];
    int unk_CC;
    int unk_D0;
} UnkStruct_020599a8;

struct UnkStruct_0205996c {
    char pad_00[0xcc];
    void *unk_CC[2];
};

struct UnkStruct_0205992c {
    char pad_00[0xcc];
    int unk_CC;
    int unk_D0;
};

extern void func_02059694(unsigned char *);
extern unsigned int data_020cbafc;
extern void func_02059674(UnkStruct_02059ac4 *, int);
extern int func_0204bcdc(u16 *x);
extern int func_0204bc64(u16 *x);
extern int func_020b65c4(void);
extern int func_0204fea4(void);
extern int data_020cbaf8;
extern int func_0203efbc(void *x);
extern unsigned char data_020cbae8;

void func_02059920(void *param1);
void func_02059904(unsigned char *arg0, unsigned char arg1);

int func_02059b5c(unsigned char *argument0)
{
    func_02059694((unsigned char *) argument0);
    return 1;
}

void func_02059ac4(UnkStruct_02059ac4 *self)
{
    int i;

    self->u8_c8 = 0;
    for (i = 0; i < 2; i++) {
        self->u32_cc[i] = 0;
    }

    self->u16_50 = 0xfff1;
    self->u8_58 = 0xc;
    self->u16_d6 = 0;
    self->u8_d4 = 0;

    func_02059920((void *) self);

    self->u32_84 = 0;
    self->u32_88 = 0;
    self->u32_8c = 0;
    self->u32_78 = 0;
    self->u32_7c = 0;
    self->u32_80 = 0;
    self->u32_a8 = 0;
    self->u32_ac = 0;
    self->u32_b0 = 0;
    self->u8_d8 = 0;

    func_02059674(self, 0);

    self->u32_bc = data_020cbafc;
    self->u32_c4 = -1;
}

int func_020599a8(UnkStruct_020599a8 *p, u16 *src, int a3, u8 a4, int a5, int a6, int a7)
{
    int t;
    int b;
    u16 tmp;

    if (p->unk_C8 == 0 && a6 != 0) {
        p->unk_50 = *src;
        p->unk_54 = a3;
        p->unk_58 = a4;
        p->unk_5C = a5;
        p->unk_CC = a6;
        p->unk_D0 = a7;
        if (func_0204bcdc(&p->unk_50)) {
            tmp = 0x1565;
            t = (func_0204bc64(&p->unk_50) == func_0204bc64(&tmp));
        } else {
            t = (p->unk_50 == 0x1565);
        }
        if ((t && p->unk_54 == 0) || ((b = (p->unk_50 >= 0x1492 && p->unk_50 <= 0x14fd)) == 1 && p->unk_54 == 2)) {
            if (func_020b65c4() == 9 || func_020b65c4() == 0x10) {
                p->unk_BC = data_020cbaf8;
            } else {
                p->unk_BC = (*(int *) &data_020cbafc);
            }
        } else {
            p->unk_BC = (*(int *) &data_020cbafc);
        }
        b = 0;
        if (p->unk_50 >= 0x12e8 && p->unk_50 <= 0x131f) {
            b = 1;
        }
        if (b) {
            p->unk_C4 = func_0204fea4();
        }
    }
    return 0;
}

int func_0205996c(struct UnkStruct_0205996c *p, void *q, unsigned int i)
{
    if (i < 2) {
        if (p->unk_CC[i] != 0 && func_0203efbc(q) == func_0203efbc(*(void **) ((char *) p + i * 4 + 0xcc))) {
            return 1;
        }
    }
    return 0;
}

int func_0205992c(struct UnkStruct_0205992c *p, int val)
{
    int result = 0;
    if (func_0205996c((struct UnkStruct_0205996c *) p, (void *) val, 1) == 1) {
        p->unk_D0 = p->unk_CC;
        p->unk_CC = val;
        result = 1;
    } else {
        if (func_0205996c((struct UnkStruct_0205996c *) p, (void *) val, 0) == 1) {
            result = 1;
        }
    }
    return result;
}

void func_02059920(void *param1)
{
    func_02059904((unsigned char *) param1, 0xc);
}

void func_02059904(unsigned char *arg0, unsigned char arg1)
{
    unsigned char *r2;
    unsigned char *r0;
    unsigned char r1;

    r2 = arg0 + 0xda;
    *r2 = arg1;
    if (arg1 == 1 || arg1 == 7) {
        r1 = data_020cbae8;
        r0 = arg0 + 0xd5;
        *r0 = r1;
    }
}
