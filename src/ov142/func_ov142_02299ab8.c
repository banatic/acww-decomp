/* func_ov142_02299ab8 @ 0x02299ab8, 0x28 bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x94];
    unsigned int unk_94;
    char pad_98[0x10];
    unsigned int unk_A8;
} UnkStruct_02299ab8;

extern void func_0208ea70(char *, unsigned int, unsigned int);

void func_ov142_02299ab8(UnkStruct_02299ab8 *self)
{
    func_0208ea70((char *) self + 0x14c, 0x38, self->unk_94 + (self->unk_A8 - 0x34));
}
