/* func_02001d88 @ 0x02001d88, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct unk_0213fe94 {
    char pad_00[7];
    unsigned char unk_07;
};
struct unk_0213fe74 {
    char pad_00[18];
    unsigned short unk_12;
};

extern struct unk_0213fe94 data_0213fe94;
extern struct unk_0213fe74 data_0213fe74;

void func_02001d88(unsigned char param)
{
    data_0213fe94.unk_07 = param;
    data_0213fe74.unk_12 |= 2;
}
