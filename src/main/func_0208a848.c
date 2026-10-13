/* func_0208a848 @ 0x0208a848, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0208a848 {
    char pad_00[0x38];
    int unk_38;
    char pad_3C[0xc];
    int unk_48;
    int unk_4C;
    char pad_50[0x9];
    unsigned char unk_59;
    unsigned char unk_5A;
};

extern void func_0208a4dc(struct UnkStruct_0208a848 *self);
extern void func_0208a9a4(struct UnkStruct_0208a848 *self);

void func_0208a848(struct UnkStruct_0208a848 *self)
{
    if (self->unk_59 == 0) {
        self->unk_48 -= 11;
        self->unk_4C += (self->unk_5A ? -11 : 11);
    }
    self->unk_38 -= 1;
    if (self->unk_38 <= 0) {
        func_0208a4dc(self);
        func_0208a9a4(self);
    }
}
