/* func_02001cc4 @ 0x02001cc4, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern struct UnkStruct_02001cc4 {
    char pad_00[0x12];
    unsigned short flags;
    char pad_14[10];
    unsigned char unk_1E;
    unsigned char unk_1F;
} data_0213fe74;
extern struct UnkStruct_02001cc4_2 {
    unsigned char unk_00;
    unsigned char unk_01;
} data_0213fe94;

void func_02001cc4(unsigned char a, unsigned char b, unsigned char c, unsigned char d)
{
    data_0213fe74.unk_1E = a;
    data_0213fe74.unk_1F = b;
    data_0213fe94.unk_00 = c;
    data_0213fe94.unk_01 = d;
    data_0213fe74.flags |= 0x10;
}
