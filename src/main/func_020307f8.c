/* func_020307f8 @ 0x020307f8, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x12c];
    int unk_12C;
} UnkStruct_020307f8;

extern UnkStruct_020307f8 *data_020da1a8;

int func_020307f8(void)
{
    if (data_020da1a8->unk_12C == -1) {
        return 0;
    }
    data_020da1a8->unk_12C = -1;
    return 1;
}
