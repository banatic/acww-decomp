/* func_ov107_0229c894 @ 0x0229c894, 0xfc bytes, Thumb, module ov107
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229c894 {
    unsigned char pad_00[0xb8];
    unsigned char unk_B8;
};

extern int func_ov002_022088ac(void *p);
extern int func_ov002_022088cc(void *p);
extern int func_ov002_0220889c(void *p);
extern int func_ov002_022088bc(void *p);
extern void func_ov002_0220a314(void *p);
extern void func_ov107_0229c2a4(struct UnkStruct_0229c894 *self, int n);
extern int func_ov107_0229c2b4(struct UnkStruct_0229c894 *self, int n);

void func_ov107_0229c894(struct UnkStruct_0229c894 *self, void *p)
{
    int b = self->unk_B8;
    int count = 0;

    while (b >= 5) {
        b -= 5;
        count++;
    }

    if (func_ov002_022088ac(p) != 0) {
        if (func_ov002_022088cc(p) == 0 || count == 0) {
            if (b == 0) {
                self->unk_B8 += 4;
                func_ov107_0229c2a4(self, 8);
            } else {
                self->unk_B8 -= 1;
            }
        }
    } else {
        if (func_ov002_0220889c(p) != 0 && func_ov002_022088bc(p) == 0) {
            if (b == 4) {
                self->unk_B8 -= 4;
                func_ov107_0229c2a4(self, 0x10);
            } else {
                self->unk_B8 += 1;
            }
        }
    }

    if (func_ov107_0229c2b4(self, 0x18) != 0) {
        return;
    }

    if (func_ov002_022088cc(p) != 0) {
        if (count > 0) {
            self->unk_B8 -= 5;
            return;
        }
    } else {
        if (func_ov002_022088bc(p) != 0) {
            if (count < 2) {
                self->unk_B8 += 5;
            } else {
                self->unk_B8 = 0xf;
                func_ov002_0220a314((char *) self + 0x22b4);
            }
        }
    }
    return;
}
