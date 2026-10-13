/* func_02013910 @ 0x02013910, 0x22 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02013910 {
    char pad_00[0x94];
    int unk_94;
    int unk_98;
};

void func_02013910(struct UnkStruct_02013910 *self)
{
    if (self->unk_94 == 0 && self->unk_98 == 0) {
        self->unk_94 = 0xFF;
        self->unk_98 = 0xFF;
    }
}
