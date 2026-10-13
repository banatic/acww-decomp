/* func_ov105_0229d0f8 @ 0x0229d0f8, 0x5c bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0229d0f8 {
    u8 pad_00[0x2b4];
    u8 unk_2B4;
    u8 pad_2B5[0xAA7];
};

extern int func_ov105_0229d76c(struct UnkStruct_0229d0f8 *self, int arg);
extern int func_ov105_0229d75c(struct UnkStruct_0229d0f8 *self, int arg);
extern int func_ov105_0229d718(struct UnkStruct_0229d0f8 *self, int arg);
extern int func_ov094_0229b8d8(u8 *ptr, int arg);
extern void func_02066830(u8 *ptr, int arg);
extern void func_ov094_0229b890(u8 *ptr, int arg);

void func_ov105_0229d0f8(struct UnkStruct_0229d0f8 *self, int arg)
{
    int result;
    int temp;

    if (func_ov105_0229d76c(self, arg) == 0 && func_ov105_0229d75c(self, arg) == 0) {
        return;
    }

    result = func_ov105_0229d718(self, arg);
    self->unk_2B4 = 1;
    temp = func_ov094_0229b8d8((u8 *) self + 0xd5c, result);
    func_02066830((u8 *) self + 0xb4, temp);
    func_ov094_0229b890((u8 *) self + 0xd5c, result);
}
