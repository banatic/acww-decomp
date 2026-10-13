/* func_ov102_0229c790 @ 0x0229c790, 0x12c bytes, Thumb, module ov102
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    char pad_00[0x25a5];
    u8 unk_25A5;
} SelfType;

extern void func_ov102_0229c298(SelfType *self, int value);
extern int func_ov002_022088ac(void *other);
extern int func_ov002_022088cc(void *other);
extern int func_ov002_0220889c(void *other);
extern int func_ov002_022088bc(void *other);

void func_ov102_0229c790(SelfType *self, void *other, int arg2)
{
    int rem = self->unk_25A5 - 15;
    int quot = 0;

    while (rem >= 5) {
        rem -= 5;
        quot++;
    }

    if (func_ov002_022088ac(other) != 0) {
        if (func_ov002_022088cc(other) != 0 && quot != 0) {
            goto L_876;
        }

        if (rem == 0) {
            switch (quot) {
                case 0:
                    self->unk_25A5 = 0x20;
                    break;
                case 1:
                    self->unk_25A5 = 0x23;
                    break;
                case 2:
                default:
                    if (arg2 == 1) {
                        self->unk_25A5 += 4;
                    } else {
                        self->unk_25A5 = 0x24;
                    }
                    break;
            }

            func_ov102_0229c298(self, 0x10);
            return;
        } else {
            self->unk_25A5--;
            rem--;
            goto L_876;
        }
    } else {
        if (func_ov002_0220889c(other) != 0) {
            if (func_ov002_022088bc(other) == 0) {
                if (rem == 4) {
                    switch (quot) {
                        case 0:
                            self->unk_25A5 = 0x1e;
                            return;
                        case 1:
                            self->unk_25A5 = 0x21;
                            return;
                        case 2:
                        default:
                            if (arg2 == 1) {
                                self->unk_25A5 -= 4;
                                func_ov102_0229c298(self, 0x20);
                            } else {
                                self->unk_25A5 = 0x24;
                            }
                            return;
                    }
                } else {
                    self->unk_25A5++;
                    rem++;
                }
            }
        }
    }

L_876:
    if (func_ov002_022088cc(other) != 0) {
        if (quot > 0) {
            self->unk_25A5 -= 5;
        }
        return;
    }

    if (func_ov002_022088bc(other) != 0) {
        if (quot < 2) {
            self->unk_25A5 += 5;
        } else {
            self->unk_25A5 = rem;
        }
    }
}
