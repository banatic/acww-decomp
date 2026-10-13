/* func_ov106_0229c638 @ 0x0229c638, 0x110 bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    char pad_00[0xb7];
    u8 unk_B7;
    u8 unk_B8;
} SelfType;

extern int func_ov002_022088ac(void *ctx);
extern int func_ov002_0220889c(void *ctx);
extern int func_ov002_022088cc(void *ctx);
extern int func_ov002_022088bc(void *ctx);
extern void func_ov002_0220a314(void *p);
extern int func_ov106_0229d3a0(void *self, u8 b);
extern void func_ov106_0229c354(void *self, int val);
extern int func_ov106_0229c364(void *self, int val);

void func_ov106_0229c638(SelfType *self, void *ctx, int flag)
{
    int r6;
    int r4;

    r6 = (int) self->unk_B8 - 0xb;
    r4 = r6 >> 1;

    if (func_ov002_022088ac(ctx) != 0) {
        if ((r6 & 1) > 0) {
            self->unk_B8--;
        } else {
            if (flag == 1 && func_ov106_0229d3a0(self, self->unk_B7) != 0) {
                goto common;
            }
            self->unk_B8 = (r4 << 1) + 0x16;
            return;
        }
    } else {
        if (func_ov002_0220889c(ctx) != 0) {
            if ((r6 & 1) < 1) {
                self->unk_B8++;
            } else {
                if (flag == 1 && func_ov106_0229d3a0(self, self->unk_B7) != 0) {
                    goto common;
                }
                self->unk_B8 = (r4 << 1) + 0x15;
                func_ov106_0229c354(self, 0x20);
                return;
            }
        }
    }

common:
    if (func_ov106_0229d3a0(self, self->unk_B8) == 0) {
        return;
    }
    if (func_ov106_0229c364(self, 0x30) != 0) {
        return;
    }

    if (func_ov002_022088cc(ctx) != 0) {
        if (r4 > 0) {
            self->unk_B8 -= 2;
        }
        return;
    }

    if (func_ov002_022088bc(ctx) != 0) {
        if (r4 < 4) {
            self->unk_B8 += 2;
            return;
        }
        if (flag == 0) {
            self->unk_B8 = 0x1f;
            func_ov002_0220a314((char *) self + 0x22a0);
        }
    }
}
