/* func_ov068_0226ee0c @ 0x0226ee0c, 0x48 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int FX_Div(int a, int b);

typedef struct {
    char pad_00[0x60];
    int unk_60;
    char pad_64[0x44];
    int unk_A8;
    char pad_AC[0x2cc];
    unsigned short unk_378;
    char pad_37A[0x6];
    int unk_380;
    char pad_384[0x12];
    unsigned short unk_396;
} UnkStruct_0226ee0c;

int func_ov068_0226ee0c(UnkStruct_0226ee0c *s)
{
    s->unk_378 &= ~0x10;
    s->unk_378 |= 0x20;
    s->unk_396 = 0;
    s->unk_A8 = FX_Div(s->unk_380 - s->unk_60, 0x1333);
    return 1;
}
