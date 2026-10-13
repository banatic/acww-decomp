/* func_ov003_0222a918 @ 0x0222a918, 0x20 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x54];
    char unk_54;
    char pad_55[0x4f];
} UnkStruct_0222a918;
extern UnkStruct_0222a918 data_ov003_0225f4dc[];
extern char data_ov003_0225f530[];
void *func_ov003_0222a918(int i)
{
    if (i < 0 || i >= 4) {
        return data_ov003_0225f530;
    }
    return &data_ov003_0225f4dc[i].unk_54;
}
