/* func_02036d24 @ 0x02036d24, 0xb6 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u8 pad_00[0x8];
    u16 unk_08;
    u16 unk_0A;
    u16 unk_0C;
    u8 pad_0E[5];
    u8 unk_13;
} UnkStruct_02036d24;

extern int func_02036648(UnkStruct_02036d24 *self);
extern int func_0203736c(int a, int b, int c, int d, int e, int f, int g);
extern void func_02036b14(UnkStruct_02036d24 *self);
extern void func_02036af4(UnkStruct_02036d24 *self);
extern void func_02036ad4(UnkStruct_02036d24 *self);
extern void func_02036ba4(UnkStruct_02036d24 *self, int arg);
extern void func_02036b88(UnkStruct_02036d24 *self, int arg);
extern void func_02036b6c(UnkStruct_02036d24 *self, int arg);

void func_02036d24(UnkStruct_02036d24 *self, int flag)
{
    int a, b;
    if (flag != 0) {
        a = func_02036648(self);
        b = func_0203736c(a, 0, 0, 0, 2, 0, 0);
        a = func_0203736c(a, 2, 0, 0, 0, 0, 0);
        if (b != 0) {
            if (self->unk_13 != 0) {
                if (self->unk_08 != 0x35) {
                    func_02036b14(self);
                    func_02036ba4(self, 0x35);
                }
                self->unk_13 = 0;
            }
            if (self->unk_0A != 0x36) {
                func_02036af4(self);
                func_02036b88(self, 0x36);
            }
        } else {
            func_02036b14(self);
            func_02036af4(self);
        }
        if (a != 0) {
            if (self->unk_0C != 0x37) {
                func_02036ad4(self);
                func_02036b6c(self, 0x37);
            }
        } else {
            func_02036ad4(self);
        }
    } else {
        func_02036b14(self);
        func_02036af4(self);
        func_02036ad4(self);
    }
}
