/* func_02001b7c @ 0x02001b7c, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02001b7c {
    unsigned char pad_00[0x19];
    unsigned char unk_19;
};
extern struct UnkStruct_02001b7c data_0213fe74;

void func_02001b7c(unsigned char mask)
{
    data_0213fe74.unk_19 |= mask;
}
