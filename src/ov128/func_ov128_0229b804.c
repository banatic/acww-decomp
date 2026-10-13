/* func_ov128_0229b804 @ 0x0229b804, 0x88 bytes, Thumb, module ov128
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u8 pad_00[0x2d5c];
    u32 word; // 0x2d5c
    u8 pad_2D60[0x2d6d - 0x2d60];
    u8 b6d; // 0x2d6d
    u8 b6e; // 0x2d6e
    u8 b6f; // 0x2d6f
} UnkStruct_0229b804;

extern void func_ov128_0229b8bc(UnkStruct_0229b804 *self);
extern void func_ov128_0229b90c(UnkStruct_0229b804 *self);

void func_ov128_0229b804(UnkStruct_0229b804 *self)
{
    switch (self->b6e) {
        case 1:
            if (self->b6d < 3) {
                self->b6d++;
            } else {
                self->b6e = 2;
                self->b6f = 20;
            }
            break;
        case 2:
            if (self->word == -1) {
                if (self->b6f != 0) {
                    self->b6f--;
                } else {
                    func_ov128_0229b8bc(self);
                }
            } else {
                self->b6f = 20;
            }
            break;
        case 3:
            if (self->b6d != 0) {
                self->b6d--;
            } else {
                func_ov128_0229b90c(self);
            }
            break;
        default:
            break;
    }
}
