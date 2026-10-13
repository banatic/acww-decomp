/* func_ov103_0229c810 @ 0x0229c810, 0x10 bytes, Thumb, module ov103
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229c810 {
    char pad_00[0x2da4];
    unsigned char unk_2DA4;
};
extern int func_ov103_0229cc80(struct UnkStruct_0229c810 *self, unsigned char byte);
int func_ov103_0229c810(struct UnkStruct_0229c810 *self)
{
    return func_ov103_0229cc80(self, self->unk_2DA4);
}
