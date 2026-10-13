/* func_ov053_02260cf0 @ 0x02260cf0, 0x10 bytes, Thumb, module ov053
 * mwccarm 1.2/base -O4,s
 */

struct s_ov053 {
    char pad_00[0x718];
    char unk_718;
};

int func_ov053_02260cf0(struct s_ov053 *self)
{
    self->unk_718 = 0;
    return 1;
}
