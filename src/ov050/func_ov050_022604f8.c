/* func_ov050_022604f8 @ 0x022604f8, 0x18 bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_022604f8 {
    char pad_00[0xc];
    unsigned short unk_0C;
};

int func_ov050_022604f8(struct UnkStruct_022604f8 *self)
{
    unsigned int flag = (self->unk_0C == 0x75) ? 1 : 0;
    if (flag > 0) {
        return 1;
    }
    return 0;
}
