/* func_02037fa8 @ 0x02037fa8, 0x26 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02116a1c(int arg);

struct UnkStruct_02037fa8 {
    char pad_00[0xC0];
    int unk_C0;
};

void func_02037fa8(struct UnkStruct_02037fa8 *self)
{
    self->unk_C0 = self->unk_C0 - 1;
    if (self->unk_C0 <= 0) {
        func_02116a1c(0);
    }
}
