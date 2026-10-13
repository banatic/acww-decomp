/* func_ov106_0229c54c @ 0x0229c54c, 0xec bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0xb8];
    unsigned char unk_B8;
} SelfType;

extern int func_ov002_022088ac(void *ctx);
extern int func_ov002_0220889c(void *ctx);
extern int func_ov002_022088cc(void *ctx);
extern int func_ov002_022088bc(void *ctx);
extern int func_ov106_0229d390(void *self, int b);
extern int func_ov106_0229c354(void *self, int val);
extern int func_ov106_0229c364(void *self, int val);
extern void func_ov002_0220a314(void *ptr);

void func_ov106_0229c54c(SelfType *self, void *ctx, int flag)
{
    int r6, r4;

    r6 = (int) self->unk_B8 - 0x15;
    r4 = 0;
    while (r6 >= 2) {
        r4++;
        r6 -= 2;
    }

    if (func_ov002_022088ac(ctx) != 0) {
        if (r6 > 0) {
            self->unk_B8--;
        } else {
            self->unk_B8 = (unsigned char) (r4 * 2 + 0xc);
            func_ov106_0229c354(self, 0x10);
            return;
        }
    } else {
        if (func_ov002_0220889c(ctx) != 0) {
            if (r6 < 1) {
                self->unk_B8++;
            } else {
                self->unk_B8 = (unsigned char) (r4 * 2 + 0xb);
                return;
            }
        }
    }

    if (func_ov106_0229d390(self, self->unk_B8) != 0) {
        if (func_ov106_0229c364(self, 0x30) == 0) {
            if (func_ov002_022088cc(ctx) != 0) {
                if (r4 > 0) {
                    self->unk_B8 -= 2;
                }
                return;
            } else {
                if (func_ov002_022088bc(ctx) != 0) {
                    if (r4 < 4) {
                        self->unk_B8 += 2;
                        return;
                    } else {
                        if (flag == 0) {
                            self->unk_B8 = 0x1f;
                            func_ov002_0220a314((char *) self + 0x22a0);
                        }
                    }
                }
            }
        }
    }
}
