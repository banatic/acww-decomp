/* func_ov144_0229a5f4 @ 0x0229a5f4, 0xd4 bytes, Thumb, module ov144
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    char pad_00[0xba];
    s16 unk_BA;
    s16 unk_BC;
    char pad_BE[2];
    u8 unk_C0;
    char pad_C1[0x86c - 0xc1];
    u16 arr[4];
} UnkStruct_0229a5f4;

extern int func_02060a98(volatile u16 *p);
extern void func_ov144_0229a588(UnkStruct_0229a5f4 *self, int a);
extern int func_02099fe8(void);
extern void func_0209a088(volatile u16 *p, int a, int b);
extern void func_ov004_0223c310(void);
extern void func_02060984(int a);
extern void func_ov144_02299694(UnkStruct_0229a5f4 *self, int a);
extern void func_ov144_02299c2c(UnkStruct_0229a5f4 *self, int a);
extern void func_ov002_02208098(UnkStruct_0229a5f4 *self, int a);
extern void func_ov144_02299670(UnkStruct_0229a5f4 *self, int a);
extern void RtcSendPxiCommand(int a);
extern u8 data_020e54a8;

int func_ov144_0229a5f4(UnkStruct_0229a5f4 *self)
{
    volatile u16 t;
    int r;
    unsigned int ok;

    if (self->unk_BA == -1) {
        return 0;
    }
    t = self->arr[self->unk_BA];
    if (func_02060a98(&t) != 0) {
        func_ov144_0229a588(self, 0x20);
        return 1;
    }
    r = func_02099fe8();
    if (r == -1) {
        func_ov144_0229a588(self, 0x10);
        return 1;
    }
    func_0209a088(&t, 0, r);
    if (self->unk_BA == self->unk_BC) {
        ok = (data_020e54a8 == 0) ? 1 : 0;
        if (ok == 0) {
            func_ov004_0223c310();
        }
        self->unk_BC = -1;
    }
    func_02060984(self->arr[self->unk_BA]);
    func_ov144_02299694(self, self->unk_BA);
    self->unk_C0 = 0xa;
    func_ov144_02299c2c(self, 8);
    func_ov002_02208098(self, 0xa);
    func_ov144_02299670(self, 0x10);
    RtcSendPxiCommand(0x58);
    return 1;
}
