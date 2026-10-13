/* func_ov111_0229f600 @ 0x0229f600, 0x60 bytes, Thumb, module ov111
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;

struct UnkStruct_0229f600 {
    char pad_00[0x9e];
    unsigned char unk_9E;
    unsigned char unk_9F;
    unsigned char unk_A0;
};

extern void func_ov111_0229f598(struct UnkStruct_0229f600 *self, int clamp);
extern void func_ov111_0229efc8(struct UnkStruct_0229f600 *self, int n);

int func_ov111_0229f600(struct UnkStruct_0229f600 *self)
{
    int g1 = data_021f6c58;
    int g2 = data_021f6c54;
    int clamp;

    if (g2 < 0x24 || g2 >= 0x3c) {
        return 0;
    }
    if (g1 < 0x10 || g1 >= 0xc8) {
        return 0;
    }
    clamp = g1;
    if (clamp < 0x18) {
        clamp = 0x18;
    }
    func_ov111_0229f598(self, clamp);
    func_ov111_0229efc8(self, 1);
    self->unk_9F = self->unk_9E;
    self->unk_A0 = self->unk_9E;
    return 1;
}
