/* func_020f58e0 @ 0x020f58e0, 0x34 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_020f58e0 {
    u8 pad_00[0x3c];
    u16 unk_3C;
} UnkStruct_020f58e0;

extern void func_020ef760(void *sub);
extern void func_020ef840(void *sub, int flag);

void func_020f58e0(UnkStruct_020f58e0 *self)
{
    void *arg2;
    func_020ef760(self ? (u8 *) self + 4 : (void *) self);
    arg2 = self;
    if (self != 0) {
        arg2 = (u8 *) self + 4;
    }
    func_020ef840(arg2, 1);
    self->unk_3C = 0;
}
