/* func_020a17d0 @ 0x020a17d0, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern struct UnkStruct_020a17d0 {
    char pad_00[0x50];
    int unk_50;
} *data_021f3c3c;

int func_020a17d0(void)
{
    if (data_021f3c3c != 0 && data_021f3c3c->unk_50 == 0) {
        return 1;
    }
    return 0;
}
