/* func_ov104_0229cd18 @ 0x0229cd18, 0xd8 bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    char pad_00[0xb8];
    u8 unk_B8;
    char pad_B9[0x24a0 - 0xb9];
    char unk_24A0;
} UnkStruct_0229cd18;

extern int func_ov002_022088ac(void *p);
extern int func_ov002_0220889c(void *p);
extern int func_ov002_022088cc(void *p);
extern int func_ov002_022088bc(void *p);
extern int func_ov104_0229da70(UnkStruct_0229cd18 *self, int a);
extern int func_ov104_0229c364(UnkStruct_0229cd18 *self, int a);
extern void func_ov002_0220a314(void *p);

void func_ov104_0229cd18(UnkStruct_0229cd18 *self, void *pad, int flag)
{
    int v;
    int i;

    v = self->unk_B8 - 0x15;
    i = 0;
    while (v >= 2) {
        i++;
        v -= 2;
    }

    if (func_ov002_022088ac(pad) != 0) {
        if (v > 0) {
            self->unk_B8 = self->unk_B8 - 1;
        }
    } else if (func_ov002_0220889c(pad) != 0) {
        if (v < 1) {
            self->unk_B8 = self->unk_B8 + 1;
        } else {
            self->unk_B8 = (u8) (i * 2 + 0xb);
            return;
        }
    }

    if (func_ov104_0229da70(self, self->unk_B8) != 0) {
        if (func_ov104_0229c364(self, 0x30) == 0) {
            if (func_ov002_022088cc(pad) != 0) {
                if (i > 0) {
                    self->unk_B8 = self->unk_B8 - 2;
                }
            } else if (func_ov002_022088bc(pad) != 0) {
                if (i < 4) {
                    self->unk_B8 = self->unk_B8 + 2;
                } else if (flag == 0) {
                    self->unk_B8 = 0x20;
                    func_ov002_0220a314(&self->unk_24A0);
                }
            }
        }
    }
}
