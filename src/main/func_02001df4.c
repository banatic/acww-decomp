/* func_02001df4 @ 0x02001df4, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02001df4 {
    char pad_00[0x11];
    unsigned char byte;
};
struct UnkStruct_02001df4_2 {
    char pad_00[0xc];
    unsigned short x;
    unsigned short y;
};
extern struct UnkStruct_02001df4 data_0213fe74;
extern struct UnkStruct_02001df4_2 data_0213fe34;

void func_02001df4(unsigned short a, unsigned short b)
{
    data_0213fe74.byte |= 0x20;
    data_0213fe34.x = a;
    data_0213fe34.y = b;
}
