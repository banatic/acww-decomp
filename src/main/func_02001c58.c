/* func_02001c58 @ 0x02001c58, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0xd];
    unsigned char d;
    unsigned char e;
    unsigned char unk_0F;
    unsigned char g;
} UnkStruct_02001c58;

typedef struct {
    unsigned char pad_00[0x12];
    unsigned short h;
} UnkStruct_02001c58_2;

extern UnkStruct_02001c58 data_0213fe94;
extern UnkStruct_02001c58_2 data_0213fe74;

void func_02001c58(unsigned char a, unsigned char b, unsigned char c, unsigned char d)
{
    data_0213fe94.d = a;
    data_0213fe94.e = b;
    data_0213fe94.unk_0F = c;
    data_0213fe94.g = d;
    data_0213fe74.h |= 0x80;
}
