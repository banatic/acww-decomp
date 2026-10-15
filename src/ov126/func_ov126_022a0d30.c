/* func_ov126_022a0d30 @ 0x022a0d30, 0x5c bytes, Thumb, module ov126
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern u16 data_021fbe40;

typedef struct {
    u8 pad_00[0xae];
    u8 unk_AE;
    u8 pad_AF[0x19c - 0xae - 1];
    u8 unk_19C;
} UnkStruct_022a0d30;

extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern int func_ov095_0229bf0c(void *ptr);
extern int func_ov126_022a027c(UnkStruct_022a0d30 *self, int val);
extern int func_ov126_0229f7c8(UnkStruct_022a0d30 *self, int val);
extern void func_ov126_0229ff0c(UnkStruct_022a0d30 *self);
extern int func_ov126_022a0a50(UnkStruct_022a0d30 *self);

void func_ov126_022a0d30(UnkStruct_022a0d30 *self)
{
    if ((data_021fbe40 & 2) == 0) {
        func_ov002_02208098((void *) (self), self->unk_AE);
    } else {
        if (func_ov095_0229bf0c(&self->unk_19C) != 0) {
            if (func_ov126_022a027c(self, 0) != 0) {
                if (func_ov126_0229f7c8(self, 0x80) != 0) {
                    func_ov126_0229ff0c(self);
                }
            } else {
                func_ov126_022a0a50(self);
            }
        }
    }
}
