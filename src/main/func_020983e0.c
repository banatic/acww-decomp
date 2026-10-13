/* func_020983e0 @ 0x020983e0, 0xc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020983e0 {
    char pad_00[0x40];
    unsigned int unk_40;
};

extern struct UnkStruct_020983e0 data_021ef8a8;

unsigned int func_020983e0(void)
{
    return data_021ef8a8.unk_40;
}
