/* func_ov121_0229bc70 @ 0x0229bc70, 0x58 bytes, Thumb, module ov121
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0229bc70 {
    u8 pad_00[0x8c];
    u8 unk_8C;
    u8 pad_8D[0x2d8 - 0x8c - 1];
    u8 unk_2D8;
};

extern void *func_020ee45c(struct UnkStruct_0229bc70 *self);
extern void func_ov090_022993cc(void *ptr, unsigned char b);
extern unsigned char *func_ov002_022080a0(struct UnkStruct_0229bc70 *self, unsigned char value);
extern int func_ov002_02207d24(void *p, int x);
extern int func_ov121_0229a50c(void);

int func_ov121_0229bc70(struct UnkStruct_0229bc70 *self, int mode)
{
    void *r = func_020ee45c(self);
    if (mode != -1 && mode != 1) {
        func_ov090_022993cc(r, (unsigned char) mode);
        self->unk_8C = 2;
        func_ov002_022080a0(self, 1);
        func_ov002_02207d24(&self->unk_2D8, 1);
        if (mode != 7) {
            asm {
                mov r0, self
            }
            func_ov121_0229a50c();
        }
        return 1;
    }
    return 0;
}
