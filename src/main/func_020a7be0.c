/* func_020a7be0 @ 0x020a7be0, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x24];
    int unk_24;
    char pad_28[0x28];
    int unk_50;
    char pad_54[0x4];
    unsigned char unk_58;
} UnkStruct_020a7be0;

void func_020a7be0(UnkStruct_020a7be0 *s)
{
    if (s->unk_24 == 4 && s->unk_50 == 0) {
        s->unk_58 = 1;
    }
}
