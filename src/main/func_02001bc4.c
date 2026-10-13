/* func_02001bc4 @ 0x02001bc4, 0xc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x18];
    unsigned char byte;
} UnkStruct_02001bc4;

extern UnkStruct_02001bc4 data_0213fe74;

void func_02001bc4(unsigned char value)
{
    data_0213fe74.byte = value;
}
