/* func_ov002_02207d5c @ 0x02207d5c, 0xac bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_02207d5c {
    char pad_00[0xcc];
    u8 unk_CC;
    char pad_CD;
    u8 unk_CE;
} UnkStruct_02207d5c;

extern int func_0208a844(UnkStruct_02207d5c *self);
extern int func_0208a9ac(UnkStruct_02207d5c *self);
extern int func_0208a9c8(UnkStruct_02207d5c *self);
extern void func_0208aaa0(UnkStruct_02207d5c *self);
extern void func_ov002_02207d24(UnkStruct_02207d5c *self, int value);

int func_ov002_02207d5c(UnkStruct_02207d5c *self)
{
    int result = 0;

    if (self->unk_CE != 0) {
        self->unk_CE--;
        if (self->unk_CE == 0 && self->unk_CC == 3) {
            func_ov002_02207d24(self, result);
        }
    }

    switch (self->unk_CC) {
        case 1:
            if (func_0208a844(self) != 0) {
                func_0208a9ac(self);
            } else {
                result = 1;
                self->unk_CC = 2;
            }
            break;
        case 2:
            if (func_0208a9c8(self) != 0) {
                self->unk_CC = 3;
            }
            break;
        case 4:
            if (func_0208a844(self) == 0 || func_0208a9ac(self) != 0) {
                self->unk_CC = 0;
            }
            break;
    }

    func_0208aaa0(self);
    return result;
}
