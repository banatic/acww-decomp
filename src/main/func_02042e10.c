/* func_02042e10 @ 0x02042e10, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char unk_00;
    char unk_01;
    short unk_02;
    short unk_04;
} UnkStruct_02042e10;

typedef struct {
    int unk_00;
    int w1;
} UnkStruct_02042e10_2;

extern int func_0205be38(int a, int b);
extern void func_02042d94(UnkStruct_02042e10 *a, UnkStruct_02042e10_2 *b);

void func_02042e10(UnkStruct_02042e10 *a, UnkStruct_02042e10_2 *b)
{
    UnkStruct_02042e10_2 buf;

    if (a->unk_04 < 0) {
        int y = b->w1;
        int x = b->unk_00;

        a->unk_01 = x;
        a->unk_00 = y;
        a->unk_04 = ((func_0205be38(x, y) * 960) >> 12) + 150;
    }
    a->unk_02++;
    if (a->unk_02 >= 8) {
        a->unk_02 = 8;
    }
    buf.unk_00 = b->unk_00;
    buf.w1 = b->w1;
    func_02042d94(a, &buf);
}
