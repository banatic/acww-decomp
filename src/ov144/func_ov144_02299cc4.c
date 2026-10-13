/* func_ov144_02299cc4 @ 0x02299cc4, 0x78 bytes, Thumb, module ov144
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02299cc4 {
    char pad_00[0x9c];
    int unk_9C;
    int unk_A0;
};
extern void func_ov144_02299e6c(struct UnkStruct_02299cc4 *self, int x);
extern void func_ov144_0229a378(struct UnkStruct_02299cc4 *self);

void func_ov144_02299cc4(struct UnkStruct_02299cc4 *self)
{
    if (self->unk_9C != self->unk_A0) {
        if (self->unk_9C > self->unk_A0) {
            self->unk_9C -= 6;
            if (self->unk_9C < self->unk_A0) {
                self->unk_9C = self->unk_A0;
            }
        } else {
            self->unk_9C += 6;
            if (self->unk_9C > self->unk_A0) {
                self->unk_9C = self->unk_A0;
            }
        }
        func_ov144_02299e6c(self, self->unk_9C);
        func_ov144_0229a378(self);
    }
}
