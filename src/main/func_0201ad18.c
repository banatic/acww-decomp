/* func_0201ad18 @ 0x0201ad18, 0x60 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct Src {
    int a;
    int b;
    int c;
};

struct UnkStruct_0201ad18 {
    unsigned char unk_00;
    char pad_01[3];
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    int unk_14;
    unsigned char unk_18;
    char pad_19[3];
    unsigned short unk_1C;
    unsigned short unk_1E;
    char pad_20[4];
    unsigned short unk_24;
    unsigned short unk_26;
    char pad_28[2];
    unsigned char unk_2A;
    char pad_2B[0x31];
    int unk_5C;
    unsigned char unk_60;
    char pad_61[3];
    int unk_64;
};

void func_0201ad18(struct UnkStruct_0201ad18 *s, unsigned char b, int arg2, int y, struct Src *src, int arg6, int arg7,
                   unsigned char arg8)
{
    if (s->unk_18 != 0 || s->unk_14 == 4 || arg2 < s->unk_14) {
        return;
    }
    s->unk_00 = b;
    s->unk_04 = y;
    s->unk_08 = src->a;
    s->unk_0C = src->b;
    s->unk_10 = src->c;
    s->unk_14 = arg2;
    s->unk_2A = 0;
    s->unk_5C = arg7;
    s->unk_60 = arg8;
    s->unk_64 = arg6;
    s->unk_1E = 0;
    s->unk_26 = 0;
    s->unk_1C = 0x200;
    s->unk_24 = 0x400;
}
