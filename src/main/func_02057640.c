/* func_02057640 @ 0x02057640, 0x16 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x50];
    int unk_50;
    char pad_54[0x24];
    int unk_78;
    int unk_7C;
    int unk_80;
    int unk_84;
} UnkStruct_02057640;

void func_02057640(UnkStruct_02057640 *s)
{
    s->unk_50 = 0;
    s->unk_78 = 0;
    s->unk_7C = 0;
    s->unk_80 = -1;
    s->unk_84 = -1;
}
