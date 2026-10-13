/* func_ov094_0229bbc0 @ 0x0229bbc0, 0x18 bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229bbc0 {
    char pad_00[0x25];
    volatile unsigned char unk_25;
};

void func_ov094_0229bbc0(struct UnkStruct_0229bbc0 *self)
{
    if (self->unk_25 != 0) {
        self->unk_25--;
    }
}
