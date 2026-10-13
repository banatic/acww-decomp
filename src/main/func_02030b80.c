/* func_02030b80 @ 0x02030b80, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern struct UnkStruct_02030b80 {
    char pad_00[0x132];
    short unk_132;
    short unk_134;
} *data_020da1a8;

void func_02030b80(short value)
{
    if (data_020da1a8->unk_134 != value) {
        data_020da1a8->unk_132 = data_020da1a8->unk_134;
        data_020da1a8->unk_134 = value;
    }
}
