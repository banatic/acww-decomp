/* func_02001c08 @ 0x02001c08, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02001c08 {
    unsigned char pad_00[16];
    unsigned char unk_10;
    unsigned char pad_11[6];
    unsigned char unk_17;
};

extern struct UnkStruct_02001c08 data_0213fe74;

void func_02001c08(unsigned char param)
{
    data_0213fe74.unk_17 = param;
    data_0213fe74.unk_10 = (data_0213fe74.unk_10 & ~0x0C) | ((0x3de0u >> (param << 1)) & 0x0C);
}
