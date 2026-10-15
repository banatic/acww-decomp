/* func_0203a958 @ 0x0203a958, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x4C];
    int unk_4C;
    int unk_50;
    int unk_54;
    unsigned short unk_58;
} UnkStruct_0203a958;

extern void func_0203a89c(UnkStruct_0203a958 *self);

void func_0203a958(UnkStruct_0203a958 *self, int a1, unsigned short a2, int a3, int a4)
{
    self->unk_4C = a1;
    self->unk_58 = a2;
    self->unk_50 = a3;
    self->unk_54 = a4;
    func_0203a89c(self);
}
