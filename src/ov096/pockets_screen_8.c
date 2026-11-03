/* pockets_screen_8: 8 functions, module ov096
 * mwccarm 1.2/base -O4,s
 * func_ov096_0229eb14 @ 0x0229eb14, 0x84 bytes, Thumb
 * func_ov096_0229eab4 @ 0x0229eab4, 0x60 bytes, Thumb
 * func_ov096_0229ea88 @ 0x0229ea88, 0x2c bytes, Thumb
 * func_ov096_0229ea5c @ 0x0229ea5c, 0x2c bytes, Thumb
 * func_ov096_0229ea34 @ 0x0229ea34, 0x28 bytes, Thumb
 * func_ov096_0229e9f8 @ 0x0229e9f8, 0x3c bytes, Thumb
 * func_ov096_0229e9a0 @ 0x0229e9a0, 0x58 bytes, Thumb
 * func_ov096_0229e95c @ 0x0229e95c, 0x44 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_0229eab4 {
    char pad_00[0xa4];
    int unk_A4;
    int unk_A8;
    char pad_AC[0xb1 - 0xac];
    unsigned char unk_B1;
};

typedef struct UnkStruct_0229ea5c {
    char pad_00[0xa4];
    int unk_A4;
    int unk_A8;
    char pad_AC[0x2454];
    char unk_2500[1];
} UnkStruct_0229ea5c;

struct UnkStruct_0229e9f8 {
    unsigned char pad_00;
};

struct UnkStruct_0229e9f8_2 {
    unsigned char pad_00[0xAC];
    unsigned short unk_AC;
    unsigned char pad_AE[2];
    unsigned char unk_B0;
    unsigned char unk_B1;
    unsigned char pad_B2[0x2A6];
    struct UnkStruct_0229e9f8 sub;
};

typedef struct UnkStruct_0229e9a0 {
    u8 pad_00[0xac];
    u16 ac;
    u8 pad_AE[2];
    u8 b0;
    u8 b1;
} UnkStruct_0229e9a0;

extern int func_ov096_0229f830(void *obj, unsigned char b);
extern int func_ov096_0229f820(void *obj, unsigned char b);
extern int func_ov096_0229f150(void *obj, unsigned char b);
extern int func_ov096_0229f810(void *obj, unsigned char b);
extern int func_ov096_0229f800(void *obj, unsigned char b);
extern void func_ov002_02207cf0(void *ptr);
extern void func_ov002_02207cf8(void *ptr);
extern int func_ov096_0229c2fc(void *self, int flag);
extern void func_ov094_0229a6bc(void *addr, int a4, int a8);
extern void func_ov094_0229b5e8(void *addr, int a4, int a8, void *addr2);
extern unsigned char data_021f6c58; // 0x021f6c58
extern unsigned char data_021f6c54; // 0x021f6c54
extern int func_ov002_02209f3c(void *);
extern int func_ov002_02209f14(void *);
extern int func_ov002_02209d84(char *p);
extern int func_ov002_02209d7c(char *p);
extern void func_ov094_0229a99c(void *sub, unsigned short a, unsigned char b);
extern void func_ov096_0229e258(void *p);
extern u16 func_ov096_0229f0dc(UnkStruct_0229e9a0 *self, UnkStruct_0229e9a0 *other);
extern u8 func_ov096_0229f088(UnkStruct_0229e9a0 *self, UnkStruct_0229e9a0 *other);
extern void func_ov096_0229f5ac(UnkStruct_0229e9a0 *self, UnkStruct_0229e9a0 *other);
extern int func_ov096_0229f548(void *p, unsigned int argument1);
extern int func_ov094_0229b8d8(void *p, int v);
extern int func_02066830(void *p, int v);
extern void func_ov094_0229b890(void *p, int v);

void func_ov096_0229eb14(void *obj)
{
    if (func_ov096_0229f830(obj, ((unsigned char *) obj)[0xb5]) != 0 ||
        func_ov096_0229f820(obj, ((unsigned char *) obj)[0xb5]) != 0) {
        if (func_ov096_0229f150(obj, ((unsigned char *) obj)[0xb5]) != 0) {
            func_ov002_02207cf0((char *) obj + 0x2418);
        } else {
            ((unsigned char *) obj)[0xb3] = ((unsigned char *) obj)[0xb5];
            func_ov002_02207cf8((char *) obj + 0x2418);
        }
    }
    if (func_ov096_0229f810(obj, ((unsigned char *) obj)[0xb5]) != 0 ||
        func_ov096_0229f800(obj, ((unsigned char *) obj)[0xb5]) != 0) {
        func_ov002_02207cf0((char *) obj + 0x2418);
    }
}

void func_ov096_0229eab4(struct UnkStruct_0229eab4 *self)
{
    unsigned char mode;

    if (func_ov096_0229c2fc(self, 0x40) != 0) {
        return;
    }
    mode = self->unk_B1;
    if (mode == 0) {
        return;
    }
    if (mode == 2) {
        func_ov094_0229a6bc((char *) self + 0x358, self->unk_A4, self->unk_A8);
        return;
    }
    if (mode == 1) {
        func_ov094_0229b5e8((char *) self + 0xdb8, self->unk_A4, self->unk_A8, (char *) self + 0x2e28);
    }
}

void func_ov096_0229ea88(void *p)
{
    int t;
    t = *(int *) ((char *) p + 0x9c);
    t += data_021f6c58;
    *(int *) ((char *) p + 0xa4) = t;

    t = *(int *) ((char *) p + 0xa0);
    t += data_021f6c54;
    *(int *) ((char *) p + 0xa8) = t;
}

int func_ov096_0229ea5c(UnkStruct_0229ea5c *self)
{
    self->unk_A4 = func_ov002_02209f3c(self->unk_2500) - 2;
    {
        int result = func_ov002_02209f14(self->unk_2500) - 4;
        self->unk_A8 = result;
        return result;
    }
}

void func_ov096_0229ea34(char *self)
{
    *(int *) (self + 0xa4) = func_ov002_02209d84(self + 0x24e8);
    *(int *) (self + 0xa8) = func_ov002_02209d7c(self + 0x24e8);
}

void func_ov096_0229e9f8(struct UnkStruct_0229e9f8_2 *p, unsigned short a, unsigned char b)
{
    p->unk_B1 = 2;
    p->unk_AC = a;
    p->unk_B0 = b;
    func_ov094_0229a99c(&p->sub, p->unk_AC, p->unk_B0);
    func_ov096_0229e258(p);
}

void func_ov096_0229e9a0(UnkStruct_0229e9a0 *self, UnkStruct_0229e9a0 *other)
{
    self->b1 = 2;
    self->ac = func_ov096_0229f0dc(self, other);
    self->b0 = func_ov096_0229f088(self, other);
    func_ov096_0229f5ac(self, other);
    func_ov094_0229a99c((char *) self + 0x358, self->ac, self->b0);
    func_ov096_0229e258((void *) self);
}

void func_ov096_0229e95c(void *obj, unsigned int argument1)
{
    int val = func_ov096_0229f548(obj, argument1);
    ((char *) obj)[0xb1] = 1;
    func_02066830((char *) obj + 0x2e28, func_ov094_0229b8d8((char *) obj + 0xdb8, val));
    func_ov094_0229b890((char *) obj + 0xdb8, val);
}
