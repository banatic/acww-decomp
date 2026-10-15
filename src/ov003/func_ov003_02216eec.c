/* func_ov003_02216eec @ 0x02216eec, 0xc4 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct Work {
    u8 pad_00[0x5c];
    u8 unk_5C[0x32];
    u8 unk_8E[0xa];
    void *unk_98;
    u8 pad_9C[0x764];
    u32 unk_800;
};

extern void *data_020ccf94;
extern int func_02073908(void *, u32);
extern void func_02010f5c(struct Work *);
extern int func_0201100c(struct Work *);
extern void func_02010d64(struct Work *);
extern int func_020113a4(void *, int, int);
extern void func_0201107c(struct Work *, int *);
extern int func_0200f554(struct Work *);
extern int func_020912d4(int, void *, void *, int);
extern void func_ov003_02217060(struct Work *);
extern void func_ov003_02216fec(struct Work *);
extern void func_ov003_02217020(struct Work *);
extern void func_ov003_02216fb0(struct Work *);

void func_ov003_02216eec(struct Work *self)
{
    void *orig = self->unk_98;
    int res[2];

    if (func_02073908(data_020ccf94, self->unk_800)) {
        func_ov003_02217060(self);
        func_02010f5c(self);
        func_0201100c(self);
        func_02010d64(self);

        res[0] = func_020113a4(self->unk_98, 0, 0x171);
        func_0201107c(self, &res[0]);

        func_ov003_02216fec(self);
        func_ov003_02217020(self);
    } else {
        func_02010f5c(self);

        if (func_0200f554(self)) {
            func_0201100c(self);
        }

        func_02010d64(self);

        res[1] = func_020113a4(self->unk_98, 0, 0x171);
        func_0201107c(self, &res[1]);

        func_ov003_02216fb0(self);
    }

    if (orig != 0 && self->unk_98 == 0) {
        func_020912d4(0x2c, &self->unk_5C, &self->unk_8E, 0);
    }
}
