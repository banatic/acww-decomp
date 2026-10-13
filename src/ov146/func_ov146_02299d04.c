/* func_ov146_02299d04 @ 0x02299d04, 0x7e bytes, Thumb, module ov146
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xa4];
    int unk_A4;
    int unk_A8;
} Self_t;
extern void func_ov146_02299dec(Self_t *self, int val);
extern void func_ov146_02299af4(Self_t *self);
int func_ov146_02299d04(Self_t *self)
{
    if (self->unk_A4 != self->unk_A8) {
        if (self->unk_A4 > self->unk_A8) {
            self->unk_A4 -= 6;
            if (self->unk_A4 < self->unk_A8) {
                self->unk_A4 = self->unk_A8;
            }
        } else {
            self->unk_A4 += 6;
            if (self->unk_A4 > self->unk_A8) {
                self->unk_A4 = self->unk_A8;
            }
        }
        func_ov146_02299dec(self, self->unk_A4);
        func_ov146_02299af4(self);
        return 1;
    } else {
        return 0;
    }
}
