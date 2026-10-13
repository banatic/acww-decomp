/* func_020ba494 @ 0x020ba494, 0xc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020ba494 {
    unsigned char pad_00[0x3c];
    unsigned short unk_3C;
};
extern struct UnkStruct_020ba494 data_021f8ab0;

unsigned short func_020ba494(void)
{
    return data_021f8ab0.unk_3C;
}
