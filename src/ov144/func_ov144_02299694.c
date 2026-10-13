/* func_ov144_02299694 @ 0x02299694, 0x40 bytes, Thumb, module ov144
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02299694 {
    char pad_00[0x9C];
    int unk_9C;
    int unk_A0;
    char pad_A4[0x14];
    short unk_B8;
} UnkStruct_02299694;

extern void func_ov144_02299e6c(UnkStruct_02299694 *self, int n);
extern void func_ov144_0229a378(UnkStruct_02299694 *self);

void func_ov144_02299694(UnkStruct_02299694 *self, int param)
{
    int n = param - 3;
    int upper = self->unk_B8 - 8;
    if (upper < 0) {
        upper = 0;
    }
    if (n < 0) {
        n = 0;
    } else if (n > upper) {
        n = upper;
    }
    func_ov144_02299e6c(self, n << 4);
    self->unk_A0 = self->unk_9C;
    func_ov144_0229a378(self);
}
