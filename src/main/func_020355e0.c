/* func_020355e0 @ 0x020355e0, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_020355e0 {
    unsigned char pad_00[4];
    unsigned short unk_04;
    unsigned char pad_06[22];
} UnkStruct_020355e0;

extern UnkStruct_020355e0 *data_021c526c;
extern int func_02034f44(UnkStruct_020355e0 *ptr);

unsigned short func_020355e0(void)
{
    int index;
    unsigned short result;

    index = func_02034f44(data_021c526c);
    result = 0xffff;
    if (index >= 0) {
        result = data_021c526c[index].unk_04;
    }
    return result;
}
