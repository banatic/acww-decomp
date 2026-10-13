/* func_ov003_0222e970 @ 0x0222e970, 0x1c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x204];
    int unk_204;
    char pad_208[0x54];
} UnkStruct_0222e970;

extern UnkStruct_0222e970 data_ov003_02260e4c[];

int *func_ov003_0222e970(int i)
{
    return &data_ov003_02260e4c[i].unk_204;
}
