/* func_ov003_0222c3e0 @ 0x0222c3e0, 0x34 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    char pad_00[0x30];
    u8 unk_30;
    char pad_31[3];
    int unk_34, unk_38, unk_3C, unk_40, unk_44, unk_48, unk_4C, unk_50, unk_54, unk_58;
} UnkStruct_0222c3e0;
void *func_02032c64(void *p);
void *func_ov003_0222c3e0(UnkStruct_0222c3e0 *self)
{
    func_02032c64(self);
    self->unk_30 = 0;
    self->unk_34 = 0x1000;
    self->unk_38 = 0x1000;
    self->unk_3C = 0x1000;
    self->unk_40 = 0x1000;
    self->unk_44 = 0x1000;
    self->unk_48 = 0x1000;
    self->unk_4C = 0x1000;
    self->unk_50 = 0x1000;
    self->unk_54 = 0x1000;
    self->unk_58 = 0;
    return self;
}
