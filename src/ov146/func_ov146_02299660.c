/* func_ov146_02299660 @ 0x02299660, 0xe bytes, Thumb, module ov146
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xac];
    unsigned short unk_AC;
} UnkStruct_02299660;

void func_ov146_02299660(UnkStruct_02299660 *self, unsigned short mask)
{
    self->unk_AC = self->unk_AC | mask;
}
