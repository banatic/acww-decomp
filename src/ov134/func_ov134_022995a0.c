/* func_ov134_022995a0 @ 0x022995a0, 0xe bytes, Thumb, module ov134
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x90];
    unsigned short unk_90;
} UnkStruct_022995a0;

void func_ov134_022995a0(UnkStruct_022995a0 *self, unsigned short mask)
{
    self->unk_90 &= ~mask;
}
