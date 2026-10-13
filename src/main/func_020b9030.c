/* func_020b9030 @ 0x020b9030, 0x1a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xE0];
    int unk_E0;
    char pad_E4[4];
    unsigned char unk_E8;
} UnkStruct_020b9030;

int func_020b9030(UnkStruct_020b9030 *arg)
{
    if (arg->unk_E8 != 0 && arg->unk_E0 < 25) {
        return 1;
    }
    return 0;
}
