/* func_ov145_022997d0 @ 0x022997d0, 0xf4 bytes, Thumb, module ov145
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    char pad_00[0xa4];
    int unk_A4;
    char pad_A8[0xc2 - 0xa8];
    volatile u8 unk_C2;
} UnkStruct_022997d0;

extern int func_ov002_022088ac(void *p);
extern int func_ov002_0220889c(void *p);
extern int func_ov002_022088cc(void *p);
extern int func_ov002_022088bc(void *p);

int func_ov145_022997d0(UnkStruct_022997d0 *self, void *pad)
{
    u8 st = self->unk_C2;

    if (st <= 3) {
        if (func_ov002_022088ac(pad) != 0) {
            if (self->unk_C2 < 3) {
                self->unk_C2 = self->unk_C2 + 1;
            }
        } else if (func_ov002_0220889c(pad) != 0) {
            if (self->unk_C2 != 0) {
                self->unk_C2 = self->unk_C2 - 1;
            } else {
                self->unk_C2 = 4;
            }
        } else if (func_ov002_022088cc(pad) != 0) {
            if (self->unk_A4 > 0) {
                self->unk_C2 = 5;
            }
        }
    } else {
        switch (st) {
            case 4:
                if (func_ov002_022088cc(pad) != 0) {
                    if (self->unk_A4 > 0) {
                        self->unk_C2 = 5;
                    }
                } else if (func_ov002_022088ac(pad) != 0) {
                    self->unk_C2 = 0;
                }
                break;
            case 5:
                if (func_ov002_022088bc(pad) != 0) {
                    self->unk_C2 = 4;
                } else if (func_ov002_022088ac(pad) != 0) {
                    self->unk_C2 = 0;
                }
                break;
        }
    }
    if (st != self->unk_C2) {
        return 1;
    } else {
        return 0;
    }
}
