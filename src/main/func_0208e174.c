/* func_0208e174 @ 0x0208e174, 0x26 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0208e174;

extern void func_0208e044(struct UnkStruct_0208e174 *self);
extern void func_0208e240(struct UnkStruct_0208e174 *self);

struct UnkStruct_0208e174 {
    char pad_00[0x30];
    int unk_30;
    char pad_34[0x44];
    int unk_78;
};

void func_0208e174(struct UnkStruct_0208e174 *self)
{
    self->unk_30 += 0xb;
    self->unk_78 -= 1;
    if (self->unk_78 > 0) {
        return;
    }
    func_0208e044(self);
    func_0208e240(self);
}
