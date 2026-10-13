/* func_02038078 @ 0x02038078, 0x2e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xbc];
    int unk_BC;
    int unk_C0;
    int unk_C4;
    unsigned char unk_C8;
    char pad_C9[0x17];
    int unk_E0;
    int unk_E4;
} UnkStruct_02038078;

void func_02038078(UnkStruct_02038078 *p)
{
    p->unk_BC = 6;
    p->unk_C4 = 0;
    p->unk_C8 = 1;
    p->unk_E0 = 0;
    p->unk_E4 = -1;
    p->unk_C0 = 0x14;
}
