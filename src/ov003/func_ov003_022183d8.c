/* func_ov003_022183d8 @ 0x022183d8, 0x1c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_0200f268(void *obj, int value);

struct UnkStruct_022183d8 {
    char pad_00[0x7f8];
    int unk_7F8;
};

void func_ov003_022183d8(struct UnkStruct_022183d8 *self, void *message, int previous)
{
    func_0200f268(self, 0);
    self->unk_7F8 = 0;
}
