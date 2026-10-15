/* func_ov129_0229b910 @ 0x0229b910, 0x90 bytes, Thumb, module ov129
 * mwccarm 1.2/base -O1,s
 */

#include "types.h"

typedef struct {
    u8 pad_00[0xaa];
    u16 unk_AA;   // 0xaa
    u8 pad_AC[4]; // 0xac-0xaf
    u8 unk_B0;    // 0xb0
    u8 unk_B1;    // 0xb1
    u8 unk_B2;    // 0xb2
} UnkStruct_0229b910;

extern unsigned short func_ov129_0229bbd8(UnkStruct_0229b910 *self, int previous, unsigned char current);
extern int func_ov129_0229b9d8(UnkStruct_0229b910 *self);
extern void func_ov129_0229b9a0(UnkStruct_0229b910 *self);
extern void func_ov002_0220a63c(void *p, int arg);

int func_ov129_0229b910(UnkStruct_0229b910 *self)
{
    int idx;
    int v;
    u8 t0;
    u8 t1;

    t0 = self->unk_B0;
    t1 = self->unk_B2;
    if (t1 != t0) {
        idx = func_ov129_0229bbd8(self, t1, t0);
        if (idx != 0xffff && ((u8 *) self + idx)[0x2f98] == 3) {
            self->unk_AA = (u16) idx;
        } else {
            v = func_ov129_0229b9d8(self);
            if (v != 0) {
                return v;
            }
        }
    }

    if (self->unk_AA != 0xffff && ((u8 *) self + self->unk_AA)[0x2f98] == 3) {
        self->unk_B1 = 2;
        *(u16 *) ((u8 *) self + 0x2f78) = self->unk_AA;
        func_ov002_0220a63c((u8 *) self + 0x1d4, 6);
        func_ov129_0229b9a0(self);
        return 2;
    }
    return 0;
}
