/* func_ov126_022a06b4 @ 0x022a06b4, 0x24 bytes, Thumb, module ov126
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_022a06b4 {
    char pad_00[0xa8];
    unsigned char unk_A8;
    unsigned char unk_A9;
    unsigned char unk_AA;
} UnkStruct_022a06b4;

extern void func_ov126_0229f7a8(UnkStruct_022a06b4 *self, int a);

void func_ov126_022a06b4(UnkStruct_022a06b4 *self)
{
    self->unk_A9 = self->unk_A8;
    self->unk_AA = self->unk_A8;
    func_ov126_0229f7a8(self, 4);
}
