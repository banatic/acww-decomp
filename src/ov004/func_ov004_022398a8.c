/* func_ov004_022398a8 @ 0x022398a8, 0x9c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_022398a8 {
    u8 pad_00[0x100];
    int unk_100;
    int unk_104;
    int unk_108;
    u8 pad_10C[0x1c6 - 0x10c];
    u8 unk_1C6;
    u8 pad_1C7[0x22e - 0x1c7];
    u8 unk_22E;
};

extern int func_02056f28(void *p, int a);
extern void func_ov004_02239820(struct UnkStruct_022398a8 *self, int k);

void func_ov004_022398a8(struct UnkStruct_022398a8 *self, int n)
{
    if (self->unk_1C6 != 0) {
        if (self->unk_22E != 0) {
            if (func_02056f28(&self->unk_100, n) != 0) {
                self->unk_108 = (u16) (n - 1) << 12;
            }
        } else {
            if (func_02056f28(&self->unk_100, (u16) ((((unsigned int) self->unk_104 << 4) >> 16) - 1)) != 0) {
                if (n == 0xa) {
                    func_ov004_02239820(self, 2);
                } else {
                    func_ov004_02239820(self, 1);
                }
                self->unk_22E = 1;
            }
        }
    } else {
        if (func_02056f28(&self->unk_100, n) != 0) {
            self->unk_108 = (u16) (n - 1) << 12;
        }
    }
}
