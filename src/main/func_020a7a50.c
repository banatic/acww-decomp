/* func_020a7a50 @ 0x020a7a50, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x48];
    int unk_48;
    int unk_4C;
    unsigned char pad_50[8];
    unsigned char unk_58;
} UnkStruct_020a7a50;

void func_020a7a50(UnkStruct_020a7a50 *p)
{
    int old = p->unk_4C;
    p->unk_4C = old + 1;
    if (old == p->unk_48) {
        p->unk_58 = 1;
    }
}
