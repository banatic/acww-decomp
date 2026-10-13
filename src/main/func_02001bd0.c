/* func_02001bd0 @ 0x02001bd0, 0xc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct0213fe74 {
    unsigned char bytes[0x18];
    unsigned char unk_18;
};
extern struct UnkStruct0213fe74 data_0213fe74;

unsigned char func_02001bd0(void)
{
    return data_0213fe74.unk_18;
}
