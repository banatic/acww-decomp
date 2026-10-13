/* func_02001b28 @ 0x02001b28, 0xc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0213FE74 {
    unsigned char pad_00[0x15];
    unsigned char unk_15;
};

extern struct UnkStruct_0213FE74 data_0213fe74;

unsigned char func_02001b28(void)
{
    return data_0213fe74.unk_15;
}
