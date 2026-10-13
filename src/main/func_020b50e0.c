/* func_020b50e0 @ 0x020b50e0, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x24];
    unsigned int unk_24;
    char pad_28[8];
    unsigned int unk_30;
    char pad_34[4];
    signed char *unk_38;
    char pad_3C[4];
    unsigned int unk_40;
    char pad_44[1];
    unsigned char unk_45;
} UnkStruct_020b50e0;

void func_020b50e0(UnkStruct_020b50e0 *s)
{
    signed char *src;
    unsigned int needed;
    unsigned int i;

    src = s->unk_38;
    needed = s->unk_30 + 6;

    if (0xa00 - s->unk_40 > needed) {
        for (i = 0; i < needed; i++) {
            *((char *) s->unk_24 + s->unk_40 + i + 0xafc) = src[i];
        }
        s->unk_40 += needed;
    } else {
        s->unk_45 = 0;
    }
}
