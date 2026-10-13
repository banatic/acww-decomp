/* func_02038a30 @ 0x02038a30, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x3c];
    int unk_3C;
} UnkStruct_02038a30;
extern UnkStruct_02038a30 data_021c5ccc;

int func_02038a30(void)
{
    if (data_021c5ccc.unk_3C >= 5) {
        return 1;
    }
    return 0;
}
