/* func_ov129_0229d008 @ 0x0229d008, 0x108 bytes, Thumb, module ov129
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern u8 data_021fbdd8;
extern u8 data_021fbddc;
extern u8 data_021f6c58;
extern u8 data_021f6c54;

typedef struct UnkStruct_0229d008 {
    u8 pad_00[0xad];
    u8 unk_AD;
    u8 pad_AE[0x1d4 - 0xae];
    u8 sub1d4[1];
    u8 pad_1D5[0x734 - 0x1d5];
    u8 sub734[4];
} UnkStruct_0229d008;

extern int func_ov002_02208054(void *self, int x);
extern int func_ov127_02299d20(void *p, int a, int b);
extern void func_ov127_02299c08(void *p, u8 a, int b);
extern void func_ov002_02208098(void *self, int x);
extern int func_ov002_0220a620(void *p, int x);
extern int func_ov002_0220a784(void *p, int x);
extern void func_ov129_0229c848(UnkStruct_0229d008 *self);
extern void func_ov129_0229c1d4(UnkStruct_0229d008 *self);
extern void func_ov129_0229c79c(UnkStruct_0229d008 *self);
extern void func_ov129_0229c758(UnkStruct_0229d008 *self);
extern int func_ov129_0229bd4c(UnkStruct_0229d008 *self, int a, int b);
extern int func_ov129_0229b800(UnkStruct_0229d008 *self);
extern void func_ov129_0229c170(UnkStruct_0229d008 *self);
extern void func_ov129_0229c140(UnkStruct_0229d008 *self);

void func_ov129_0229d008(UnkStruct_0229d008 *self)
{
    if (func_ov002_02208054(self, 1)) {
        func_ov129_0229c848(self);
        func_ov129_0229c1d4(self);
        return;
    }
    {
        unsigned int cond = (data_021fbdd8 != 0 && data_021fbddc != 0);
        if (cond > 0) {
            int a = data_021f6c58;
            int b = data_021f6c54;
            self->unk_AD = func_ov127_02299d20(self->sub734, a, b);
            if (self->unk_AD != 4) {
                func_ov127_02299c08(self->sub734, self->unk_AD, 0);
                func_ov002_02208098(self, 1);
                func_ov129_0229c1d4(self);
                return;
            }
            if (func_ov002_0220a620(self->sub1d4, 6) == 0) {
                if (func_ov002_0220a784(self->sub1d4, 6) != 0) {
                    func_ov129_0229c79c(self);
                    func_ov129_0229c1d4(self);
                    return;
                }
            }
            if (func_ov002_0220a784(self->sub1d4, 5) != 0) {
                func_ov129_0229c758(self);
                func_ov129_0229c1d4(self);
                return;
            }
            if (func_ov129_0229bd4c(self, a, b) != 0) {
                switch (func_ov129_0229b800(self)) {
                    case 1:
                        return;
                    case 2:
                        func_ov129_0229c170(self);
                        return;
                    case 3:
                        return;
                    default:
                        break;
                }
            }
        }
        func_ov129_0229c140(self);
    }
}
