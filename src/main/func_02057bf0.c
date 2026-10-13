/* func_02057bf0 @ 0x02057bf0, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern struct UnkStruct_02057bf0 *data_021c9350;

struct UnkStruct_02057bf0 {
    unsigned char pad_00[0xc8];
    unsigned char unk_C8;
    unsigned char pad_C9[0x10];
    unsigned char unk_D9;
    unsigned char unk_DA;
};

int func_02057bf0(int param)
{
    int result = 0;
    if (data_021c9350 != 0) {
        if ((data_021c9350->unk_C8 == param && data_021c9350->unk_D9 == 1) || data_021c9350->unk_DA == param) {
            result = 1;
        }
    }
    return result;
}
