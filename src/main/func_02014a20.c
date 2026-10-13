/* func_02014a20 @ 0x02014a20, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02014a20 {
    char pad_00[0x14];
    int unk_14;
} UnkStruct_02014a20;

typedef struct UnkStruct_02014a20_2 {
    char pad_00[0x40];
    UnkStruct_02014a20 *unk_40;
    char pad_44[0x60];
    unsigned char unk_A4;
    char pad_A5[0x7];
    unsigned char unk_AC;
} UnkStruct_02014a20_2;

int func_02014a20(UnkStruct_02014a20_2 *arg)
{
    if (arg->unk_40) {
        arg->unk_40->unk_14 = 2;
        if (arg->unk_A4) {
            arg->unk_AC = 1;
        } else {
            arg->unk_AC = 2;
        }
    }
    return 0;
}
