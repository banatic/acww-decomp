/* func_ov050_02260510 @ 0x02260510, 0x18 bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02260510 {
    char pad_00[0xc];
    unsigned short unk_0C;
};

int func_ov050_02260510(struct UnkStruct_02260510 *self)
{
    unsigned int flag = (self->unk_0C == 0x76) ? 1 : 0;
    if (flag > 0) {
        return 1;
    }
    return 0;
}
