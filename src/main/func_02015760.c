/* func_02015760 @ 0x02015760, 0x12 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x14];
    int unk_14;
} OtherStruct;

typedef struct {
    char pad_00[0x40];
    OtherStruct *unk_40;
    char pad_44[0xAC - 0x44];
    unsigned char unk_AC;
} UnkStruct_02015760;

int func_02015760(UnkStruct_02015760 *param)
{
    OtherStruct *ptr;
    ptr = param->unk_40;
    if (ptr) {
        ptr->unk_14 = 1;
        param->unk_AC = 1;
    }
    return 0;
}
