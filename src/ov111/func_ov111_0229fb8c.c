/* func_ov111_0229fb8c @ 0x0229fb8c, 0xac bytes, Thumb, module ov111
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov111_0229f4dc(void *self, int param1);
extern void func_ov095_0229b3ec(void *ptr);
extern int func_ov095_0229b3a0(void *ptr, void *ptr2, int _x);
extern void RtcSendPxiCommand(int cmd);
extern void func_ov111_0229fb48(void *self);
extern void func_ov111_0229fd08(void *self);
extern void func_ov111_0229f524(void *self);

typedef struct {
    u8 pad_00[0x9e];
    u8 unk_9E;
    u8 unk_9F;
    u8 unk_A0;
    u8 pad_A1[0xac - 0xa1];
    u8 unk_AC;
    u8 pad_AD[0x3d16 - 0xad];
    u16 unk_3D16;
} UnkStruct_0229fb8c;

int func_ov111_0229fb8c(UnkStruct_0229fb8c *self, int param1)
{
    if (func_ov111_0229f4dc(self, param1) != 0) {
        func_ov095_0229b3ec(&self->unk_AC);
        func_ov111_0229fb48(self);
    } else {
        if (self->unk_9E != 0) {
            if (func_ov095_0229b3a0(&self->unk_AC, (u8 *) self + 0x3d16, self->unk_9E) == 0) {
                self->unk_9F = self->unk_9E;
                self->unk_A0 = self->unk_9E - 1;
                func_ov111_0229fb48(self);
            }
        } else {
            if (self->unk_3D16 != 0) {
                self->unk_9F = 0;
                self->unk_A0 = 1;
                func_ov111_0229fb48(self);
            } else {
                if (param1 != 0) {
                    RtcSendPxiCommand(0x34);
                }
                return 0;
            }
        }
    }
    RtcSendPxiCommand(0x35);
    func_ov111_0229fd08(self);
    func_ov111_0229f524(self);
    return 1;
}