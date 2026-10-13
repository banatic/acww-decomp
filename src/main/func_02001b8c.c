/* func_02001b8c @ 0x02001b8c, 0xc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern struct _GlobalStruct {
    unsigned char pad_00[0x19];
    unsigned char unk_19;
} data_0213fe74;

void func_02001b8c(unsigned char val)
{
    data_0213fe74.unk_19 = val;
}
