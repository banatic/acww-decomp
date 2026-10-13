/* func_ov003_0220f884 @ 0x0220f884, 0x5c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u32 unk_00;
    u32 unk_04;
    u8 pad_08[3];
    u8 unk_0B;
    u8 unk_0C;
} UnkStruct_0220f884;

extern int func_02008258(void *self, int value);
extern int func_02056f94(void *ptr);
extern void func_ov003_0220f768(void *self, u32 a, u32 b, u8 c, int d, int e, int f);

void func_ov003_0220f884(void *self)
{
    UnkStruct_0220f884 *sub = (UnkStruct_0220f884 *) ((char *) self + 0x7d4);
    *(u32 *) ((char *) self + 0x7fc) = func_02008258(self, *(u32 *) ((char *) self + 0x7f0));
    if (sub->unk_0C != 0) {
        if (func_02056f94((char *) self + 0x2d0) != 0) {
            func_ov003_0220f768(self, sub->unk_00, sub->unk_04, sub->unk_0B, 1, 6, -1);
        }
    }
}
