/* func_020a1848 @ 0x020a1848, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x50];
    int unk_50;
    char pad_54[0x4D];
    unsigned char unk_A1;
} UnkStruct_020a1848;

extern UnkStruct_020a1848 *data_021f3c3c;

int func_020a1848(void)
{
    if (data_021f3c3c != 0 && data_021f3c3c->unk_50 == 0x12 && data_021f3c3c->unk_A1 == 3) {
        return 1;
    }
    return 0;
}
