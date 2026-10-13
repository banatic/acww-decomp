/* func_ov125_022a0510 @ 0x022a0510, 0x54 bytes, Thumb, module ov125
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u8 pad_00[0x180];
    u8 sub180[1];
    u8 pad_181[0x574 - 0x181];
    u8 sub574[1];
    u8 pad_575[0x878 - 0x575];
    u16 unk_878;
    u8 unk_87A;
    u8 unk_87B;
    u8 unk_87C;
} UnkStruct_022a0510;

extern void func_ov002_02209984(void *p, int a, int b, int _x);
extern void func_0206fc4c(int arg);
extern void func_ov002_02207cec(void *p, int a);

void func_ov125_022a0510(UnkStruct_022a0510 *self)
{
    self->unk_878 = 0;
    func_ov002_02209984(self->sub180, 3, 1, 0);
    self->unk_87A = 9;
    self->unk_87B = 9;
    self->unk_87C = 0;
    func_0206fc4c(0);
    func_ov002_02207cec(self->sub574, 2);
}