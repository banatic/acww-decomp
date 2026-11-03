/* pockets_screen_16: 8 functions, module ov096
 * mwccarm 1.2/base -O4,s
 * func_ov096_0229ff54 @ 0x0229ff54, 0x8c bytes, Thumb
 * func_ov096_0229fecc @ 0x0229fecc, 0x88 bytes, Thumb
 * func_ov096_0229fe9c @ 0x0229fe9c, 0x30 bytes, Thumb
 * func_ov096_0229fe74 @ 0x0229fe74, 0x28 bytes, Thumb
 * func_ov096_0229fe10 @ 0x0229fe10, 0x64 bytes, Thumb
 * func_ov096_0229fdf8 @ 0x0229fdf8, 0x18 bytes, Thumb
 * func_ov096_0229fdb0 @ 0x0229fdb0, 0x48 bytes, Thumb
 * func_ov096_0229fd44 @ 0x0229fd44, 0x6a bytes, Thumb
 */

#include "types.h"

typedef struct {
    u8 pad_00[0xa4];
    u32 unk_A4;
    u32 unk_A8;
    u16 unk_AC;
    u8 pad_AE[0xc0 - 0xac - 2];
    u8 unk_C0;
} UnkStruct_0229ff54;

typedef struct {
    char pad_00[0xac];
    unsigned short unk_AC;
    char pad_AE[0xb4 - 0xac - 2];
    unsigned char unk_B4;
} UnkStruct_0229fecc;

struct UnkStruct_0229fdb0 {
    char pad_00[0xb6];
    u8 unk_B6;
};

typedef struct {
    char pad_00[0xB6];
    unsigned char unk_B6;
    char pad_B7[0x0A];
    volatile unsigned char unk_C1;
} UnkStruct_0229fd44;

extern u32 func_ov096_0229f290(void *self, int x);
extern u32 func_ov096_0229f200(void *self, int x);
extern void func_ov096_0229c434(void *self);
extern int func_ov096_0229e2fc(void *self, u32 b, u32 w);
extern u16 func_ov096_0229e3b0(void *self, u32 b, u32 w);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov094_02299d7c(void *ptr, int x);
extern unsigned char data_020e54a8;
extern int func_ov094_02299d40(void *p);
extern void func_ov096_0229e6a0(void *p);
extern void func_ov094_02299e1c(void *p);
extern int func_ov096_0229c2fc(void *p, int val);
extern unsigned char *func_ov096_0229f8cc(void *p, int a, unsigned char b, unsigned short c, int d);
extern void func_ov096_0229e9f8(void *p, unsigned short c, int d);
extern void func_ov096_0229e82c(void *p, int val);
extern int func_ov096_0229e2c8(void *self, unsigned char byte);
extern void func_ov094_02299d34(void *ptr);
extern void func_ov096_0229fb9c(void *self);
extern int func_ov094_0229b19c(void *);
extern int func_ov094_0229a3b0(const void *);
extern int func_020984e8(void);
extern void func_02098ff8(int, int);
extern void func_ov096_0229e898(void *, unsigned char, int);
extern int func_02096150(void);
extern void func_0200467c(u32 cmd);
extern u16 func_ov096_0229f0dc(struct UnkStruct_0229fdb0 *self, u8 b);
extern int func_02095aec(u16 *p);
extern void func_ov096_0229f5ac(struct UnkStruct_0229fdb0 *self, u8 b);
extern void func_ov096_0229ec90(UnkStruct_0229fd44 *p, unsigned char b);
extern void func_ov096_0229ed44(UnkStruct_0229fd44 *p);

void func_ov096_0229fe9c(void *self);

void func_ov096_0229ff54(UnkStruct_0229ff54 *self)
{
    u8 b;
    unsigned int flag;

    self->unk_A4 = func_ov096_0229f290(self, 0x24);
    self->unk_A8 = func_ov096_0229f200(self, 0x24);
    b = self->unk_C0;
    if (b == 5) {
        flag = (data_020e54a8 == 0) ? 1 : 0;
        if (flag == 0) {
            goto skip;
        }
    }
    func_ov096_0229c434(self);
skip:
    if (func_ov096_0229e2fc(self, b, self->unk_AC) != 0) {
        func_ov002_02208098((void *) (self), 0x26);
        self->unk_AC = func_ov096_0229e3b0(self, b, self->unk_AC);
        func_ov094_02299d7c((char *) self + 0xde0, 1);
    }
}

void func_ov096_0229fecc(UnkStruct_0229fecc *p)
{
    if (func_ov094_02299d40((char *) p + 0xde0) == 0) {
        return;
    }
    func_ov096_0229e6a0(p);
    func_ov094_02299e1c((char *) p + 0xde0);
    if (p->unk_AC != 0xfff1) {
        if (func_ov096_0229c2fc(p, 0x8000)) {
            func_ov096_0229f8cc(p, 0x24, p->unk_B4, p->unk_AC, 0);
            return;
        }
        func_ov096_0229e9f8(p, p->unk_AC, 0);
        func_ov096_0229e82c(p, 1);
    }
    func_ov002_02208098((void *) (p), 0x27);
    func_ov096_0229fe9c(p);
}

void func_ov096_0229fe9c(void *self)
{
    int ret = func_ov096_0229e2c8(self, *(unsigned char *) ((char *) self + 0xc0));
    if (ret != 0) {
        return;
    }
    func_ov096_0229e6a0(self);
    func_ov094_02299d34((char *) self + 0xde0);
    func_ov096_0229fb9c(self);
}

void func_ov096_0229fe74(void *arg0)
{
    if (func_ov094_0229b19c((char *) arg0 + 0xdb8)) {
        func_ov096_0229e6a0(arg0);
        func_ov096_0229fb9c(arg0);
    }
}

void func_ov096_0229fe10(void *ptr)
{
    if (func_ov094_0229a3b0((char *) ptr + 0x358) != 0) {
        int ret = func_020984e8();
        unsigned short val = *(unsigned short *) ((char *) ptr + 0xac);
        if (val == 0x136a) {
            func_02098ff8(ret, 0x27);
        } else if (val == 0x137b) {
            func_02098ff8(ret, 0x28);
        }
        *(unsigned char *) ((char *) ptr + 0xb0) = 0;
        func_ov096_0229e898(ptr, *(unsigned char *) ((char *) ptr + 0xb6), 1);
        func_ov096_0229fb9c(ptr);
    }
}

void func_ov096_0229fdf8(int param)
{
    if (func_02096150() != 0) {
        func_ov096_0229fb9c((void *) param);
    }
}

unsigned char *func_ov096_0229fdb0(struct UnkStruct_0229fdb0 *self)
{
    u16 temp;
    int result;
    func_0200467c(0x40);
    func_ov096_0229c434((void *) self);
    temp = func_ov096_0229f0dc(self, self->unk_B6);
    result = func_02095aec(&temp);
    if (result != 0) {
        func_ov096_0229f5ac(self, self->unk_B6);
        return func_ov002_02208098((void *) (self), 0x2f);
    }
    return (unsigned char *) result;
}

void func_ov096_0229fd44(UnkStruct_0229fd44 *p)
{
    int rem;
    if (p->unk_C1 != 0) {
        p->unk_C1 = p->unk_C1 - 1;
        rem = p->unk_C1 % 5;
        if (rem != 0) {
            if (rem == 3) {
                func_ov096_0229ec90(p, p->unk_B6);
            }
        } else {
            func_ov096_0229ed44(p);
        }
        if (p->unk_C1 == 0) {
            func_ov096_0229f5ac((struct UnkStruct_0229fdb0 *) p, (unsigned char) p->unk_B6);
        }
    } else {
        func_ov002_02208098((void *) (p), 0x2f);
        func_ov096_0229fdf8((int) p);
    }
}
