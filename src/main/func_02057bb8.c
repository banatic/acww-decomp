/* func_02057bb8 @ 0x02057bb8, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x50];
    unsigned short unk_50;
} UnkStruct_02057bb8;

extern UnkStruct_02057bb8 *data_021c9350;

void func_02057bb8(unsigned short *dst)
{
    *dst = 0xfff1;
    if (data_021c9350 != 0) {
        *dst = data_021c9350->unk_50;
    }
}
