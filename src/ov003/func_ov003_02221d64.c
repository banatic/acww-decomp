/* func_ov003_02221d64 @ 0x02221d64, 0x3c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x3c];
    int unk_3C;
    char pad_40[4];
    int unk_44;
    char pad_48[6];
    unsigned short unk_4E;
} UnkStruct_02221d64;

extern void func_ov003_02222860(UnkStruct_02221d64 *s);

void func_ov003_02221d64(UnkStruct_02221d64 *s)
{
    unsigned short y = s->unk_4E;
    if ((y >= 6 && y <= 10) || y >= 18) {
        s->unk_3C -= 410;
    }
    if (s->unk_3C <= 0) {
        s->unk_3C = 0;
        func_ov003_02222860(s);
    }
    s->unk_44 = s->unk_3C;
}
