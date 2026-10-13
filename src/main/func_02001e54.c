/* func_02001e54 @ 0x02001e54, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x11];
    unsigned char unk_11;
} UnkStruct_02001e54;

typedef struct {
    char pad_00[0x20];
    unsigned int unk_20;
    unsigned int unk_24;
} UnkStruct_02001e54_2;

extern UnkStruct_02001e54 data_0213fe74;
extern UnkStruct_02001e54_2 data_0213fdf4;

void func_02001e54(unsigned int a, unsigned int b)
{
    data_0213fe74.unk_11 |= 0x04;
    data_0213fdf4.unk_20 = a;
    data_0213fdf4.unk_24 = b;
}
