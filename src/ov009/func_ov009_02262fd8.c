/* func_ov009_02262fd8 @ 0x02262fd8, 0x20 bytes, Thumb, module ov009
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02262fd8 {
    unsigned char pad_00[0x27c];
    unsigned int unk_27C;
};

extern int func_ov009_02262ff8(struct UnkStruct_02262fd8 *self);

int func_ov009_02262fd8(struct UnkStruct_02262fd8 *self)
{
    if (self->unk_27C == 0) {
        return func_ov009_02262ff8(self);
    } else {
        return 0;
    }
}
