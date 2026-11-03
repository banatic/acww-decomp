/* store_front_2: 9 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_0221edf4 @ 0x0221edf4, 0x1c bytes, Thumb
 * func_ov003_0221edd0 @ 0x0221edd0, 0x24 bytes, Thumb
 * func_ov003_0221edac @ 0x0221edac, 0x24 bytes, Thumb
 * func_ov003_0221ed80 @ 0x0221ed80, 0x2c bytes, Thumb
 * func_ov003_0221ed60 @ 0x0221ed60, 0x20 bytes, Thumb
 * func_ov003_0221ed58 @ 0x0221ed58, 0x8 bytes, Thumb
 * func_ov003_0221ed50 @ 0x0221ed50, 0x8 bytes, Thumb
 * func_ov003_0221ed48 @ 0x0221ed48, 0x8 bytes, Thumb
 * func_ov003_0221ec24 @ 0x0221ec24, 0x124 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_0221edd0 {
    void *unk_00;
    char pad_04[0xe8];
    void *unk_EC;
};

struct func_ov003_0221ed80_obj {
    int *unk_00;
    char pad_04[0xe8];
    int *unk_EC;
};

typedef struct {
    char pad_00[0x136];
    char unk_136;
    char pad_137[0x2b4 - 0x136 - 1];
    int unk_2B4;
} UnkStruct_0221ed60;

struct UnkStruct_0221ec24 {
    u8 pad_00[0xec];
    u8 sub[0x1e];
    u8 unk_10A;
    u8 pad_10B[0x236 - 0x10b];
    struct {
        u8 bit0 : 1;
        u8 bit1 : 1;
        u8 rest : 6;
    } unk_236;
    u8 pad_237[0x2b4 - 0x237];
    u32 unk_2B4;
};

extern int func_020edf70(int);
extern void *func_ov009_0226552c(void *self);
extern int data_ov003_02239754;
extern int data_ov003_02239818;
extern void *func_ov009_0226539c(void *p);
extern void func_020edf54(void *p);
extern int func_0204bb80(void *addr);
extern int *func_ov009_02264c10(void *argument0);
extern char *func_ov009_02264be0(void *argument0);
extern void *func_ov009_02264b64(void *argument0);
extern void func_020a8164(void *dst, const void *src);
extern int func_020984e8(void);
extern int func_020a12e8(void);
extern int func_02099020(int p, int n);
extern int func_ov003_0221eb48(void *self);
extern void *func_020afad4(void *p);
extern void func_0209e474(void *p);
extern int func_020af90c(void *p);
extern int func_020af950(void *p);
extern int func_020af9f0(void *p);
extern const char data_ov003_02239890[];
extern const char data_ov003_022398a0[];
extern const char data_ov003_022398b0[];
extern char data_021f395c;

struct UnkStruct_0221edd0 *func_ov003_0221edd0(struct UnkStruct_0221edd0 *self);

void func_ov003_0221edf4(void)
{
    void *condition_value_16;
    condition_value_16 = (void *) (func_020edf70(0x2b8));
    if (condition_value_16 != 0) {
        func_ov003_0221edd0((struct UnkStruct_0221edd0 *) condition_value_16);
    }
}

struct UnkStruct_0221edd0 *func_ov003_0221edd0(struct UnkStruct_0221edd0 *self)
{
    func_ov009_0226552c(self);
    self->unk_00 = &data_ov003_02239754;
    self->unk_EC = &data_ov003_02239818;
    return self;
}

unsigned long *func_ov003_0221edac(unsigned long *p)
{
    p[0] = (unsigned long) ((unsigned long *) &data_ov003_02239754);
    p[59] = (unsigned long) ((unsigned long *) &data_ov003_02239818);
    func_ov009_0226539c(p);
    return p;
}

void *func_ov003_0221ed80(struct func_ov003_0221ed80_obj *self)
{
    self->unk_00 = &data_ov003_02239754;
    self->unk_EC = &data_ov003_02239818;
    func_ov009_0226539c(self);
    func_020edf54(self);
    return self;
}

int func_ov003_0221ed60(UnkStruct_0221ed60 *this)
{
    this->unk_2B4 = func_0204bb80(&this->unk_136);
    return 1;
}

void func_ov003_0221ed58(void *argument0)
{
    func_ov009_02264c10(argument0);
}

void func_ov003_0221ed50(void *argument0)
{
    func_ov009_02264be0(argument0);
}

void func_ov003_0221ed48(void *argument0)
{
    func_ov009_02264b64(argument0);
}

void func_ov003_0221ec24(struct UnkStruct_0221ec24 *self)
{
    struct {
        u8 pad[8];
        u32 w0;
        u32 w1;
    } local;
    int ret;
    int flag;

    func_020a8164(&self->sub, data_ov003_02239890);

    if (self->unk_2B4 == (u32) -1) {
        if (self->unk_236.bit1) {
            func_020a8164(&self->sub, data_ov003_022398a0);
            self->unk_10A = 0;
        } else {
            self->unk_10A = 4;
        }
        return;
    }

    ret = func_020984e8();

    if (func_020a12e8() != 0 || func_02099020(ret, 0x23) != 0) {
        func_020a8164(&self->sub, data_ov003_022398b0);
        self->unk_10A = 0x15;
        return;
    }

    if (func_ov003_0221eb48(self) != 0) {
        self->unk_10A = 7;
        return;
    }

    if (self->unk_236.bit1) {
        func_020a8164(&self->sub, data_ov003_022398a0);
        self->unk_10A = 0;
        return;
    }

    flag = 0;
    {
        void *base = &data_021f395c;
        if (((u8 *) func_020afad4(base))[3] != 0) {
            local.w0 = 0;
            local.w1 = 0;
            func_0209e474(&local.w0);
            if (func_020af90c(base) != 0) {
                if (((u8 *) &local)[0xa] > 12) {
                    flag = 1;
                }
            } else if (func_020af950(base) != 0) {
                flag = 1;
            } else if (func_020af9f0(base) != 0) {
                flag = 1;
            }
        }
    }

    if (flag != 0) {
        self->unk_10A = 7;
    } else {
        self->unk_10A = self->unk_2B4 & 3;
    }
}
