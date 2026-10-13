/* func_02010934 @ 0x02010934, 0x6c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02010934 {
    char pad_00[0x2d8];
    unsigned int unk_2D8;
    char pad_2DC[0x2e0 - 0x2d8 - 4];
    unsigned int unk_2E0;
    unsigned char unk_2E4;
    char pad_2E5[0x704 - 0x2e4 - 1];
    int unk_704;
    char pad_708[0x718 - 0x704 - 4];
    int unk_718;
    char pad_71C[0x744 - 0x718 - 4];
    int unk_744;
};

extern void func_02010a24(struct UnkStruct_02010934 *s, int a, int b, int c, unsigned int d, unsigned int e, int f, int g);

void func_02010934(struct UnkStruct_02010934 *s)
{
    unsigned int v2;
    unsigned int v1;
    v1 = ((s->unk_718 >> 12) << 16);
    v2 = ((s->unk_744 >> 12) << 16);
    func_02010a24(s, s->unk_704, 3, s->unk_2E4, s->unk_2E0, (s->unk_2D8 << 4) >> 16, 0, 0x137);
    s->unk_718 = v1 >> 4;
    s->unk_744 = v2 >> 4;
}
