/* func_ov112_022a02f4 @ 0x022a02f4, 0xb8 bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov112_0229f900(void *self);
extern void func_ov095_0229b3ec(void *ptr);
extern int func_ov095_0229b3a0(void *p, void *q, int _x);
extern void func_ov112_0229f89c(void *self);
extern void func_ov112_0229ff50(void *receiver);
extern void func_ov112_0229fd20(void *self);
extern void func_ov112_0229f668(void *self);
extern void func_0200467c(int cmd);

typedef struct UnkStruct_022a02f4 {
    u8 pad_00[0xbd];
    u8 unk_BD;      // 0xbd
    u8 unk_BE;      // 0xbe
    u8 unk_BF;      // 0xbf
    u8 unk_C0;      // 0xc0
    u8 pad_C1[3];   // 0xc1..0xc3
    u16 arr_c4[16]; // 0xc4
} UnkStruct_022a02f4;

int func_ov112_022a02f4(UnkStruct_022a02f4 *self, int flag)
{
    if (func_ov112_0229f900(self) != 0) {
        func_ov095_0229b3ec((char *) self + 0x384);
        func_ov112_0229f89c(self);
        goto fail_ret;
    }

    if (self->unk_BD > self->unk_C0) {
        if (func_ov095_0229b3a0((char *) self + 0x384, &self->arr_c4[0], self->unk_BD) != 0) {
            goto fail_ret;
        }
        self->unk_BE = self->unk_BD;
        self->unk_BF = self->unk_BD - 1;
        func_ov112_0229f89c(self);
        goto fail_ret;
    } else {
        if (self->arr_c4[self->unk_C0] != 0) {
            self->unk_BE = self->unk_C0;
            self->unk_BF = self->unk_C0 + 1;
            func_ov112_0229f89c(self);
            goto fail_ret;
        } else {
            if (flag != 0) {
                func_ov112_0229ff50(self);
            }
            return 0;
        }
    }

fail_ret:
    func_0200467c(0x35);
    func_ov112_0229fd20(self);
    func_ov112_0229f668(self);
    return 1;
}