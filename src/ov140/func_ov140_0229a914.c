/* func_ov140_0229a914 @ 0x0229a914, 0xa0 bytes, Thumb, module ov140
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_0208e484(void *);
extern void func_ov140_0229a6dc(void *);
extern void func_ov140_0229a774(void *);
extern void func_ov140_0229a73c(void *);
extern void func_ov140_0229a3fc(void *, int _x);
extern void func_ov140_02299fa0(void *, int);
extern void RtcSendPxiCommand(int);
extern void func_ov002_02208098(void *, int);
extern void func_ov140_0229a544(void *);

typedef struct UnkStruct_0229a914 {
    u8 pad_00[0xa0];
    u32 unk_A0;
    u8 pad_A4[0x4];
    u32 unk_A8;
    u8 pad_AC[0x8af - 0xac];
    u8 arr1[0x31];
    u8 arr2[0x100];
    u8 pad_9E0[0x128c - (0x8e0 + 0x100)];
} UnkStruct_0229a914;

void func_ov140_0229a914(UnkStruct_0229a914 *self)
{
    if (func_0208e484((char *) self + 0x128c) != 0) {
        u8 c = self->arr1[0x2d];
        if (c == 6) {
            if (self->unk_A8 != 8) {
                goto tail;
            }
            func_ov140_0229a6dc(self);
            goto exit;
        } else if (c == 8) {
            if (self->unk_A0 != 8) {
                goto tail;
            }
            func_ov140_0229a774(self);
            goto exit;
        } else if (c == 7) {
            func_ov140_0229a73c(self);
            goto exit;
        } else {
            if (self->arr1[c] != 0 && self->arr2[c] != 4) {
                func_ov140_0229a3fc(self, c);
                RtcSendPxiCommand(0x29);
                func_ov140_02299fa0(self, 8);
                func_ov140_02299fa0(self, 0x10);
            }
        }
    tail:
        func_ov002_02208098(self, 1);
        func_ov140_0229a544(self);
    }
exit:
    return;
}