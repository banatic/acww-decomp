/* func_ov103_0229c3a0 @ 0x0229c3a0, 0xa4 bytes, Thumb, module ov103
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229c3a0 {
    unsigned char pad_00[0x2da4];
    unsigned char b;
};

extern int func_ov002_022088ac(void *arg);
extern int func_ov002_0220889c(void *arg);
extern int func_ov002_022088cc(void *arg);
extern int func_ov002_022088bc(void *arg);
extern int func_ov103_0229cdfc(struct UnkStruct_0229c3a0 *self, int b);
extern int func_ov103_0229c2f4(struct UnkStruct_0229c3a0 *self, int val);

void func_ov103_0229c3a0(struct UnkStruct_0229c3a0 *self, void *arg, int b)
{
    int r4 = self->b - 11;
    int r6 = r4 >> 1;

    if (func_ov002_022088ac(arg)) {
        if ((r4 & 1) > 0) {
            self->b--;
        }
    } else {
        if (func_ov002_0220889c(arg)) {
            if ((r4 & 1) < 1) {
                self->b++;
            }
        }
    }

    if (func_ov103_0229cdfc(self, self->b) != 0) {
        if (func_ov103_0229c2f4(self, 0x30) == 0) {
            if (func_ov002_022088cc(arg)) {
                if (r6 > 0) {
                    self->b -= 2;
                }
            } else {
                if (func_ov002_022088bc(arg)) {
                    if (r6 < 4) {
                        self->b += 2;
                    }
                }
            }
        }
    }
}
