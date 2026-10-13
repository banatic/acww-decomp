/* func_02068a04 @ 0x02068a04, 0xcc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u32 unk_00;
    u32 unk_04;
    u16 data[4];
    int count;
    u8 pad_14[8];
    u8 flag1c;
    u8 flag1d;
    u8 flag1e;
    u8 pad_1F[5];
    u32 unk_24;
    u32 unk_28;
} UnkStruct_02068a04;

extern void func_020688e0(UnkStruct_02068a04 *self);
extern void func_020688dc(UnkStruct_02068a04 *self);
extern int func_02068958(UnkStruct_02068a04 *self);
extern int func_02068924(UnkStruct_02068a04 *self);
extern void RtcSendPxiCommand(int cmd);
extern void func_020045f4(int a, int b, int c, int d);
extern void func_020680ec(u32 p, int flag);
extern void func_020680d0(u32 p);
extern u16 data_020cb8f4;

void func_02068a04(UnkStruct_02068a04 *self)
{
    int res1, res2;
    int flag, i;
    u16 base, v;

    func_020688e0(self);
    func_020688dc(self);
    if (self->flag1c != 0 || self->flag1d != 0) {
    } else {
        res1 = func_02068958(self);
        res2 = func_02068924(self);
        if (self->count >= 1) {
            if (self->unk_24 == 5) {
                if (res1 != 2) {
                    RtcSendPxiCommand(0x2c);
                }
            } else {
                func_020045f4(res1, res2, self->data[0], self->data[1]);
            }
        }
        flag = 0;
        if (self->unk_28 != 4) {
            i = 0;
            base = data_020cb8f4;
            while (i < self->count) {
                v = self->data[i];
                if (v != base && v != 0x3000 && v != 0x0a && v != 0x30fb && v != 0xff01 && v != 0xff1f && v != 0xfe &&
                    v != 0xff0c) {
                    flag = 1;
                }
                i++;
            }
        }
        func_020680ec(self->unk_04, flag);
    }
    if (self->flag1e != 0) {
        func_020680d0(self->unk_04);
    }
}
