/* func_020422f8 @ 0x020422f8, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern struct UnkStruct_020422f8 {
    unsigned char pad_00[0x20];
    unsigned char *unk_20;
} data_021c779c;

extern void func_020422a0(void);

int func_020422f8(void)
{
    int result = 0;
    if (data_021c779c.unk_20 != 0 && data_021c779c.unk_20[0x10e9] != 0) {
        func_020422a0();
        result = 1;
    }
    return result;
}
