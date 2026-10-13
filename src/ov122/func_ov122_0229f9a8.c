/* func_ov122_0229f9a8 @ 0x0229f9a8, 0x40 bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229f9a8 {
    char pad_00[0xAA];
    unsigned char unk_AA;
};

extern void func_ov122_0229fa90(struct UnkStruct_0229f9a8 *self);
extern void func_ov122_0229fa34(struct UnkStruct_0229f9a8 *self);
extern void func_ov122_0229f9e8(struct UnkStruct_0229f9a8 *self);
extern void func_ov122_0229f394(struct UnkStruct_0229f9a8 *self);

void func_ov122_0229f9a8(struct UnkStruct_0229f9a8 *self)
{
    switch (self->unk_AA) {
        case 0:
        case 1:
            func_ov122_0229fa90(self);
            break;
        case 2:
            func_ov122_0229fa34(self);
            break;
        case 3:
            func_ov122_0229f9e8(self);
            break;
    }
    func_ov122_0229f394(self);
}
