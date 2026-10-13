/* func_02001db8 @ 0x02001db8, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02001db8 {
    unsigned char pad_00[8];
    int unk_08;
    int unk_0C;
    unsigned char pad_10;
    unsigned char flag;
};

extern struct UnkStruct_02001db8 data_0213fe74;

void func_02001db8(int a, int b)
{
    data_0213fe74.flag |= 0x80;
    data_0213fe74.unk_08 = a;
    data_0213fe74.unk_0C = b;
}
