/* func_ov003_0221ec24 @ 0x0221ec24, 0x124 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

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