/* func_020ba4c4 @ 0x020ba4c4, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020ba4c4 {
    unsigned char pad_00[0x24];
    unsigned int unk_24;
    unsigned int unk_28;
};
extern struct UnkStruct_020ba4c4 data_021f8ab0;

void func_020ba4c4(unsigned int *out0, unsigned int *out1)
{
    *out0 = data_021f8ab0.unk_24;
    *out1 = data_021f8ab0.unk_28;
}
