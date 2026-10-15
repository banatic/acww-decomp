/* func_ov003_0220fbf8 @ 0x0220fbf8, 0x3c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct Sub0x2d0 {
    int pad_00;
} Sub0x2d0;

typedef struct {
    char pad_00[0x2d0];
    Sub0x2d0 sub_2d0;
    char pad1[0x7f0 - (0x2d0 + sizeof(Sub0x2d0))];
    int unk_7F0;
    char pad_7F4[0x7fc - (0x7f0 + 4)];
    int unk_7FC;
} UnkStruct_0220fbf8;

extern int func_02008258(UnkStruct_0220fbf8 *s, int x);
extern int func_02056f94(Sub0x2d0 *p);
extern int func_0200d4e8(UnkStruct_0220fbf8 *s, int a, int b, int c);

void func_ov003_0220fbf8(UnkStruct_0220fbf8 *s)
{
    s->unk_7FC = func_02008258(s, s->unk_7F0);
    if (func_02056f94(&s->sub_2d0) != 0) {
        func_0200d4e8(s, 3, 1, -1);
    }
}
