/* func_ov129_0229cb08 @ 0x0229cb08, 0xd4 bytes, Thumb, module ov129
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_0229cb08 {
    u8 pad_00[0x94];
    s32 unk_94;
    s32 unk_98;
    u8 pad_9C[0xad - 0x9c];
    u8 unk_AD;
    u8 unk_AE;
    u8 pad_end[0x734 - 0xaf];
} UnkStruct_0229cb08;

extern int func_0208e484(void *);
extern int func_ov129_0229b7ec(UnkStruct_0229cb08 *, int);
extern int func_ov129_0229bd4c(UnkStruct_0229cb08 *, s32, s32);
extern int func_ov129_0229b800(UnkStruct_0229cb08 *);
extern void func_ov129_0229c1f8(UnkStruct_0229cb08 *);
extern void func_ov129_0229c2fc(UnkStruct_0229cb08 *);
extern void func_ov129_0229c79c(UnkStruct_0229cb08 *);
extern void func_ov129_0229c758(UnkStruct_0229cb08 *);
extern void func_ov002_02208098(UnkStruct_0229cb08 *, int);
extern int func_ov002_0220a620(void *, int);
extern void func_ov127_02299c08(void *, s32, s32);

void func_ov129_0229cb08(UnkStruct_0229cb08 *self)
{
    if (func_0208e484((char *) self + 0x3a0) == 0) {
        return;
    }
    if (func_ov129_0229b7ec(self, 2)) {
        if (func_ov129_0229bd4c(self, self->unk_94, self->unk_98) != 0) {
            if (func_ov129_0229b800(self) == 3) {
                return;
            }
        }
        func_ov129_0229c1f8(self);
        func_ov002_02208098(self, 3);
        func_ov129_0229c2fc(self);
    } else {
        switch (self->unk_AE) {
            case 4:
                if (func_ov002_0220a620((char *) self + 0x1d4, 6) == 0) {
                    func_ov129_0229c79c(self);
                } else {
                    func_ov002_02208098(self, 4);
                    func_ov129_0229c2fc(self);
                }
                break;
            case 5:
                func_ov129_0229c758(self);
                break;
            case 0:
            case 1:
            case 2:
            case 3:
                self->unk_AD = self->unk_AE;
                func_ov127_02299c08((char *) self + 0x734, self->unk_AD, 0);
                func_ov002_02208098(self, 5);
                break;
            default:
                break;
        }
    }
}
