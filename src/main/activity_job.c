/* activity_job: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020a17d0 @ 0x020a17d0, 0x1c bytes, Thumb
 * func_020a17a8 @ 0x020a17a8, 0x28 bytes, Thumb
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

int func_020a17a8(void)
{
    unsigned char *p;
    if ((*(void **) &data_021f3c3c) && (*(int *) ((char *) (*(void **) &data_021f3c3c) + 0x50) == 0x1f)) {
        p = (unsigned char *) (*(void **) &data_021f3c3c) + 0xa1;
        if (*p == 0x0f || *p == 0x14) {
            return 1;
        }
    }
    return 0;
}
