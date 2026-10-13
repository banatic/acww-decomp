/* func_02001b1c @ 0x02001b1c, 0xc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x15];
    unsigned char unk_15;
} UnkStruct_02001b1c;

extern UnkStruct_02001b1c data_0213fe74;

void func_02001b1c(unsigned char value)
{
    data_0213fe74.unk_15 = value;
}
