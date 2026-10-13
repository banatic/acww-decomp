/* func_ov009_022630a0 @ 0x022630a0, 0x14 bytes, Thumb, module ov009
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x134];
    unsigned char unk_134;
} UnkStruct_022630a0;

int func_ov009_022630a0(UnkStruct_022630a0 *self)
{
    if (self->unk_134 == 0) {
        return 1;
    } else {
        return 0;
    }
}
