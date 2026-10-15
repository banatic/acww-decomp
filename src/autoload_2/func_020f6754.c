/* func_020f6754 @ 0x020f6754, 0x90 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

typedef struct {
    u8 pad_00[0x14];
    u8 unk_14[0x14];
    u8 unk_28[0x11];
    s8 unk_39;
    u8 unk_3A;
    u8 unk_3B;
    u8 unk_3C;
} UnkStruct_020f6754;

extern void func_020f6580(UnkStruct_020f6754 *, int);
extern int func_020f6564(UnkStruct_020f6754 *, int);
extern int func_020f1d3c(void *, int);
extern int func_020f7054(void *, u16, void *);

extern int data_021fd1bc;
extern u8 data_02138ff4[];

int func_020f6754(UnkStruct_020f6754 *self, unsigned int value)
{
    unsigned int next;
    self->unk_3C = 1;
    self->unk_39 = -1;
    if (value > 0xc8) {
        return (int) self;
    }

    func_020f6580(self, value + 0x263);
    next = value + 4;
    func_020f6564(self, next);
    self->unk_3B = (u8) func_020f1d3c(&data_021fd1bc, 0x30);
    return func_020f7054(&self->unk_14, (u16) next, data_02138ff4 + self->unk_3B * 16);
}
