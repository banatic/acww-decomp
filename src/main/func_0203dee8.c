/* func_0203dee8 @ 0x0203dee8, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0203e4c0(int);

struct UnkStruct_0203dee8 {
    char pad_00[0x16];
    char unk_16;
};

extern struct UnkStruct_0203dee8 *data_021c72b8;

int func_0203dee8(void)
{
    if (func_0203e4c0(13) != 0) {
        data_021c72b8->unk_16 = 6;
        return 1;
    } else {
        return 0;
    }
}
