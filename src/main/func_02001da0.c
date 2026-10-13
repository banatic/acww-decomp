/* func_02001da0 @ 0x02001da0, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02001da0 {
    char pad_00[2];
    unsigned char byte;
};
struct UnkStruct_02001da0_2 {
    char pad_00[0x12];
    unsigned short word;
};
extern struct UnkStruct_02001da0 data_0213fe94;
extern struct UnkStruct_02001da0_2 data_0213fe74;

void func_02001da0(unsigned char param)
{
    data_0213fe94.byte = param;
    data_0213fe74.word |= 0x0001;
}
