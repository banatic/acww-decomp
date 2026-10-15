/* func_020157d4 @ 0x020157d4, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x78];
    int (*unk_78)(unsigned short *, int);
    unsigned short unk_7C;
    unsigned short unk_7E;
    char pad_80[4];
    unsigned char unk_84;
    char pad_85[3];
    unsigned char unk_88;
} UnkStruct_020157d4;

void func_020157d4(UnkStruct_020157d4 *s, int (*val1)(unsigned short *, int), unsigned char val2, unsigned char val3)
{
    s->unk_7C = 0;
    s->unk_78 = val1;
    s->unk_84 = val2;
    s->unk_7E = 0xfff1;
    s->unk_88 = val3;
}
